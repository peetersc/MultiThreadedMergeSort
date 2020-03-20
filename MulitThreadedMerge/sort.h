#include<stdio.h>
#include<stdlib.h>

#ifndef _SORT_H_INCLUDE_
#define _SORT_H_INCLUDE_

void merge                  (long[], int, int , int );
void singleThreadedMergeSort(long[], int, int );
void multiThreadedMergeSort (long[], int, int );

struct thread
{
    int id;
    long *t_arr;
    int left;
    int right;
    int middle;
};

#endif

