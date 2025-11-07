#include <stdio.h>
#include <unistd.h>

int main(void) {
    int y = 0, cycles = 0;
    while (y > -500) {
        if (y % 3 == 0) printf("[child ] cycle=%d  %d is a multiple of 3\n", cycles, y);
        y--;
        cycles++;
        usleep(150000);
    }
    printf("[child ] reached < -500, exiting.\n");
    return 0;// parent will detect this via wait()
}
