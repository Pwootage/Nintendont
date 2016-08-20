//
// Created by pwootage on 8/19/16.
//

#include "PrimeMemoryDumping.h"

#define GET_PTR(value) (P2C(value))
#define MEM_HIGH (0x2400000)
#define INVALID_PTR(value) (value) > MEM_HIGH

#define PRIME_1_GAMEID (0x474D3845)
#define PRIME_1_MAKERID (0x3031)

void primeMemoryDump(PrimeMemoryDump *dest) {
  u32 gameID = read32FromGCMemory(0x00);
  u16 makerID = read16FromGCMemory(0x04);
//  u32 gameID = PRIME_1_GAMEID;
//  u16 makerID = PRIME_1_MAKERID;

  dest->gameid = gameID;
  dest->makerid = makerID;
  dest->type = PACKET_TYPE_RAW_DISC_INVALID;

  if (gameID == PRIME_1_GAMEID && makerID == PRIME_1_MAKERID) {
    u32 playerStatusPtr = read32FromGCMemory(0x4578CC);

    dest->type = PACKET_TYPE_GAME_DATA;
    dest->speed[0] = read32FromGCMemory(0x46BAB4);
    dest->speed[1] = read32FromGCMemory(0x46BAB8);
    dest->speed[2] = read32FromGCMemory(0x46BABC);
    dest->pos[0] = read32FromGCMemory(0x46B9BC);
    dest->pos[1] = read32FromGCMemory(0x46B9CC);
    dest->pos[2] = read32FromGCMemory(0x46B9DC);
    dest->room = read32FromGCMemory(0x45AA74);
    dest->health = read32FromGCMemory(playerStatusPtr + 0x2AC);
    u32 i;
    for (i = 0; i < INVENTORY_SIZE; i++) {
      dest->inventory[i] = read32FromGCMemory(playerStatusPtr + 0x2C8 + i * 4);
    }
    dest->timer = read64FromGCMemory(playerStatusPtr + 0xA0);
  }
};

u64 read64FromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  u64 res = ((u64)read32(GET_PTR(actualPtr)) << 32) | (u64)read32(GET_PTR(actualPtr + 4));
  return res;
}

u32 read32FromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  u32 res = read32(GET_PTR(actualPtr));
  return res;
}

u16 read16FromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  u16 res = read16(GET_PTR(actualPtr));
  return res;
}

u8 read8FromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  u8 res = read8(GET_PTR(actualPtr));
  return res;
}