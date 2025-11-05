#include <stdio.h>
#include <unistd.h>

int main(void) {
    int y = 0;
    while (y >= -60) {
        if (y % 3 == 0) {
            printf("[child ] %d is a multiple of 3\n", y);
        }
        y--;
        usleep(200000); // 0.2s for readable interleave
    }
    printf("[child ] done.\n");
    return 0;
}
