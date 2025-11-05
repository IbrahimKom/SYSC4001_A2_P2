#include "p5_common_101308485.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(void) {
    int shmid = shmget(SHM_KEY, sizeof(shmvars_t), IPC_CREAT | 0666);
    if (shmid < 0) { perror("shmget"); return 1; }
    shmvars_t *sv = (shmvars_t*) shmat(shmid, NULL, 0);
    if (sv == (void*)-1) { perror("shmat"); return 1; }

    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid < 0) { perror("semget"); return 1; }
    //initialize binary semaphore to 1 
    semctl(semid, 0, SETVAL, 1);

    sem_P(semid);
    sv->multiple = 3;
    sv->counter  = 0;
    sem_V(semid);

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        execl("./p5_process2_101308485", "p5_process2_101308485", (char*)NULL);
        perror("execl"); return 1;
    }

    // parent increments counter
    while (1) {
        sem_P(semid);
        int m = sv->multiple;
        int c = sv->counter;
        if (c % m == 0) printf("[parent] counter=%d is multiple of %d\n", c, m);
        sv->counter = c + 1;
        int done = (sv->counter > 500);
        sem_V(semid);
        if (done) break;
        usleep(70000);
    }

    int status; waitpid(pid, &status, 0);
    shmdt(sv);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);// remove semaphore set
    return 0;
}
