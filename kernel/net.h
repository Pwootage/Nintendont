
#ifndef _NET_H_
#define _NET_H_

#ifdef __cplusplus
extern "C" {
#endif

void NetInit();
u32 NetThread(void *arg);

#ifdef __cplusplus
};
#endif

#endif
