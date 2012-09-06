#include "array_header.h"

#define RANDOM_NUMBERS 9999

void randomArray(int *array){
    int i;
    
    for(i = 0; i < ARRAY_SIZE_LEVEL_1; i++)
        array[i] = rand()%RANDOM_NUMBERS;
}

void printArray(int *array,int numElemInArray){ 
    int i;
    
    for(i = 1; i <= numElemInArray; i++){
        printf("%5d  ",array[i-1]);
    	if(!(i%11))
    		printf("\n");
    }
	printf("\n");
}

int compar(const void *x1, const void *x2){
    int elem1 = *(const int*) x1;     
    int elem2 = *(const int*) x2;     

    return (elem1<elem2)?-1:1;  
}
