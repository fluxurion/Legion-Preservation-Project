/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Boss_Prince_Malchezzar
SD%Complete: 100
SDComment:
SDCategory: Karazhan
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum Says
{
    SAY_AGGRO = 0,
    SAY_AXE_TOSS,
    SAY_SPECIAL,
    SAY_SLAY,
    SAY_SUMMON,
    SAY_DEATH
};

// 18 Coordinates for Infernal spawns
struct InfernalPoint
{
    float x, y;
};

#define INFERNAL_Z  275.5f

static InfernalPoint InfernalPoints[] =
{
    {-10922.8f, -1985.2f},
    {-10916.2f, -1996.2f},
    {-10932.2f, -2008.1f},
    {-10948.8f, -2022.1f},
    {-10958.7f, -1997.7f},
    {-10971.5f, -1997.5f},
    {-10990.8f, -1995.1f},
    {-10989.8f, -1976.5f},
    {-10971.6f, -1973.0f},
    {-10955.5f, -1974.0f},
    {-10939.6f, -1969.8f},
    {-10958.0f, -1952.2f},
    {-10941.7f, -1954.8f},
    {-10943.1f, -1988.5f},
    {-10948.8f, -2005.1f},
    {-10984.0f, -2019.3f},
    {-10932.8f, -1979.6f},
    {-10935.7f, -1996.0f}
};

#define TOTAL_INFERNAL_POINTS       18

//Enfeeble is supposed to reduce hp to 1 and then heal player back to full when it ends
//Along with reducing healing and regen while enfeebled to 0%
//This spell effect will only reduce healing

#define SPELL_ENFEEBLE              30843                       //Enfeeble during phase 1 and 2
#define SPELL_ENFEEBLE_EFFECT       41624

#define SPELL_SHADOWNOVA            30852                       //Shadownova used during all phases
#define SPELL_SW_PAIN               30854                       //Shadow word pain during phase 1 and 3 (different targeting rules though)
#define SPELL_THRASH_PASSIVE        12787                       //Extra attack chance during phase 2
#define SPELL_SUNDER_ARMOR          30901                       //Sunder armor during phase 2
#define SPELL_THRASH_AURA           12787                       //Passive proc chance for thrash
#define SPELL_EQUIP_AXES            30857                       //Visual for axe equiping
#define SPELL_AMPLIFY_DAMAGE        39095                       //Amplifiy during phase 3
#define SPELL_CLEAVE                30131                       //Same as Nightbane.
#define SPELL_HELLFIRE              30859                       //Infenals' hellfire aura
#define NETHERSPITE_INFERNAL        17646                       //The netherspite infernal creature
#define MALCHEZARS_AXE              17650                       //Malchezar's axes (creatures), summoned during phase 3

#define INFERNAL_MODEL_INVISIBLE    11686                      //Infernal Effects
#define SPELL_INFERNAL_RELAY        30834

#define EQUIP_ID_AXE                33542                      //Axes info

//---------Infernal code first
class netherspite_infernal : public CreatureScript
{
public:
    netherspite_infernal() : CreatureScript("netherspite_infernal") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new netherspite_infernalAI (creature);
    }

    struct netherspite_infernalAI : public ScriptedAI
    {
        netherspite_infernalAI(Creature* creature) : ScriptedAI(creature), HellfireTimer(0), CleanupTimer(0), point(NULL) {}

        uint32 HellfireTimer;
        uint32 CleanupTimer;
        ObjectGuid malchezaar;
        InfernalPoint *point;

        void Reset() override {}
        void EnterCombat(Unit* /*who*/) override {}
        void MoveInLineOfSight(Unit* /*who*/) override {}

        void UpdateAI(uint32 diff) override
        {
            if (HellfireTimer)
            {
                if (HellfireTimer <= diff)
                {
                    DoCast(SPELL_HELLFIRE);
                    HellfireTimer = 0;
                }
                else
                    HellfireTimer -= diff;
            }

            if (CleanupTimer)
            {
                if (CleanupTimer <= diff)
                {
                    Cleanup();
                    CleanupTimer = 0;
                }
                else
                    CleanupTimer -= diff;
            }
        }

        void KilledUnit(Unit* who) override
        {
            if (Unit* pMalchezaar = Unit::GetUnit(*me, malchezaar))
                CAST_CRE(pMalchezaar)->AI()->KilledUnit(who);
        }

        void SpellHit(Unit* /*who*/, const SpellInfo* spell) override
        {
            if (spell->Id == SPELL_INFERNAL_RELAY)
            {
                me->SetDisplayId(me->GetUInt32Value(UNIT_FIELD_NATIVE_DISPLAY_ID));
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                HellfireTimer = 4000;
                CleanupTimer = 170000;
            }
        }

        void DamageTaken(Unit* done_by, uint32 &damage, DamageEffectType /*dmgType*/) override
        {
            if (done_by->GetGUID() != malchezaar)
                damage = 0;
        }

        void Cleanup();
    };
};

