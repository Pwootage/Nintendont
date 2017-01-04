//
// Created by pwootage on 1/4/17.
//

#include "global.h"
#include "alloc.h"


void *operator new(size_t count) {
  return malloc(count);
}

void *operator new[](size_t count) {
  return malloc(count);
}

void operator delete(void *ptr) noexcept {
  free(ptr);
}

void operator delete[](void *ptr) noexcept {
  free(ptr);
}