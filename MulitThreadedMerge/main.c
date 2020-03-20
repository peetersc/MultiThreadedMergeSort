#include "sort.h"
#include<stdlib.h> 
#include<stdio.h> 
#include <pthread.h>
#include <time.h>

int main(int argc, char* argv[]){

    size_t size = argc-1;
    long arr[size];
    int num;

    for(int i = 1; i < argc; ++i){
        sscanf(argv[i],"%d",&num);
        arr[i-1] = num;
    }

    for (int i = 0; i < size; ++i)
        printf("%ld ", arr[i]);
    printf("\n");

    multiThreadedMergeSort(arr, 0,size);

    for (int i = 1; i <= size; ++i)
        printf("%ld ", arr[i]);
    printf("\n");
    
    return 0;
}