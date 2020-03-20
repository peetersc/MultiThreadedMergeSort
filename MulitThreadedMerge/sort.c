#include<stdlib.h> 
#include<stdio.h> 
#include <pthread.h>
#include "sort.h"

void merge(long arr[], int left, int middle, int right) 
{ 
    int i, j, k; 
    int n1 = middle - left + 1; 
    int n2 =  right - middle; 
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[left + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[middle + 1+ j]; 
  
    i= 0;  
    j = 0;  
    k = left; 

    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void singleThreadedMergeSort(long arr[], int left, int right){
  if (left < right) {
    int middle = (left+right)/2;
    singleThreadedMergeSort(arr, left, middle); 
    singleThreadedMergeSort(arr, middle+1, right); 
    merge(arr, left, middle, right); 
  }
}

void* merge_single_Threads(void* thread){
    struct thread *this_thread = (struct thread*)thread;
    singleThreadedMergeSort(this_thread->t_arr,this_thread->left,this_thread->right);
    pthread_exit(0);
    
}

void* merge_multi_Threads(void* thread){
    struct thread *this_thread = (struct thread*)thread;
    merge(this_thread->t_arr,this_thread->left,this_thread->middle,this_thread->right);
    pthread_exit(0);

}

void multiThreadedMergeSort(long arr[], int left, int right){

    //indices for separating the array
    int middle = (left+right)/2;
    int upper_middle = middle * 1.5;
    int sub_middle = middle/2;
    
    //seperate threads
    struct thread args[4];
    pthread_t tids[4];
    
    //launch threads at once
    for (int i = 0; i < 4; ++i){

        args[i].id = i;
        args[i].t_arr = arr;
        
        if (i == 0){
            args[i].left = left;
            args[i].right = sub_middle;
        }
        else if (i == 1){
            args[i].left = sub_middle+1;
            args[i].right = middle;
        }
        else if (i == 2){
            args[i].left = middle+1;
            args[i].right = upper_middle;
        }
        else if (i == 3){
            args[i].left = upper_middle+1;
            args[i].right = right;
        }
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i],&attr,merge_single_Threads, &args[i]);
    }
    
    pthread_t mL,mR;
    struct thread a,b;
    
    a.t_arr = arr;
    a.left = left;
    a.middle = sub_middle;
    a.right = middle;
    
    b.t_arr = arr;
    b.left = middle+1;
    b.middle = upper_middle;
    b.right = right;
    
    pthread_create(&mL,NULL,merge_multi_Threads,&a);
    pthread_create(&mR,NULL,merge_multi_Threads,&b);

    pthread_join(mL,NULL);
    pthread_join(mR,NULL);
    
    merge(arr,left, middle, right);
    
}