//
// Created by pwootage on 8/19/16.
//

#ifndef NINTENDONT_PRIMEMEMORYDUMPING_H
#define NINTENDONT_PRIMEMEMORYDUMPING_H

#include <memory>
#include <string>
#include "string.h"
#include "global.h"
#include "common.h"
#include "alloc.h"
//#include "PrimeMemoryDumping/prime1/Prime1JsonDumper.hpp"

#define PACKET_TYPE_GAME_DATA (0x1)
#define PACKET_TYPE_RAW_DISC_READ (0x2)
#define PACKET_TYPE_INVALID (0xFF)
#define INVENTORY_SIZE (0x29)

std::string primeMemoryDump();
float readFloatFromGCMemory(u32 addr);
u64 read64FromGCMemory(u32 addr);
u32 read32FromGCMemory(u32 addr);
u16 read16FromGCMemory(u32 addr);
u8 read8FromGCMemory(u32 addr);

#endif //NINTENDONT_PRIMEMEMORYDUMPING_H
