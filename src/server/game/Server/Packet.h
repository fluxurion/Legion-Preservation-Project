/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#ifndef PacketBaseWorld_h__
#define PacketBaseWorld_h__

#include "WorldPacket.h"

namespace WorldPackets
{
    class TC_GAME_API Packet
    {
    public:
        Packet(WorldPacket&& worldPacket);

        virtual ~Packet() = default;

        Packet(Packet const& right) = delete;
        Packet& operator=(Packet const& right) = delete;

        virtual WorldPacket const* Write() = 0;
        virtual void Read() = 0;

        WorldPacket const* GetRawPacket() const;
        size_t GetSize() const;
        ConnectionType GetConnection() const;

    protected:
        WorldPacket _worldPacket;
    };

    class TC_GAME_API ServerPacket : public Packet
    {
    public:
        ServerPacket(OpcodeServer opcode, size_t initialSize = 200, ConnectionType connection = CONNECTION_TYPE_DEFAULT);

        void Read() override final;

        void Clear();
        WorldPacket&& Move();
        OpcodeServer GetOpcode() const;
    };

    class TC_GAME_API ClientPacket : public Packet
    {
    public:
        ClientPacket(WorldPacket&& packet);
        ClientPacket(OpcodeClient expectedOpcode, WorldPacket&& packet);

        WorldPacket const* Write() override final;
        OpcodeClient GetOpcode() const;
    };
}

#endif // PacketBaseWorld_h__
