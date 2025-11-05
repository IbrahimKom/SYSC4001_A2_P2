#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        // fork error
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // child replace this process image with process2
        execl("./process2", "process2", (char *)NULL);

        // if execl returns, it failed
        perror("execl");
        return 1;
    }
    else {
        // parent count UP, print multiples of 3 up to 60
        int x = 0;
        while (x <= 60) {
            if (x % 3 == 0) {
                printf("[parent] %d is a multiple of 3\n", x);
            }
            x++;
            usleep(200000); // 0.2s to make output readable
        }
        printf("[parent] done.\n");
    }

    return 0;
}
