#ifndef __ALLOC_H__
#define __ALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif
void *malloc( u32 size );
void *malloca( u32 size, u32 align );
void free( void *ptr );
#ifdef __cplusplus
};
#endif

#endif