#include "p4_common_101308485.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char **argv) {
    int shmid = shmget(SHM_KEY, sizeof(shmvars_t), IPC_CREAT | 0666);
    if (shmid < 0) { perror("shmget(parent)"); return 1; }
    shmvars_t *sv = (shmvars_t*) shmat(shmid, NULL, 0);
    if (sv == (void*)-1) { perror("shmat(parent)"); return 1; }

    sv->multiple = 3;        
    sv->counter  = 0;

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        execl("./p4_process2_101308485", "p4_process2_101308485", (char*)NULL);
        perror("execl"); return 1;
    }

    // parent drives the counter until > 500
    while (sv->counter <= 500) {
        if (sv->counter % sv->multiple == 0)
            printf("[parent] shared counter=%d is multiple of %d\n", sv->counter, sv->multiple);
        sv->counter++;
        usleep(70000);
    }
    printf("[parent] counter > 500; waiting child and cleaning up.\n");

    int status; waitpid(pid, &status, 0);
    shmdt(sv);
    shmctl(shmid, IPC_RMID, NULL);// remove segment
    return 0;
}
