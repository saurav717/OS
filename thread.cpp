
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string> 
#include <math.h>
using namespace std;
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 

double  mean1, median, standardDev;
int sizeS;

/////////////////////////////////////////////////////////////////////

void *findMedian(void *vargp) 
{ 
    // First we sort the array
    int *a = (int*)vargp; 
    int n = 3;
    sort(a, a+n); 
  
    // check for even case 
    if (n % 2 != 0) 
    {  
     //  cout<< "median = "<< (double)a[n/2] << "\n"; 
       median = (double)a[n/2];
    }	
    else      
    { 
      // cout <<"median = " << (double)(a[(n-1)/2] + a[n/2])/2.0 << "\n"; 
       median = (double)a[n/2];
    }
} 
/////////////////////////////////////////////////////////////////////
double variance(int a[], int n) 
{ 
    // Compute mean (average of elements) 
    int sum = 0; 
    for (int i = 0; i < n; i++) 
        sum += a[i]; 
    double mean = (double)sum /  
                  (double)n; 
  
    // Compute sum squared  
    // differences with mean. 
    double sqDiff = 0; 
    for (int i = 0; i < n; i++)  
        sqDiff += (a[i] - mean) *  
                  (a[i] - mean); 
    return sqDiff / n  ; 
} 
  
void *standardDeviation(void *vargp) 
{ 
    
    int *arr = (int*)vargp;
   // cout << "standard deviation = " << sqrt(variance(arr, 3)) << "\n"; 
    standardDev = sqrt(variance(arr, 3));
} 


////////////////////////////////////////////////////////////////////////
void *average(void *vargp) 
{ 
  //  sleep(1); 
    int *arr = (int*)vargp;
  //  printf("Printing GeeksQuiz from Thread \n");
    int sum = 0; 
    for(int i=0; i<3; i++)
    {
   	sum = sum + arr[i];
    } 
    float avg = sum/3;
  //  cout << "average = " << avg << "\n";
    mean1 = sum/ 3;
    return NULL; 
} 
////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) 
{ 
    pthread_t thread_id, thread_id1, thread_id2; 
    vector<int> array;
    //printf("Before Thread\n");
   // size = 
    int arr[3] = {1,2,3};
    pthread_create(&thread_id, NULL, average, (void*)arr);   //avg
    pthread_create(&thread_id1, NULL, standardDeviation, (void*)arr); 
    pthread_create(&thread_id2, NULL, findMedian, (void*)arr); 
    pthread_join(thread_id, NULL); 
//    printf("After Thread\n"); 
   // exit(0); 

    cout << "the average value is " << mean1 << "\n";
    cout << "the standard deviation value is " << standardDev << "\n";
    cout << "the median values is " << median << "\n";
}

