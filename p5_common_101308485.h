#ifndef P5_COMMON_H
#define P5_COMMON_H
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY  0x12345
#define SEM_KEY  0x54321

typedef struct { int multiple; int counter; } shmvars_t;

static int sem_P(int semid) { struct sembuf op = {0, -1, 0}; return semop(semid, &op, 1); }
static int sem_V(int semid) { struct sembuf op = {0, +1, 0}; return semop(semid, &op, 1); }

#endif
