#include "p4_common_101308485.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int shmid = shmget(SHM_KEY, sizeof(shmvars_t), 0666);
    if (shmid < 0) { perror("shmget(child)"); return 1; }
    shmvars_t *sv = (shmvars_t*) shmat(shmid, NULL, 0);
    if (sv == (void*)-1) { perror("shmat(child)"); return 1; }

    // wait until counter > 100
    while (sv->counter <= 100) usleep(50000);

    // react to shared variables until counter > 500
    int last_seen = -1;
    while (sv->counter <= 500) {
        int c = sv->counter;
        if (c != last_seen && c % sv->multiple == 0) {
            printf("[child ] shared counter=%d is multiple of %d\n", c, sv->multiple);
            last_seen = c;
        }
        usleep(80000);
    }

    printf("[child ] counter > 500; exiting.\n");
    shmdt(sv);
    return 0;
}
