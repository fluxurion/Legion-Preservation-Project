/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef _GAMEOBJECT_MODEL_H
#define _GAMEOBJECT_MODEL_H

#include <G3D/Matrix3.h>
#include <G3D/Vector3.h>
#include <G3D/AABox.h>
#include <G3D/Ray.h>

#include "Define.h"
#include <memory>

namespace VMAP
{
    class WorldModel;
    struct AreaInfo;
    enum class ModelIgnoreFlags : uint32;
}

class GameObject;
struct GameObjectDisplayInfoEntry;

class TC_COMMON_API GameObjectModelOwnerBase
{
public:
    virtual ~GameObjectModelOwnerBase() = default;

    virtual bool IsSpawned() const = 0;
    virtual uint32 GetDisplayId() const = 0;
    virtual uint8 GetNameSetId() const = 0;
    virtual bool IsDoor() const { return false; }
    virtual uint32 GetPhaseMask() const { return 0; }
    virtual bool InSamePhaseId(std::set<uint32> const& /*phases*/, bool /*otherUsePlayerPhasingRules*/) const { return false; }
    virtual G3D::Vector3 GetPosition() const = 0;
    virtual float GetOrientation() const = 0;
    virtual float GetScale() const = 0;
    virtual void DebugVisualizeCorner(G3D::Vector3 const& /*corner*/) const = 0;
    virtual GameObject const* GetOwner() const { return nullptr; }
    virtual uint32 GetGUIDLow() const { return 0; }
};

class TC_COMMON_API GameObjectModel /*, public Intersectable*/
{
    GameObjectModel() : _collisionEnabled(false), iInvScale(0), iScale(0), iModel(nullptr), isWmo(false) { }
public:
    std::string name;

    const G3D::AABox& getBounds() const { return iBound; }

    ~GameObjectModel();

    const G3D::Vector3& getPosition() const { return iPos;}

    /* Enables/disables collision */
    void enableCollision(bool enable) { _collisionEnabled = enable; }
    bool isCollisionEnabled() const { return _collisionEnabled; }
    bool isMapObject() const { return isWmo; }

    bool intersectRay(G3D::Ray const& ray, float& maxDist, bool stopAtFirstHit,  std::set<uint32> const& phases, bool otherUsePlayerPhasingRules, VMAP::ModelIgnoreFlags ignoreFlags) const;
    void intersectPoint(G3D::Vector3 const& point, VMAP::AreaInfo& info,  std::set<uint32> const& phases, bool otherUsePlayerPhasingRules) const;

    bool isInLineOfSight(G3D::Vector3 const& startPos, G3D::Vector3 const& endPos, std::set<uint32> const& phases, bool otherUsePlayerPhasingRules) const;
    bool getObjectHitPos(std::set<uint32> const& phases, bool otherUsePlayerPhasingRules, G3D::Vector3 const& startPos, G3D::Vector3 const& endPos, G3D::Vector3& resultHitPos, float modifyDist) const;
    float getHeight(float x, float y, float z, float maxSearchDist, std::set<uint32> const& phases, bool otherUsePlayerPhasingRules) const;

    static GameObjectModel* Create(std::unique_ptr<GameObjectModelOwnerBase> modelOwner, std::string const& dataPath);

    bool UpdatePosition();
    std::unique_ptr<GameObjectModelOwnerBase> owner;

private:
    bool initialize(std::unique_ptr<GameObjectModelOwnerBase> modelOwner, std::string const& dataPath);

    bool _collisionEnabled;
    G3D::AABox iBound;
    G3D::Matrix3 iInvRot;
    G3D::Vector3 iPos;
    float iInvScale;
    float iScale;
    VMAP::WorldModel* iModel;
    bool isWmo;
};

TC_COMMON_API void LoadGameObjectModelList(std::string const& dataPath);

#endif // _GAMEOBJECT_MODEL_H