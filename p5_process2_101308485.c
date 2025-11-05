#include "p5_common.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int shmid = shmget(SHM_KEY, sizeof(shmvars_t), 0666);
    if (shmid < 0) { perror("shmget(child)"); return 1; }
    shmvars_t *sv = (shmvars_t*) shmat(shmid, NULL, 0);
    if (sv == (void*)-1) { perror("shmat(child)"); return 1; }

    int semid = semget(SEM_KEY, 1, 0666);
    if (semid < 0) { perror("semget(child)"); return 1; }

    // wait until counter > 100 
    while (1) {
        sem_P(semid);
        int c = sv->counter;
        sem_V(semid);
        if (c > 100) break;
        usleep(50000);
    }

    int last_seen = -1;
    while (1) {
        sem_P(semid);
        int m = sv->multiple;
        int c = sv->counter;
        sem_V(semid);

        if (c % m == 0 && c != last_seen) {
            printf("[child ] counter=%d is multiple of %d\n", c, m);
            last_seen = c;
        }
        if (c > 500) break;
        usleep(80000);
    }

    shmdt(sv);
    return 0;
}
