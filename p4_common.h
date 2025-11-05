#ifndef P4_COMMON_H
#define P4_COMMON_H
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_KEY 0x12345

typedef struct {
    int multiple;
    int counter;
} shmvars_t;

#endif
