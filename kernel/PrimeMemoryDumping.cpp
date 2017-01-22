//
// Created by pwootage on 8/19/16.
//

#include "PrimeMemoryDumping.h"
#include "PrimeMemoryDumping/prime1/CGameGlobalObjects.hpp"
#include "string.h"

#define GET_PTR(value) (P2C(value))
#define MEM_HIGH (0x2400000)
#define INVALID_PTR(value) (value) > MEM_HIGH

#define PRIME_1_GAMEID (0x474D3845)
#define PRIME_1_MAKERID (0x3031)

using namespace std;

string primeMemoryDump() {
  u32 gameID = read32FromGCMemory(0x00);
  u16 makerID = read16FromGCMemory(0x04);

//  json json_message;

  u32 count = 0;
  if (gameID == PRIME_1_GAMEID && makerID == PRIME_1_MAKERID) {
    CGameGlobalObjects global(CGameGlobalObjects::LOCATION);
    count = global.mainPool.resources.size.read();
    //        json_message["heap"] = Prime1JsonDumper::parseHeap();
//    json_message["camera"] = Prime1JsonDumper::parseCamera();
//        json_message["player"] = Prime1JsonDumper::parsePlayer();
//    json_message["player_raw"] = Prime1JsonDumper::parsePlayerRaw();
//    json_message["world"] = Prime1JsonDumper::parseWorld();
//    json_message["pool_summary"] = Prime1JsonDumper::parsePoolSummary();
  }

//  char buff[32];
//  _sprintf(buff, "%lu", count);
  return string("{\"pool_summary\":{\"count\":1}}");
};

float readFloatFromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  union {
      u32 i;
      float f;
  };
  i = read32(GET_PTR(actualPtr));
  return f;
}

float readDoubleFromGCMemory(u32 addr) {
  union {
      u64 i;
      double f;
  };
  i = read64FromGCMemory(addr);
  return f;
}

u64 read64FromGCMemory(u32 addr) {
  u32 actualPtr = P2C(addr);
  if (INVALID_PTR(actualPtr)) {
    return 0;
  }
  u64 res = ((u64) read32(GET_PTR(actualPtr)) << 32) | (u64) read32(GET_PTR(actualPtr + 4));
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

namespace GameMemory {
    std::uint32_t read_u32(std::uint32_t address) {
      return read32FromGCMemory(address);
    }
    std::uint64_t read_u64(std::uint32_t address) {
      return read64FromGCMemory(address);
    }
    float read_float(std::uint32_t address) {
      return readFloatFromGCMemory(address);
    }
    double read_double(std::uint32_t address) {
      return readDoubleFromGCMemory(address);
    }
}

extern "C" {

struct _reent *
_DEFUN_VOID(__getreent)
{
  return _impure_ptr;
}

}