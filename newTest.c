#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator using the current time
    srand(time(NULL));

    printf("5 Random Numbers:\n");
    for (int i = 0; i < 5; i++) {
        // Generates a random integer
        printf("%d\n", rand());
    }

    return 0;
}
