#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#define ARRAY_SIZE_LEVEL_1 125
#define ARRAY_SIZE_LEVEL_2 250
#define ARRAY_SIZE_LEVEL_3 500
#define ARRAY_SIZE_LEVEL_4 1000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomArray(int *);
void printArray(int *,int );
int compar(const void *, const void *);

#endif
