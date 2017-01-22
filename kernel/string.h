#ifndef __STRING_H__
#define __STRING_H__

#include <stdarg.h>
#include "global.h"
#include "common.h"
#include "vsprintf.h"

#ifdef __cplusplus
extern "C" {
#endif
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, size_t);
size_t strlcpy(char *dest, const char *src, size_t maxlen);
char *strstr(const char *str1, const char *str2);
int strcmp(const char *, const char *);
int strncmp(const char *p, const char *q, size_t n);
size_t strlen(const char *);
size_t strnlen(const char *, size_t);
char *strchr(const char *s, int c);
int memcmp(const void *s1, const void *s2, size_t n);
void *memset(void *dst, int x, size_t n);
extern void memcpy(void *dst, const void *src, u32 size);
void* memchr(const void* ptr, int ch, size_t count);
#ifdef __cplusplus
//Not implemented, just makes compiler happy
void* memmove( void* dest, const void* src, size_t count );
char *strcat( char *dest, const char *src );
int strcoll( const char *lhs, const char *rhs );
size_t strcspn( const char *dest, const char *src );
char* strerror( int errnum );
char *strncat( char *dest, const char *src, size_t count );
size_t strspn( const char *dest, const char *src );
char *strtok( char *str, const char *delim );
size_t strxfrm( char *dest, const char *src, size_t count );
char* strpbrk( const char* dest, const char* breakset );
char *strrchr( const char *str, int ch );
float strtof( const char * str, char ** str_end );
long double strtold( const char * str, char ** str_end );
}
#endif

#ifdef __cplusplus
#include <string>
namespace std {
  template<typename T>
  inline std::string to_string(T val) {
    return "FIXME 1824679";
  }

  using ::strtof;
  using ::strtold;
  int       stoi( const std::string& str, std::size_t* pos = 0, int base = 10 );
}
#endif

int _sprintf( char *buf, const char *fmt, ... );

#ifdef DEBUG
void hexdump(void *d, int len);
#else
#define hexdump(...)
#endif

#endif
