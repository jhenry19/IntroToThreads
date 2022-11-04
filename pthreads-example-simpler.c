-------------------------------
 jdh CS201 Spring 2021
-------------------------------

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_CHILDREN 2
#define NUM_ELEMENTS 1000

void *searchFunction(void *param);

typedef struct {
    int lowVal;
    int highVal;
    int maxVal;
} SumStruct;

int A[NUM_ELEMENTS];

//---------------------------------------------------------------------------

void *searchFunction(void *param) {
    SumStruct *data;
    int i, maxVal;

    data = (SumStruct *) param;
    printf("(R) I am runner; will do search the range %d to %d\n",
           data->lowVal, data->highVal);

    maxVal = A[data->lowVal];

    for (i=data->lowVal; i<=data->highVal; ++i) {
        if (A[i] > maxVal)
            maxVal = A[i];
    }

    data->maxVal = maxVal;
    printf("(R) max is %d\n", data->maxVal);
    pthread_exit(NULL);
}

//---------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    SumStruct dataOne;   // holds data we want to give to child thread #1
    SumStruct dataTwo;   // holds data we want to give to child thread #2
    pthread_t tidOne;    // thread identifier for child thread #1
    pthread_t tidTwo;    // thread identifier for child thread #2
    int maxVal;
    int i;  // initialize the array with random integers in the range 0..NUM_ELEMENTS
    for (i=0; i<NUM_ELEMENTS; ++i)
        A[i] = (int) NUM_ELEMENTS * drand48();

    // set up bounds for the threads
    dataOne.lowVal = 0;
    dataOne.highVal = NUM_ELEMENTS/2;

    dataTwo.lowVal = NUM_ELEMENTS/2 + 1;
    dataTwo.highVal = NUM_ELEMENTS-1;

    // create child thread #1
    pthread_create(&tidOne, NULL, runner, &dataOne);
    // create child thread #2
    pthread_create(&tidTwo, NULL, runner, &dataTwo);

    // wait for the child threads to terminate
    pthread_join(tidOne, NULL);
    pthread_join(tidTwo, NULL);

    // gather data from the individual results
    maxVal = dataOne.maxVal;
    if (dataTwo.maxVal > dataOne.maxVal)
        maxVal = dataTwo.maxVal;

    printf("maxVal = %d\n", maxVal);
    return 0;
}