class boss_malchezaar : public CreatureScript
{
public:
    boss_malchezaar() : CreatureScript("boss_malchezaar") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_malchezaarAI (creature);
    }

    struct boss_malchezaarAI : public ScriptedAI
    {
        boss_malchezaarAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            memset(axes, 0, sizeof(axes));
        }

        InstanceScript* instance;
        uint32 EnfeebleTimer;
        uint32 EnfeebleResetTimer;
        uint32 ShadowNovaTimer;
        uint32 SWPainTimer;
        uint32 SunderArmorTimer;
        uint32 AmplifyDamageTimer;
        uint32 Cleave_Timer;
        uint32 InfernalTimer;
        uint32 AxesTargetSwitchTimer;
        uint32 InfernalCleanupTimer;

        GuidVector infernals;
        std::vector<InfernalPoint*> positions;

        ObjectGuid axes[2];
        ObjectGuid enfeeble_targets[5];
        uint32 enfeeble_health[5];

        uint32 phase;

        void Reset() override
        {
            AxesCleanup();
            ClearWeapons();
            InfernalCleanup();
            positions.clear();

            for (uint8 i = 0; i < 5; ++i)
            {
                enfeeble_targets[i].Clear();
                enfeeble_health[i] = 0;
            }

            for (uint8 i = 0; i < TOTAL_INFERNAL_POINTS; ++i)
                positions.push_back(&InfernalPoints[i]);

            EnfeebleTimer = 30000;
            EnfeebleResetTimer = 38000;
            ShadowNovaTimer = 35500;
            SWPainTimer = 20000;
            AmplifyDamageTimer = 5000;
            Cleave_Timer = 8000;
            InfernalTimer = 40000;
            InfernalCleanupTimer = 47000;
            AxesTargetSwitchTimer = urand(7500, 20000);
            SunderArmorTimer = urand(5000, 10000);
            phase = 1;

            if (instance)
                instance->HandleGameObject(instance->GetGuidData(DATA_GO_NETHER_DOOR), true);
        }

        void KilledUnit(Unit* /*victim*/) override
        {
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(SAY_DEATH);

            AxesCleanup();
            ClearWeapons();
            InfernalCleanup();
            positions.clear();

            for (uint8 i = 0; i < TOTAL_INFERNAL_POINTS; ++i)
                positions.push_back(&InfernalPoints[i]);

            if (instance)
                instance->HandleGameObject(instance->GetGuidData(DATA_GO_NETHER_DOOR), true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO);

            if (instance)
                instance->HandleGameObject(instance->GetGuidData(DATA_GO_NETHER_DOOR), false); // Open the door leading further in
        }

        void InfernalCleanup()
        {
            //Infernal Cleanup
            for (GuidVector::const_iterator itr = infernals.begin(); itr != infernals.end(); ++itr)
            {
                if (Unit* pInfernal = Unit::GetUnit(*me, *itr))
                {
                    if (pInfernal->IsAlive())
                    {
                        pInfernal->SetVisible(false);
                        pInfernal->setDeathState(JUST_DIED);
                    }
                }
            }

            infernals.clear();
        }

        void AxesCleanup()
        {
            for (uint8 i = 0; i < 2; ++i)
            {
                if (Unit* axe = Unit::GetUnit(*me, axes[i]))
                    if (axe->IsAlive())
                        axe->Kill(axe);

                axes[i].Clear();
            }
        }

        void ClearWeapons()
        {
            SetEquipmentSlots(false, EQUIP_UNEQUIP, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
        }

        void EnfeebleHealthEffect()
        {
            const SpellInfo* info = sSpellMgr->GetSpellInfo(SPELL_ENFEEBLE_EFFECT);
            if (!info)
                return;

            std::list<HostileReference*> t_list = me->getThreatManager().getThreatList();
            std::vector<Unit*> targets;

            if (t_list.empty())
                return;

            //begin + 1, so we don't target the one with the highest threat
            std::list<HostileReference*>::const_iterator itr = t_list.begin();
            std::advance(itr, 1);
            for (; itr != t_list.end(); ++itr) //store the threat list in a different container
                if (Unit* target = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                    if (target->IsAlive() && target->GetTypeId() == TYPEID_PLAYER)
                        targets.push_back(target);

            //cut down to size if we have more than 5 targets
            while (targets.size() > 5)
                targets.erase(targets.begin()+rand()%targets.size());

            uint32 i = 0;
            for (std::vector<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter, ++i)
                if (Unit* target = *iter)
                {
                    enfeeble_targets[i] = target->GetGUID();
                    enfeeble_health[i] = target->GetHealth();

                    target->CastSpell(target, SPELL_ENFEEBLE, true, 0, NULL, me->GetGUID());
                    target->SetHealth(1);
                }
        }

        void EnfeebleResetHealth()
        {
            for (uint8 i = 0; i < 5; ++i)
            {
                Unit* target = Unit::GetUnit(*me, enfeeble_targets[i]);
                if (target && target->IsAlive())
                    target->SetHealth(enfeeble_health[i]);
                enfeeble_targets[i].Clear();
                enfeeble_health[i] = 0;
            }
        }

        void SummonInfernal(const uint32 /*diff*/)
        {
            InfernalPoint *point = NULL;
            Position pos;
            if ((me->GetMapId() != 532) || positions.empty())
                pos = me->GetRandomNearPosition(60);
            else
            {
                point = Trinity::Containers::SelectRandomContainerElement(positions);
                pos.Relocate(point->x, point->y, INFERNAL_Z, frand(0.0f, float(M_PI * 2)));
            }

            Creature* Infernal = me->SummonCreature(NETHERSPITE_INFERNAL, pos, TEMPSUMMON_TIMED_DESPAWN, 180000);

            if (Infernal)
            {
                Infernal->SetDisplayId(INFERNAL_MODEL_INVISIBLE);
                Infernal->setFaction(me->getFaction());
                if (point)
                    CAST_AI(netherspite_infernal::netherspite_infernalAI, Infernal->AI())->point=point;
                CAST_AI(netherspite_infernal::netherspite_infernalAI, Infernal->AI())->malchezaar=me->GetGUID();

                infernals.push_back(Infernal->GetGUID());
                DoCast(Infernal, SPELL_INFERNAL_RELAY);
            }

            Talk(SAY_SUMMON);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (EnfeebleResetTimer && EnfeebleResetTimer <= diff) // Let's not forget to reset that
            {
                EnfeebleResetHealth();
                EnfeebleResetTimer = 0;
            }
            else
                EnfeebleResetTimer -= diff;

            if (me->HasUnitState(UNIT_STATE_STUNNED))      // While shifting to phase 2 malchezaar stuns himself
                return;

            if (me->GetGuidValue(UNIT_FIELD_TARGET) != me->getVictim()->GetGUID())
                me->SetTarget(me->getVictim()->GetGUID());

            if (phase == 1)
            {
                if (HealthBelowPct(60))
                {
                    me->InterruptNonMeleeSpells(false);

                    phase = 2;

                    //animation
                    DoCast(SPELL_EQUIP_AXES);

                    //text
                    Talk(SAY_AXE_TOSS);

                    //passive thrash aura
                    DoCast(me, SPELL_THRASH_AURA, true);

                    //models
                    SetEquipmentSlots(false, EQUIP_ID_AXE, EQUIP_ID_AXE, EQUIP_NO_CHANGE);
                    me->SetAttackTime(OFF_ATTACK, (me->GetAttackTime(BASE_ATTACK)*150)/100);
                }
            }
            else if (phase == 2)
            {
                if (HealthBelowPct(30))
                {
                    InfernalTimer = 15000;

                    phase = 3;

                    ClearWeapons();

                    //remove thrash
                    me->RemoveAurasDueToSpell(SPELL_THRASH_AURA);

                    Talk(SAY_AXE_TOSS);

                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                    for (uint8 i = 0; i < 2; ++i)
                    {
                        Creature* axe = me->SummonCreature(MALCHEZARS_AXE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
                        if (axe)
                        {
                            axe->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            axe->setFaction(me->getFaction());
                            axes[i] = axe->GetGUID();
                            if (target)
                            {
                                axe->AI()->AttackStart(target);
                                //axe->getThreatManager().tauntApply(target); //Taunt Apply and fade out does not work properly
                                                                // So we'll use a hack to add a lot of threat to our target
                                axe->AddThreat(target, 10000000.0f);
                            }
                        }
                    }

                    if (ShadowNovaTimer > 35000)
                        ShadowNovaTimer = EnfeebleTimer + 5000;

                    return;
                }

                if (SunderArmorTimer <= diff)
                {
                    if (auto victim = me->getVictim())
                        DoCast(victim, SPELL_SUNDER_ARMOR, false);

                    SunderArmorTimer = urand(10000, 18000);

                } 
                else
                    SunderArmorTimer -= diff;

                if (Cleave_Timer <= diff)
                {
                    if (auto victim = me->getVictim())
                        DoCast(victim, SPELL_CLEAVE, false);

                    Cleave_Timer = urand(6000, 12000);

                }
                else
                    Cleave_Timer -= diff;
            }
            else
            {
                if (AxesTargetSwitchTimer <= diff)
                {
                    AxesTargetSwitchTimer = urand(7500, 20000);

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Unit* axe = Unit::GetUnit(*me, axes[i]))
                            {
                                if (axe->getVictim())
                                    DoModifyThreatPercent(axe->getVictim(), -100);
                                if (target)
                                    axe->AddThreat(target, 1000000.0f);
                                //axe->getThreatManager().tauntFadeOut(axe->getVictim());
                                //axe->getThreatManager().tauntApply(target);
                            }
                        }
                    }
                } else AxesTargetSwitchTimer -= diff;

                if (AmplifyDamageTimer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(target, SPELL_AMPLIFY_DAMAGE, false);

                    AmplifyDamageTimer = urand(20000, 30000);
                }
                else
                    AmplifyDamageTimer -= diff;
            }

            //Time for global and double timers
            if (InfernalTimer <= diff)
            {
                SummonInfernal(diff);
                InfernalTimer = phase == 3 ? 14500 : 44500;    // 15 secs in phase 3, 45 otherwise
            }
            else
                InfernalTimer -= diff;

            if (ShadowNovaTimer <= diff)
            {
                if (auto victim = me->getVictim())
                    DoCast(victim, SPELL_SHADOWNOVA, false);

                ShadowNovaTimer = phase == 3 ? 31000 : uint32(-1);
            }
            else
                ShadowNovaTimer -= diff;

            if (phase != 2)
            {
                if (SWPainTimer <= diff)
                {
                    Unit* target = NULL;
                    if (phase == 1)
                        target = me->getVictim();        // the tank
                    else                                          // anyone but the tank
                        target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true);

                    if (target)
                        DoCast(target, SPELL_SW_PAIN);

                    SWPainTimer = 20000;
                }
                else
                    SWPainTimer -= diff;
            }

            if (phase != 3)
            {
                if (EnfeebleTimer <= diff)
                {
                    EnfeebleHealthEffect();
                    EnfeebleTimer = 30000;
                    ShadowNovaTimer = 5000;
                    EnfeebleResetTimer = 9000;
                }
                else
                    EnfeebleTimer -= diff;
            }

            if (phase == 2)
                DoMeleeAttacksIfReady();
            else
                DoMeleeAttackIfReady();
        }

        void DoMeleeAttacksIfReady()
        {
            if (me->IsWithinMeleeRange(me->getVictim()) && !me->IsNonMeleeSpellCast(false))
            {
                //Check for base attack
                if (me->isAttackReady() && me->getVictim())
                {
                    me->AttackerStateUpdate(me->getVictim());
                    me->resetAttackTimer();
                }
                //Check for offhand attack
                if (me->isAttackReady(OFF_ATTACK) && me->getVictim())
                {
                    me->AttackerStateUpdate(me->getVictim(), OFF_ATTACK);
                    me->resetAttackTimer(OFF_ATTACK);
                }
            }
        }

        void Cleanup(Creature* infernal, InfernalPoint *point)
        {
            for (GuidVector::iterator itr = infernals.begin(); itr != infernals.end(); ++itr)
            {
                if (*itr == infernal->GetGUID())
                {
                    infernals.erase(itr);
                    break;
                }
            }

            positions.push_back(point);
        }
    };

};

void netherspite_infernal::netherspite_infernalAI::Cleanup()
{
    Unit* pMalchezaar = Unit::GetUnit(*me, malchezaar);

    if (pMalchezaar && pMalchezaar->IsAlive())
        CAST_AI(boss_malchezaar::boss_malchezaarAI, CAST_CRE(pMalchezaar)->AI())->Cleanup(me, point);
}

void AddSC_boss_malchezaar()
{
    new boss_malchezaar();
    new netherspite_infernal();
}
