#include <pthread.h>
#include <printf.h>
#include "maxrun.jhenry3.h"

int main(int argc, char *argv[]) {
    int rc, numChars;
    if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }
    rc = readFile(argv[1], &numChars);
    if (rc != 0)
        return 8;

    // Sets up structs for 4 threads. WARNING: does not work if NUM_THREADS is not 4
    int interval = numChars / NUM_THREADS;
    SearchInfo structs[NUM_THREADS];

    // Initialize structs with default values
    for (int i = 0; i < NUM_THREADS; ++i) {
        structs[i].maxRunChar = ' ';
        structs[i].maxRunLength = 0;
    }

    // Give each struct the intervals it will be scanning
    structs[0].startIndex = 0;
    structs[0].endIndex = interval + MARGIN;

    structs[1].startIndex = interval - MARGIN;
    structs[1].endIndex = 2 * interval + MARGIN;

    structs[2].startIndex = 2 * interval - MARGIN;
    structs[2].endIndex = 3 * interval + MARGIN;

    structs[3].startIndex = 3 * interval - MARGIN;
    structs[3].endIndex = numChars - 1;

    // Creates the 4 threads and runs them
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, searchFunction, &structs[i]);
    }

    // Wait for the child threads to terminate
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    // Compares all the structs and determines the longest run of characters
    int highestLength = 0;
    char longestChar = ' ';
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (structs[i].maxRunLength > highestLength) {
            highestLength = structs[i].maxRunLength;
            longestChar = structs[i].maxRunChar;
        }
    }

    printf("longest run = %d, char = %c\n", highestLength, longestChar);


    return 0;
}