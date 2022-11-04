#ifndef ASSIGNMENT3PTHREADS_MAXRUN_JHENRY3_H
#define ASSIGNMENT3PTHREADS_MAXRUN_JHENRY3_H

#define LINELEN 256
#define BUFLEN 10100
char buffer[BUFLEN];

#define NUM_THREADS 4
#define MARGIN 10 //used in case run of digits goes over buffer separation point

typedef struct {
    int startIndex; // start index in buffer[] at which to begin searching
    int endIndex; // end index
    int maxRunLength; // result: the longest run found of any character in buffer[],
// between startIndex and endIndex (inclusive)
    char maxRunChar; // result: the character in the longest run
} SearchInfo;

/**
 * Function that is run by each thread, which searches for the longest run of the same character in an array
 */
void *searchFunction(void *param);

/**
 * Reads in files of multiple lines and added them to character array
 */
int readFile(char *fileName, int *numChars);

#endif //ASSIGNMENT3PTHREADS_MAXRUN_JHENRY3_H
