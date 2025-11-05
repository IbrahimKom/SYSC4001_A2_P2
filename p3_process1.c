#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        execl("./p3_process2", "p3_process2", (char*)NULL);
        perror("execl"); return 1;
    }

    // parent will count up multiples of 3 while child runs
    int x = 0, cycles = 0;
    while (1) {
        int status; pid_t r = waitpid(pid, &status, WNOHANG);
        if (r == pid) break; // child finished (< -500)
        if (x % 3 == 0) printf("[parent] cycle=%d  %d is a multiple of 3\n", cycles, x);
        x++; cycles++;
        usleep(150000);
    }
    printf("[parent] child done; exiting too.\n");
    return 0;
}
