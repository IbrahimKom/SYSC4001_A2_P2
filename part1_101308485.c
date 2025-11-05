#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();// Create a new process 

    if (pid < 0) {
        // fork() failed
        printf("Error: fork failed.\n");
        return 1;
    }
    else if (pid == 0) {
        // child process
        int child_counter = 0;
        while (1) {
            printf("Child Process: counter = %d\n", child_counter);
            child_counter++;
            usleep(300000); // Pause for 0.3 sec so we can read output
        }
    }
    else {
        // parent process
        int parent_counter = 0;
        while (1) {
            printf("Parent Process: counter = %d\n", parent_counter);
            parent_counter++;
            usleep(300000);
        }
    }

    return 0;
}
