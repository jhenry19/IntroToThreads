#include <printf.h>
#include <pthread.h>
#include <string.h>
#include "maxrun.jhenry3.h"

void *searchFunction(void *param) {
    SearchInfo *data;
    int i;
    int maxLength = 0;
    char maxLengthChar = ' ';

    data = (SearchInfo *) param;

    // Used to count continuous runs of characters
    int currentRunCount = 0;
    char currentRunChar = ' ';

    for (i = data->startIndex; i <= data->endIndex; ++i) {
        if (buffer[i] == currentRunChar) { // if this character is the same as the last
            ++currentRunCount;
        }
        else { // if this character breaks a run of characters
            if (currentRunCount > maxLength) { // if this run was larger than any before
                maxLength = currentRunCount;
                maxLengthChar = currentRunChar;
            }
            // Starts counting a new run on the most recent character
            currentRunCount = 1;
            currentRunChar = buffer[i];
        }
    }
    // Save results into the struct
    data->maxRunLength = maxLength;
    data->maxRunChar = maxLengthChar;
    pthread_exit(NULL);
}

int readFile(char *fileName, int *numChars) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) { // Attempts to open the fi;e
        printf("ERROR: cannot open file '%s'\n", fileName);
        return 1;
    }

    // Initialized variables for collecting data from file
    char *chp;
    char line[LINELEN];
    int len;
    int bufferIndex = 0;

    chp = fgets(line, LINELEN, fp);
    if (chp == NULL) { // If the file is empty at the start
        printf("file is empty\n");
        fclose(fp);
        return 8;
    }

    // Loops through remainder of file
    while(chp != NULL) {
        len = strlen(line);
        // Fixes fget() quirk where newline character is read
        if (line[len-1] == '\n') {
            len = len - 1;
        }

        // Append the contents of the line[] buffer to the global buffer
        for (int i=0; i < len; ++i) {
            buffer[bufferIndex] = line[i];
            ++bufferIndex;
        }
        chp = fgets(line, LINELEN, fp);
    }
    *numChars = bufferIndex;
    return 0;
}