/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

#ifndef _CHARACTERDATABASE_H
#define _CHARACTERDATABASE_H

#include "MySQLConnection.h"

enum CharacterDatabaseStatements : uint32
{
    /*  Naming standard for defines:
        {DB}_{SEL/INS/UPD/DEL/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    CHAR_DEL_QUEST_POOL_SAVE,
    CHAR_INS_QUEST_POOL_SAVE,
    CHAR_DEL_NONEXISTENT_GUILD_BANK_ITEM,
    CHAR_DEL_EXPIRED_BANS,
    CHAR_SEL_GUID_BY_NAME,
    CHAR_SEL_CHECK_NAME,
    CHAR_SEL_CHECK_GUID,
    CHAR_SEL_SUM_CHARS,
    CHAR_SEL_CHAR_CREATE_INFO,
    CHAR_INS_CHARACTER_BAN,
    CHAR_UPD_CHARACTER_BAN,
    CHAR_DEL_CHARACTER_BAN,
    CHAR_SEL_BANINFO,
    CHAR_SEL_GUID_BY_NAME_FILTER,
    CHAR_SEL_BANINFO_LIST,
    CHAR_SEL_BANNED_NAME,
    CHAR_SEL_MAIL_LIST_COUNT,
    CHAR_SEL_MAIL_LIST_INFO,
    CHAR_SEL_MAIL_LIST_ITEMS,
    CHAR_SEL_ENUM,
    CHAR_SEL_ENUM_DELETED,
    CHAR_SEL_ENUM_DECLINED_NAME,

    // Pet
    CHAR_SEL_PET,
    CHAR_INS_PET,
    CHAR_SEL_PET_DETAIL,
    CHAR_SEL_PET_BY_ID,
    CHAR_DEL_CHAR_PET_BY_ID,
    CHAR_DEL_CHAR_PET_DECLINED_BY_ID,
    CHAR_DEL_CHAR_PET_AURA_BY_ID,
    CHAR_DEL_CHAR_PET_SPELL_BY_ID,
    CHAR_DEL_CHAR_PET_SPELL_COOLDOWN_BY_ID,
    CHAR_DEL_INVALID_PET_SPELL,

    CHAR_SEL_FREE_NAME,
    CHAR_SEL_GUID_RACE_ACC_BY_NAME,
    CHAR_SEL_CHAR_RACE,
    CHAR_SEL_CHAR_LEVEL,
    CHAR_SEL_CHAR_ZONE,
    CHAR_SEL_CHARACTER_NAME_DATA,
    CHAR_SEL_CHAR_POSITION_XYZ,
    CHAR_SEL_CHAR_POSITION,
    CHAR_DEL_QUEST_STATUS_DAILY,
    CHAR_DEL_QUEST_STATUS_WEEKLY,
    CHAR_DEL_QUEST_STATUS_SEASONAL,
    CHAR_DEL_QUEST_STATUS_DAILY_CHAR,
    CHAR_DEL_QUEST_STATUS_DAILY_ACC,
    CHAR_DEL_QUEST_STATUS_WEEKLY_CHAR,
    CHAR_DEL_QUEST_STATUS_WEEKLY_ACC,
    CHAR_DEL_QUEST_STATUS_SEASONAL_CHAR,
    CHAR_DEL_QUEST_STATUS_SEASONAL_ACC,

    CHAR_DEL_QUEST_STATUS_C,
    CHAR_DEL_QUEST_STATUS_DAILY_C,
    CHAR_DEL_QUEST_STATUS_WEEKLY_C,
    CHAR_DEL_QUEST_STATUS_SEASONAL_C,

    CHAR_DEL_BATTLEGROUND_RANDOM,
    CHAR_REP_BATTLEGROUND_RANDOM,

    CHAR_SEL_CHARACTER,
    CHAR_SEL_GROUP_MEMBER,
    CHAR_SEL_CHARACTER_INSTANCE,
    CHAR_SEL_CHARACTER_AURAS,
    CHAR_SEL_CHARACTER_AURAS_EFFECTS,
    CHAR_SEL_CHARACTER_SPELL,
    CHAR_SEL_CHARACTER_QUESTSTATUS,
    CHAR_SEL_CHARACTER_QUESTSTATUS_OBJECTIVES,
    CHAR_SEL_CHARACTER_DAILYQUESTSTATUS,
    CHAR_SEL_CHARACTER_WEEKLYQUESTSTATUS,
    CHAR_SEL_CHARACTER_SEASONALQUESTSTATUS,
    CHAR_INS_CHARACTER_DAILYQUESTSTATUS,
    CHAR_INS_CHARACTER_WEEKLYQUESTSTATUS,
    CHAR_INS_CHARACTER_SEASONALQUESTSTATUS,
    CHAR_SEL_CHARACTER_REPUTATION,
    CHAR_SEL_CHARACTER_INVENTORY,
    CHAR_SEL_CHARACTER_NOT_INVENTORY,
    CHAR_SEL_ITEM_INFO,
    CHAR_SEL_CHARACTER_ACTIONS,
    CHAR_SEL_CHARACTER_ACTIONS_SPEC,
    CHAR_SEL_CHARACTER_MAILCOUNT,
    CHAR_SEL_CHARACTER_MAILDATE,
    CHAR_SEL_MAIL_COUNT,
    CHAR_SEL_CHARACTER_SOCIALLIST,
    CHAR_SEL_CHARACTER_HOMEBIND,
    CHAR_SEL_CHARACTER_SPELLCOOLDOWNS,
    CHAR_SEL_CHARACTER_DECLINEDNAMES,
    CHAR_SEL_GUILD_MEMBER,
    CHAR_SEL_CHARACTER_BRACKETS,
    CHAR_REP_CHARACTER_BRACKETS_STATS,
    CHAR_UPD_CHARACTER_BRACKETS_STATS,
    CHAR_DEL_PLAYER_BRACKETS_INFO,
    CHAR_SEL_CHARACTER_ACHIEVEMENTS,
    CHAR_SEL_ACCOUNT_ACHIEVEMENTS,
    CHAR_SEL_CHARACTER_CRITERIAPROGRESS,
    CHAR_SEL_ACCOUNT_CRITERIAPROGRESS,
    CHAR_SEL_CHARACTER_BGDATA,
    CHAR_SEL_CHARACTER_GLYPHS,
    CHAR_SEL_CHARACTER_TALENTS,
    CHAR_SEL_CHARACTER_PVP_TALENTS,
    CHAR_SEL_CHARACTER_SKILLS,
    CHAR_SEL_CHARACTER_RANDOMBG,
    CHAR_SEL_CHARACTER_BANNED,
    CHAR_SEL_CHARACTER_QUESTSTATUSREW,
    CHAR_SEL_ACCOUNT_QUEST,
    CHAR_SEL_CHARACTER_QUESTSTATUSREW_NON_ACC,
    CHAR_SEL_MAILITEMS,
    CHAR_SEL_AUCTION_ITEMS,
    CHAR_INS_AUCTION,
    CHAR_DEL_AUCTION,
    CHAR_SEL_AUCTION_BY_TIME,
    CHAR_UPD_AUCTION_BID,
    CHAR_SEL_AUCTIONS,
    CHAR_INS_MAIL,
    CHAR_DEL_MAIL_BY_ID,
    CHAR_INS_MAIL_ITEM,
    CHAR_DEL_MAIL_ITEM,
    CHAR_DEL_INVALID_MAIL_ITEM,
    CHAR_DEL_EMPTY_EXPIRED_MAIL,
    CHAR_SEL_EXPIRED_MAIL,
    CHAR_SEL_EXPIRED_MAIL_ITEMS,
    CHAR_UPD_MAIL_RETURNED,
    CHAR_UPD_MAIL_ITEM_RECEIVER,
    CHAR_UPD_ITEM_OWNER,
    CHAR_SEL_ITEM_REFUNDS,
    CHAR_SEL_ITEM_BOP_TRADE,
    CHAR_DEL_ITEM_BOP_TRADE,
    CHAR_INS_ITEM_BOP_TRADE,
    CHAR_REP_INVENTORY_ITEM,
    CHAR_REP_ITEM_INSTANCE,
    CHAR_UPD_ITEM_INSTANCE,
    CHAR_UPD_ITEM_INSTANCE_ON_LOAD,
    CHAR_DEL_ITEM_INSTANCE,
    CHAR_INS_ITEM_INSTANCE_GEMS,
    CHAR_DEL_ITEM_INSTANCE_GEMS,
    CHAR_DEL_ITEM_INSTANCE_GEMS_BY_OWNER,
    CHAR_INS_ITEM_INSTANCE_TRANSMOG,
    CHAR_DEL_ITEM_INSTANCE_TRANSMOG,
    CHAR_DEL_ITEM_INSTANCE_TRANSMOG_BY_OWNER,
    CHAR_UPD_GIFT_OWNER,
    CHAR_DEL_GIFT,
    CHAR_SEL_CHARACTER_GIFT_BY_ITEM,
    CHAR_SEL_ACCOUNT_BY_NAME,
    CHAR_SEL_ACCOUNT_BY_GUID,
    CHAR_SEL_CHARACTER_NAME_CLASS,
    CHAR_SEL_CHARACTER_NAME,
    CHAR_SEL_CHARACTER_COUNT,
    CHAR_UPD_NAME,
    CHAR_UPD_NAME_LOG,
    CHAR_SEL_ACCOUNT_NAME_BY_GUID,

    CHAR_INS_GUILD,
    CHAR_DEL_GUILD,
    CHAR_INS_GUILD_MEMBER,
    CHAR_DEL_GUILD_MEMBER,
    CHAR_DEL_GUILD_MEMBERS,
    CHAR_UPD_GUILD_MEMBERS_RANK,
    CHAR_UPD_GUILD_MEMBER_STATS,
    CHAR_INS_GUILD_RANK,
    CHAR_DEL_GUILD_RANKS,
    CHAR_DEL_GUILD_RANK,
    CHAR_UPD_GUILD_RANK_ID,
    CHAR_INS_GUILD_BANK_TAB,
    CHAR_DEL_GUILD_BANK_TAB,
    CHAR_DEL_GUILD_BANK_TABS,
    CHAR_INS_GUILD_BANK_ITEM,
    CHAR_DEL_GUILD_BANK_ITEM,
    CHAR_DEL_GUILD_BANK_ITEMS,
    CHAR_SEL_GUILD_BANK_ITEMS,
    CHAR_INS_GUILD_BANK_RIGHT_DEFAULT,
    CHAR_INS_GUILD_BANK_RIGHT,
    CHAR_DEL_GUILD_BANK_RIGHT,
    CHAR_DEL_GUILD_BANK_RIGHTS,
    CHAR_DEL_GUILD_BANK_RIGHTS_FOR_RANK,
    CHAR_UPD_GUILD_BANK_RIGHTS_ID,
    CHAR_INS_GUILD_BANK_EVENTLOG,
    CHAR_DEL_GUILD_BANK_EVENTLOG,
    CHAR_DEL_GUILD_BANK_EVENTLOGS,
    CHAR_INS_GUILD_EVENTLOG,
    CHAR_DEL_GUILD_EVENTLOG,
    CHAR_DEL_GUILD_EVENTLOGS,
    CHAR_UPD_GUILD_MEMBER_PNOTE,
    CHAR_UPD_GUILD_MEMBER_OFFNOTE,
    CHAR_UPD_GUILD_MEMBER_RANK,
    CHAR_UPD_GUILD_NAME,
    CHAR_UPD_GUILD_MOTD,
    CHAR_UPD_GUILD_INFO,
    CHAR_UPD_GUILD_FLAGS,
    CHAR_UPD_GUILD_LEADER,
    CHAR_UPD_GUILD_RANK_NAME,
    CHAR_UPD_GUILD_RANK_RIGHTS,
    CHAR_UPD_GUILD_EMBLEM_INFO,
    CHAR_UPD_GUILD_BANK_TAB_INFO,
    CHAR_UPD_GUILD_BANK_MONEY,
    CHAR_UPD_GUILD_BANK_EVENTLOG_TAB,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_MONEY,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_MONEY,
    CHAR_UPD_GUILD_RANK_BANK_RESET_TIME,
    CHAR_UPD_GUILD_RANK_BANK_MONEY,
    CHAR_UPD_GUILD_BANK_TAB_TEXT,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS0,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS1,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS2,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS3,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS4,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS5,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS6,
    CHAR_UPD_GUILD_MEMBER_BANK_TIME_REM_SLOTS7,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS0,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS1,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS2,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS3,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS4,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS5,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS6,
    CHAR_UPD_GUILD_MEMBER_BANK_REM_SLOTS7,
    CHAR_UPD_GUILD_RANK_BANK_TIME0,
    CHAR_UPD_GUILD_RANK_BANK_TIME1,
    CHAR_UPD_GUILD_RANK_BANK_TIME2,
    CHAR_UPD_GUILD_RANK_BANK_TIME3,
    CHAR_UPD_GUILD_RANK_BANK_TIME4,
    CHAR_UPD_GUILD_RANK_BANK_TIME5,
    CHAR_UPD_GUILD_RANK_BANK_TIME6,
    CHAR_UPD_GUILD_RANK_BANK_TIME7,
    CHAR_SEL_CHAR_DATA_FOR_GUILD,
    CHAR_REP_GUILD_ACHIEVEMENT,
    CHAR_REP_GUILD_ACHIEVEMENT_CRITERIA,
    CHAR_UPD_GUILD_ACHIEVEMENT_CRITERIA,
    CHAR_DEL_GUILD_INVALID_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_GUILD_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_ALL_GUILD_ACHIEVEMENTS,
    CHAR_DEL_ALL_GUILD_ACHIEVEMENT_CRITERIA,
    CHAR_SEL_GUILD_ACHIEVEMENT,
    CHAR_SEL_GUILD_ACHIEVEMENT_CRITERIA,
    CHAR_UPD_GUILD_EXPERIENCE,
    CHAR_UPD_GUILD_RESET_TODAY_EXPERIENCE,
    CHAR_LOAD_GUILD_CHALLENGES,
    CHAR_INIT_GUILD_CHALLENGES,
    CHAR_COMPLETE_GUILD_CHALLENGE,
    CHAR_REMOVE_GUILD_CHALLENGES,

    CHAR_INS_GUILD_NEWS,

    CHAR_SEL_PLAYER_ARCHAELOGY,
    CHAR_SEL_PLAYER_ARCHAEOLOGY_FINDS,
    CHAR_REP_PLAYER_ARCHAEOLOGY,
    CHAR_REP_PLAYER_ARCHAEOLOGY_FINDS,

    CHAR_SEL_CHANNEL,
    CHAR_INS_CHANNEL,
    CHAR_UPD_CHANNEL,
    CHAR_UPD_CHANNEL_USAGE,
    CHAR_UPD_CHANNEL_OWNERSHIP,
    CHAR_DEL_OLD_CHANNELS,

    CHAR_SEL_CHARACTER_EQUIPMENTSETS,
    CHAR_SEL_CHARACTER_TRANSMOG_OUTFITS,
    CHAR_UPD_EQUIP_SET,
    CHAR_INS_EQUIP_SET,
    CHAR_DEL_EQUIP_SET,
    CHAR_UPD_TRANSMOG_OUTFIT,
    CHAR_INS_TRANSMOG_OUTFIT,
    CHAR_DEL_TRANSMOG_OUTFIT,

    CHAR_INS_AURA,
    CHAR_INS_AURA_EFFECT,

    CHAR_SEL_PLAYER_CURRENCY,
    CHAR_UPD_PLAYER_CURRENCY,
    CHAR_REP_PLAYER_CURRENCY,

    CHAR_SEL_ACCOUNT_DATA,
    CHAR_REP_ACCOUNT_DATA,
    CHAR_DEL_ACCOUNT_DATA,
    CHAR_SEL_PLAYER_ACCOUNT_DATA,
    CHAR_REP_PLAYER_ACCOUNT_DATA,
    CHAR_DEL_PLAYER_ACCOUNT_DATA,

    CHAR_SEL_TUTORIALS,
    CHAR_INS_TUTORIALS,
    CHAR_UPD_TUTORIALS,
    CHAR_DEL_TUTORIALS,

    CHAR_DEL_GAME_EVENT_SAVE,
    CHAR_INS_GAME_EVENT_SAVE,

    CHAR_DEL_ALL_GAME_EVENT_CONDITION_SAVE,
    CHAR_DEL_GAME_EVENT_CONDITION_SAVE,
    CHAR_INS_GAME_EVENT_CONDITION_SAVE,

    CHAR_SEL_PETITION,
    CHAR_SEL_PETITION_SIGNATURE,
    CHAR_DEL_ALL_PETITION_SIGNATURES,
    CHAR_DEL_PETITION_SIGNATURE,
    CHAR_SEL_PETITION_BY_OWNER,
    CHAR_SEL_PETITION_TYPE,
    CHAR_SEL_PETITION_SIGNATURES,
    CHAR_SEL_PETITION_SIG_BY_ACCOUNT,
    CHAR_SEL_PETITION_OWNER_BY_GUID,
    CHAR_SEL_PETITION_SIG_BY_GUID,

    CHAR_INS_PLAYER_BGDATA,
    CHAR_DEL_PLAYER_BGDATA,

    CHAR_INS_PLAYER_HOMEBIND,
    CHAR_UPD_PLAYER_HOMEBIND,
    CHAR_DEL_PLAYER_HOMEBIND,

    CHAR_SEL_CORPSES,
    CHAR_INS_CORPSE,
    CHAR_DEL_CORPSE,
    CHAR_DEL_PLAYER_CORPSES,
    CHAR_DEL_OLD_CORPSES,

    CHAR_SEL_CREATURE_RESPAWNS,
    CHAR_REP_CREATURE_RESPAWN,
    CHAR_DEL_CREATURE_RESPAWN,
    CHAR_DEL_CREATURE_RESPAWN_BY_INSTANCE,
    CHAR_SEL_MAX_CREATURE_RESPAWNS,

    CHAR_SEL_GO_RESPAWNS,
    CHAR_REP_GO_RESPAWN,
    CHAR_DEL_GO_RESPAWN,
    CHAR_DEL_GO_RESPAWN_BY_INSTANCE,

    CHAR_SEL_GM_TICKETS,
    CHAR_REP_GM_TICKET,
    CHAR_DEL_GM_TICKET,
    CHAR_DEL_ALL_GM_TICKETS,
    CHAR_DEL_PLAYER_GM_TICKETS,

    CHAR_INS_GM_SURVEY,
    CHAR_INS_GM_SUBSURVEY,

    CHAR_INS_CHARACTER,
    CHAR_UPD_CHARACTER,

    CHAR_UPD_ADD_AT_LOGIN_FLAG,
    CHAR_UPD_REM_AT_LOGIN_FLAG,
    CHAR_UPD_ALL_AT_LOGIN_FLAGS,
    CHAR_INS_BUG_REPORT,
    CHAR_UPD_PETITION_NAME,
    CHAR_INS_PETITION_SIGNATURE,
    CHAR_UPD_ACCOUNT_ONLINE,
    CHAR_INS_GROUP,
    CHAR_INS_GROUP_MEMBER,
    CHAR_DEL_GROUP_MEMBER,
    CHAR_DEL_GROUP_INSTANCE_PERM_BINDING,
    CHAR_UPD_GROUP_LEADER,
    CHAR_UPD_GROUP_TYPE,
    CHAR_UPD_GROUP_MEMBER_SUBGROUP,
    CHAR_UPD_GROUP_MEMBER_FLAG,
    CHAR_UPD_GROUP_MEMBER_ROLE,
    CHAR_UPD_GROUP_DIFFICULTY,
    CHAR_UPD_GROUP_RAID_DIFFICULTY,
    CHAR_UPD_GROUP_LEGACY_RAID_DIFFICULTY,
    CHAR_DEL_INVALID_SPELL,
    CHAR_DEL_INVALID_TALENT,
    CHAR_DEL_INVALID_TALENT_PVP,
    CHAR_UPD_DELETE_INFO,
    CHAR_UDP_RESTORE_DELETE_INFO,
    CHAR_UPD_ZONE,
    CHAR_UPD_LEVEL,
    CHAR_DEL_INVALID_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_CHAR_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_INVALID_ACC_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_ACC_ACHIEV_PROGRESS_CRITERIA,
    CHAR_DEL_INVALID_ACHIEVMENT,
    CHAR_INS_ADDON,
    CHAR_DEL_GROUP_INSTANCE_BY_INSTANCE,
    CHAR_DEL_GROUP_INSTANCE_BY_GUID,
    CHAR_REP_GROUP_INSTANCE,
    CHAR_UPD_CHAR_ONLINE,
    CHAR_UPD_CHAR_NAME_AT_LOGIN,
    CHAR_UPD_WORLDSTATE,
    CHAR_INS_WORLDSTATE,
    CHAR_DEL_CHAR_INSTANCE_BY_INSTANCE_GUID,
    CHAR_UPD_CHAR_INSTANCE,
    CHAR_REP_CHAR_INSTANCE,
    CHAR_UPD_CHAR_INSTANCE_EXTENDED,
    CHAR_UPD_GENDER_PLAYERBYTES,
    CHAR_DEL_CHARACTER_SKILL,
    CHAR_UPD_ADD_CHARACTER_SOCIAL_FLAGS,
    CHAR_UPD_REM_CHARACTER_SOCIAL_FLAGS,
    CHAR_INS_CHARACTER_SOCIAL,
    CHAR_DEL_CHARACTER_SOCIAL,
    CHAR_UPD_CHARACTER_SOCIAL_NOTE,
    CHAR_UPD_CHARACTER_POSITION,

    CHAR_INS_LFG_DATA,
    CHAR_DEL_LFG_DATA,

    CHAR_SEL_CHARACTER_AURA_FROZEN,
    CHAR_SEL_CHARACTER_ONLINE,

    CHAR_SEL_CHAR_DEL_INFO_BY_GUID,
    CHAR_SEL_CHAR_DEL_INFO_BY_NAME,
    CHAR_SEL_CHAR_DEL_INFO,

    CHAR_SEL_CHARS_BY_ACCOUNT_ID,
    CHAR_SEL_CHAR_PINFO,
    CHAR_SEL_PINFO_BANS,
    CHAR_SEL_CHAR_HOMEBIND,
    CHAR_SEL_CHAR_GUID_NAME_BY_ACC,
    CHAR_SEL_POOL_QUEST_SAVE,
    CHAR_SEL_CHAR_CUSTOMIZE_INFO,
    CHAR_SEL_CHAR_CLASS_LVL_AT_LOGIN,
    CHAR_SEL_PET_SPELL_LIST,
    CHAR_SEL_CHAR_PET,
    CHAR_SEL_CHAR_PETS,
    CHAR_SEL_CHAR_COD_ITEM_MAIL,
    CHAR_SEL_CHAR_SOCIAL,
    CHAR_SEL_PET_AURA,
    CHAR_SEL_PET_AURA_EFFECT,
    CHAR_SEL_CHAR_OLD_CHARS,
    CHAR_SEL_MAIL,
    CHAR_SEL_PET_SPELL,
    CHAR_SEL_PET_SPELL_COOLDOWN,
    CHAR_SEL_PET_DECLINED_NAME,
    CHAR_SEL_CHAR_GUID_BY_NAME,
    CHAR_DEL_CHAR_AURA_FROZEN,
    CHAR_SEL_CHAR_INVENTORY_COUNT_ITEM,
    CHAR_SEL_MAIL_COUNT_ITEM,
    CHAR_SEL_AUCTIONHOUSE_COUNT_ITEM,
    CHAR_SEL_GUILD_BANK_COUNT_ITEM,
    CHAR_SEL_CHAR_INVENTORY_ITEM_BY_ENTRY,
    CHAR_SEL_MAIL_ITEMS_BY_ENTRY,
    CHAR_SEL_AUCTIONHOUSE_ITEM_BY_ENTRY,
    CHAR_SEL_GUILD_BANK_ITEM_BY_ENTRY,
    CHAR_DEL_ACCOUNT_ACHIEVEMENT,
    CHAR_DEL_CHAR_ACHIEVEMENT,
    CHAR_DEL_CHAR_ACHIEVEMENT_PROGRESS,
    CHAR_REP_CHAR_REPUTATION_BY_FACTION,
    CHAR_DEL_ITEM_REFUND_INSTANCE,
    CHAR_INS_ITEM_REFUND_INSTANCE,
    CHAR_DEL_GROUP,
    CHAR_DEL_GROUP_MEMBER_ALL,
    CHAR_INS_CHAR_GIFT,
    CHAR_DEL_CHAR_INSTANCE_BY_INSTANCE,
    CHAR_DEL_CHAR_INSTANCE_BY_MAP_DIFF,
    CHAR_DEL_GROUP_INSTANCE_BY_MAP_DIFF,
    CHAR_DEL_MAIL_ITEM_BY_ID,
    CHAR_DEL_CHAR_PET_DECLINEDNAME,
    CHAR_ADD_CHAR_PET_DECLINEDNAME,
    CHAR_UPD_CHAR_PET_NAME,
    CHAR_INS_PETITION,
    CHAR_DEL_PETITION_BY_GUID,
    CHAR_DEL_PETITION_SIGNATURE_BY_GUID,
    CHAR_DEL_PET_AURAS,
    CHAR_DEL_PET_AURAS_EFFECTS,
    CHAR_DEL_PET_SPELLS,
    CHAR_DEL_PET_SPELL_COOLDOWNS,
    CHAR_INS_PET_SPELL_COOLDOWN,
    CHAR_DEL_PET_SPELL_BY_SPELL,
    CHAR_INS_PET_SPELL,
    CHAR_INS_PET_AURA,
    CHAR_INS_PET_AURA_EFFECT,
    CHAR_DEL_CHAR_DECLINED_NAME,
    CHAR_INS_CHAR_DECLINED_NAME,
    CHAR_UPD_FACTION_OR_RACE,
    CHAR_UPD_FACTION_OR_RACE_LOG,
    CHAR_DEL_CHAR_SKILL_LANGUAGES,
    CHAR_INS_CHAR_SKILL_LANGUAGE,
    CHAR_UPD_CHAR_TAXI_PATH,
    CHAR_UPD_CHAR_TAXIMASK,
    CHAR_DEL_CHAR_QUESTSTATUS,
    CHAR_DEL_CHAR_QUESTSTATUS_OBJECTIVES,
    CHAR_DEL_CHAR_SOCIAL_BY_GUID,
    CHAR_DEL_CHAR_SOCIAL_BY_FRIEND,
    CHAR_DEL_CHAR_ACHIEVEMENT_BY_ACHIEVEMENT,
    CHAR_UPD_CHAR_ACHIEVEMENT,
    CHAR_UPD_CHAR_INVENTORY_FACTION_CHANGE,
    CHAR_DEL_CHAR_SPELL_BY_SPELL,
    CHAR_UPD_CHAR_SPELL_FACTION_CHANGE,
    CHAR_DEL_CHAR_REP_BY_FACTION,
    CHAR_UPD_CHAR_REP_FACTION_CHANGE,
    CHAR_UPD_CHAR_REP_STANDING_CHANGE,
    CHAR_UPD_CHAR_REP_FLAGS_CHANGE,
    CHAR_UPD_CHAR_TITLES_FACTION_CHANGE,
    CHAR_RES_CHAR_TITLES_FACTION_CHANGE,
    CHAR_DEL_CHAR_SPELL_COOLDOWN,
    CHAR_DEL_CHARACTER,
    CHAR_DEL_CHAR_ACTION,
    CHAR_DEL_CHAR_AURA,
    CHAR_DEL_CHAR_AURA_EFFECT,
    CHAR_DEL_CHAR_GIFT,
    CHAR_DEL_CHAR_INSTANCE,
    CHAR_DEL_CHAR_INVENTORY,
    CHAR_DEL_CHAR_QUESTSTATUS_REWARDED,
    CHAR_DEL_CHAR_REPUTATION,
    CHAR_DEL_CHAR_SPELL,
    CHAR_DEL_MAIL,
    CHAR_DEL_MAIL_ITEMS,
    CHAR_DEL_CHAR_PET_BY_OWNER,
    CHAR_DEL_CHAR_PET_DECLINEDNAME_BY_OWNER,
    CHAR_DEL_CHAR_ACHIEVEMENTS,
    CHAR_DEL_CHAR_EQUIPMENTSETS,
    CHAR_DEL_GUILD_EVENTLOG_BY_PLAYER,
    CHAR_DEL_GUILD_BANK_EVENTLOG_BY_PLAYER,
    CHAR_DEL_CHAR_GLYPHS,
    CHAR_DEL_CHAR_QUESTSTATUS_DAILY,
    CHAR_DEL_CHAR_TALENT,
    CHAR_DEL_CHAR_TALENT_PVP,
    CHAR_DEL_CHAR_SKILLS,
    CHAR_UDP_CHAR_MONEY,
    CHAR_INS_CHAR_ACTION,
    CHAR_UPD_CHAR_ACTION,
    CHAR_DEL_CHAR_ACTION_BY_BUTTON_SPEC,
    CHAR_DEL_CHAR_INVENTORY_BY_ITEM,
    CHAR_DEL_CHAR_INVENTORY_BY_BAG_SLOT,
    CHAR_UPD_MAIL,
    CHAR_REP_CHAR_QUESTSTATUS,
    CHAR_DEL_CHAR_QUESTSTATUS_BY_QUEST,
    CHAR_REP_CHAR_QUESTSTATUS_OBJECTIVES,
    CHAR_DEL_CHAR_QUESTSTATUS_OBJECTIVES_BY_QUEST,
    CHAR_DEL_ACC_QUESTSTATUS_BY_QUEST,
    CHAR_DEL_ACC_QUESTSTATUS_OBJECTIVES_BY_QUEST,
    CHAR_INS_CHAR_QUESTSTATUS,
    CHAR_DEL_CHAR_QUESTSTATUS_REWARDED_BY_QUEST,
    CHAR_DEL_ACC_QUESTSTATUS_REWARDED_BY_QUEST,
    CHAR_DEL_CHAR_SKILL_BY_SKILL,
    CHAR_INS_CHAR_SKILLS,
    CHAR_UDP_CHAR_SKILLS,
    CHAR_INS_CHAR_SPELL,
    CHAR_DEL_PETITION_BY_OWNER,
    CHAR_DEL_PETITION_SIGNATURE_BY_OWNER,
    CHAR_INS_CHAR_GLYPHS,
    CHAR_DEL_CHAR_TALENT_BY_SPELL_SPEC,
    CHAR_INS_CHAR_TALENT,
    CHAR_DEL_CHAR_ACTION_EXCEPT_SPEC,
    CHAR_UPD_CHAR_LIST_SLOT,
    CHAR_DEL_CHAR_TALENT_PVP_BY_SPELL_SPEC,
    CHAR_INS_CHAR_TALENT_PVP,

    CHAR_SEL_CHAR_VOID_STORAGE,
    CHAR_SEL_CHAR_VOID_STORAGE_ITEM,
    CHAR_REP_CHAR_VOID_STORAGE_ITEM,
    CHAR_DEL_CHAR_VOID_STORAGE_ITEM_BY_SLOT,
    CHAR_DEL_CHAR_VOID_STORAGE_ITEM,

    CHAR_REP_GUILD_FINDER_APPLICANT,
    CHAR_DEL_GUILD_FINDER_APPLICANT,
    CHAR_REP_GUILD_FINDER_GUILD_SETTINGS,
    CHAR_DEL_GUILD_FINDER_GUILD_SETTINGS,

    CHAR_INS_CHALLENGE,
    CHAR_INS_CHALLENGE_MEMBER,
    CHAR_DEL_CHALLENGE_MEMBER,
    CHAR_INS_CHALLENGE_OPLOTE_LOOT,
    CHAR_DEL_CHALLENGE_OPLOTE_LOOT,
    CHAR_DEL_CHALLENGE_OPLOTE_LOOT_BY_GUID,

    CHAR_SEL_CUF_PROFILES,
    CHAR_REP_CUF_PROFILES,

    CHAR_SEL_PETBATTLE_ACCOUNT,
    CHAR_REP_PETBATTLE,
    CHAR_INS_PETBATTLE,
    CHAR_DEL_PETBATTLE,

    CHAR_SEL_PERSONAL_RATE,
    CHAR_SEL_PLAYER_VISUAL,
    CHAR_SEL_MAILBOX_QUEUE,
    CHAR_DEL_MAILBOX_QUEUE,

    CHAR_ADD_ITEM_DONATE,
    CHAR_ITEM_DONATE_SET_STATE,

    CHAR_SEL_PLAYER_KILL,
    CHAR_DEL_PLAYER_KILL,
    CHAR_REP_PLAYER_KILL,
    CHAR_UPD_PLAYER_KILL,

    CHAR_SEL_HONOR_INFO,
    CHAR_UPD_HONOR_INFO_HONOR,
    CHAR_UPD_HONOR_INFO_HONOR_LEVEL,
    CHAR_UPD_HONOR_INFO_PRESTIGE_LEVEL,
    CHAR_REP_HONOR_INFO,

    CHAR_SEL_PLAYER_LOOTCOOLDOWN,
    CHAR_INS_PLAYER_LOOTCOOLDOWN,
    CHAR_SEL_PLAYER_LFGCOOLDOWN,
    CHAR_INS_PLAYER_LFGCOOLDOWN,

    CHAR_SEL_LAST_CHAR_UNDELETE,
    CHAR_UPD_LAST_CHAR_UNDELETE,
    CHAR_UPD_RESTORE_DELETE_INFO,

    CHAR_SEL_BLACKMARKET_AUCTIONS,
    CHAR_DEL_BLACKMARKET_AUCTIONS,
    CHAR_UPD_BLACKMARKET_AUCTIONS,
    CHAR_INS_BLACKMARKET_AUCTIONS,

    CHAR_REP_CALENDAR_EVENT,
    CHAR_DEL_CALENDAR_EVENT,
    CHAR_REP_CALENDAR_INVITE,
    CHAR_DEL_CALENDAR_INVITE,

    CHAR_SEL_CHARACTER_GARRISON,
    CHAR_INS_CHARACTER_GARRISON,
    CHAR_UPD_CHARACTER_GARRISON,
    CHAR_DEL_CHARACTER_GARRISON,
    CHAR_DEL_CHARACTER_GARRISON_ONLY,
    CHAR_DEL_CHARACTER_GARRISON_BY_SITE,

    CHAR_UPD_CHARACTER_GARRISON_FOLLOWER_ACTIVATIONS,

    CHAR_SEL_CHARACTER_GARRISON_BLUEPRINTS,
    CHAR_INS_CHARACTER_GARRISON_BLUEPRINTS,
    CHAR_DEL_CHARACTER_GARRISON_BLUEPRINTS,
    CHAR_DEL_CHARACTER_GARRISON_BLUEPRINTS_BY_BUILD,

    CHAR_SEL_CHARACTER_GARRISON_BUILDINGS,
    CHAR_INS_CHARACTER_GARRISON_BUILDINGS,
    CHAR_DEL_CHARACTER_GARRISON_BUILDINGS,
    CHAR_DEL_CHARACTER_GARRISON_BUILDINGS_BY_PLOT,

    CHAR_SEL_CHARACTER_GARRISON_FOLLOWERS,
    CHAR_INS_CHARACTER_GARRISON_FOLLOWERS,
    CHAR_DEL_CHARACTER_GARRISON_FOLLOWERS,
    CHAR_DEL_CHARACTER_GARRISON_FOLLOWER,
    CHAR_DEL_CHARACTER_GARRISON_FOLLOWER_BY_DBID,

    CHAR_SEL_CHARACTER_GARRISON_FOLLOWER_ABILITIES,
    CHAR_INS_CHARACTER_GARRISON_FOLLOWER_ABILITIES,
    CHAR_DEL_CHARACTER_GARRISON_FOLLOWER_ABILITIES,

    CHAR_SEL_CHARACTER_GARRISON_MISSIONS,
    CHAR_INS_CHARACTER_GARRISON_MISSIONS,
    CHAR_DEL_CHARACTER_GARRISON_MISSIONS,
    CHAR_DEL_CHARACTER_GARRISON_MISSIONS_DB_ID,

    CHAR_SEL_CHARACTER_GARRISON_SHIPMENTS,
    CHAR_INS_CHARACTER_GARRISON_SHIPMENTS,
    CHAR_DEL_CHARACTER_GARRISON_SHIPMENTS,
    CHAR_DEL_CHARACTER_GARRISON_SHIPMENTS_DBID,
    CHAR_DEL_CHARACTER_GARRISON_SHIPMENTS_BY_DB_ID,

    CHAR_SEL_CHARACTER_GARRISON_TALENTS,
    CHAR_INS_CHARACTER_GARRISON_TALENTS,
    CHAR_DEL_CHARACTER_GARRISON_TALENTS,
    CHAR_DEL_CHARACTER_GARRISON_TALENT_BY_ID,

    CHAR_SEL_TOYS,
    CHAR_REP_TOYS,

    CHAR_SEL_HEIRLOOMS,
    CHAR_REP_HEIRLOOMS,

    CHAR_SEL_CHARACTER_COMPLAINTS,
    CHAR_INS_CHARACTER_COMPLAINTS,

    CHAR_SEL_TRANSMOGS,
    CHAR_REP_TRANSMOGS,
    CHAR_DEL_TRANSMOG,
    CHAR_SEL_BNET_ITEM_FAVORITE_APPEARANCES,
    CHAR_INS_BNET_ITEM_FAVORITE_APPEARANCE,
    CHAR_DEL_BNET_ITEM_FAVORITE_APPEARANCE,

    CHAR_SEL_ITEM_INSTANCE_ARTIFACT,
    CHAR_REP_ITEM_INSTANCE_ARTIFACT,
    CHAR_DEL_ITEM_INSTANCE_ARTIFACT,
    CHAR_DEL_ITEM_INSTANCE_ARTIFACT_BY_OWNER,
    CHAR_SEL_ITEM_INSTANCE_ARTIFACT_XP,

    CHAR_SEL_ITEM_INSTANCE_ARTIFACT_POWERS,
    CHAR_REP_ITEM_INSTANCE_ARTIFACT_POWERS,
    CHAR_DEL_ITEM_INSTANCE_ARTIFACT_POWERS,
    CHAR_DEL_ITEM_INSTANCE_ARTIFACT_POWERS_BY_OWNER,
    CHAR_INS_ITEM_INSTANCE_MODIFIERS,
    CHAR_DEL_ITEM_INSTANCE_MODIFIERS,
    CHAR_DEL_ITEM_INSTANCE_MODIFIERS_BY_OWNER,
    CHAR_REP_ITEM_INSTANCE_RELICS,
    CHAR_DEL_ITEM_INSTANCE_RELICS,
    CHAR_SEL_ITEM_INSTANCE_RELICS,

    CHAR_SEL_MOUNTS,
    CHAR_REP_MOUNTS,

    CHAR_SEL_CHARACTER_ADVENTURE_QUEST,
    CHAR_DEL_CHARACTER_ADVENTURE_QUEST,
    CHAR_REP_CHARACTER_ADVENTURE_QUEST,

    CHAR_REP_WORLD_QUEST,
    CHAR_DEL_WORLD_QUEST_BY_ID,
    CHAR_DEL_WORLD_QUEST_BY_TIMER,

    CHAR_SEL_CHARACTER_WORLDQUESTSTATUS,
    CHAR_INS_CHARACTER_WORLDQUESTSTATUS,
    CHAR_DEL_QUEST_STATUS_WORLD,

    CHAR_DEL_WORLD_STATE_BY_STATE_INSTANCE,
    CHAR_INS_WORLD_STAT,

    CHAR_SEL_CHALLENGE_KEY,
    CHAR_UPD_CHALLENGE_KEY,
    CHAR_INS_CHALLENGE_KEY,
    CHAR_DEL_CHALLENGE_KEY,

    CHAR_SEL_PLAYER_DEATHMATCH,
    CHAR_REP_PLAYER_DEATHMATCH,

    CHAR_SEL_PLAYER_DEATHMATCH_STORE,
    CHAR_REP_PLAYER_DEATHMATCH_STORE,

    CHAR_SEL_PLAYER_CHAT_LOGOS,
    CHAR_REP_PLAYER_CHAT_LOGOS,

    CHAR_SEL_ARMY_TRAINING_INFO,
    CHAR_REP_ARMY_TRAINING_INFO,

    CHAR_SEL_ACCOUNT_PROGRESS,
    CHAR_REP_ACCOUNT_PROGRESS,

    CHAR_REP_BAD_SENTENCES,
    CHAR_UPD_BAD_SENTENCES,

    CHAR_UPD_WEEKLY_BRACKET,

    CHAR_DEL_WARDEN_BAN_ATTEMPTS,
    CHAR_INS_WARDEN_BAN_ATTEMPTS,
    CHAR_SEL_WARDEN_BAN_ATTEMPTS,
    CHAR_UPD_WARDEN_BAN_ATTEMPTS,

    CHAR_SEL_ACCOUNT_FLAGGED,
    CHAR_SEL_ACCOUNT_FLAGGED_ALL,
    CHAR_DEL_ACCOUNT_FLAGGED,
    CHAR_INS_ACCOUNT_FLAGGED,

    CHAR_INS_BOT_ACCOUNT,

    CHAR_SEL_KILL_CREATURE,
    CHAR_INS_KILL_CREATURE,
    CHAR_UPD_KILL_CREATURE,

    CHAR_SEL_NUM_ACCOUNT_CHARS_REACHED_LEVEL,

    MAX_CHARACTERDATABASE_STATEMENTS
};

class TC_DATABASE_API CharacterDatabaseConnection : public MySQLConnection
{
public:
    typedef CharacterDatabaseStatements Statements;

    CharacterDatabaseConnection(MySQLConnectionInfo& connInfo, ConnectionFlags connectionFlags);
    ~CharacterDatabaseConnection();

    //- Loads database type specific prepared statements
    void DoPrepareStatements() override;
};

#endif
