//
// Created by pwootage on 8/19/16.
//

#ifndef NINTENDONT_PRIMEMEMORYDUMPING_H
#define NINTENDONT_PRIMEMEMORYDUMPING_H

#include <memory>
#include "string.h"
#include "global.h"
#include "common.h"
#include "alloc.h"

#define PACKET_TYPE_GAME_DATA (0x1)
#define PACKET_TYPE_RAW_DISC_READ (0x2)
#define PACKET_TYPE_INVALID (0xFF)
#define INVENTORY_SIZE (0x29)

#pragma pack(push,1)
class PrimeMemoryDump {
//    union {
//        struct {
//            u8 type;
//            u32 len;
//            char* data;
//        };
//    };
public:
    u8 type;
    u32 gameid;
    u16 makerid;
    float speed[3];
    float pos[3];
    u32 morphStatus;
    float playerAABB[6];
    float morphedPos[3];
    float morphedRadius;
    u32 worldID;
    u32 worldStatus;
    u32 room;
    u32 health;
    u32 inventory[INVENTORY_SIZE*2];
    u64 timer;
};
#pragma pack(pop)

std::unique_ptr<PrimeMemoryDump> primeMemoryDump();
float readFloatFromGCMemory(u32 addr);
u64 read64FromGCMemory(u32 addr);
u32 read32FromGCMemory(u32 addr);
u16 read16FromGCMemory(u32 addr);
u8 read8FromGCMemory(u32 addr);

#endif //NINTENDONT_PRIMEMEMORYDUMPING_H
