
// Author - SAURAV VARA PRASAD CHANNURI
// Problem - finding mean, median, standard deviation using multi-threading
// data paralellisation
// used posix thread library


#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <iostream>
#include <assert.h>
#include <iterator>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <string> 
#include <math.h>
#include <time.h>
using namespace std;
 
 

double  mean1, median, standardDev;
int sizeS;

void merge(int arr[],int l , int m ,int r)
{
  int n1= m-l +1,n2=r-m,k=l;
  int arr1[n1],arr2[n2];
  for(int i =0; i<n1;i++)
  {
    arr1[i]=arr[l+i];
  }
  for(int i =0; i<n2;i++)
  {
     arr2[i]=arr[m+i+1];
  }
  int i =0, j =0;
  while(i<n1&&j<n2)
  {
        if(arr1[i]<arr2[j])
          arr[k++]= arr1[i++];
        if(arr1[i]>arr2[j])
          arr[k++]= arr2[j++];
        if(arr1[i]==arr2[j])
        {
           arr[k++]= arr1[i++];
           arr[k++] = arr2[j++];
        }
   }	
  while(i<n1)
    arr[k++]=arr1[i++];
  while(j<n2)
    arr[k++]=arr2[j++];

}
void mergesort(int arr[], int l , long int r)
{
	cout << "r = " << r << "\n";
  if(l<r)
  {
    int m = (l+r)/2;
    mergesort(arr,l,m);	
    mergesort(arr,m+1,r);
    merge(arr,l,m,r);
  }
}

/////////////////////////////////////////////////////////////////////

void *findMedian(void *vargp) 
{ 
    // First we sort the array
    int *a = (int*)vargp; 
    
    int n = sizeS;
    sort(a, a+n); 
  
    // check for even case 
    if (n % 2 != 0) 
    {  
    
       median = (double)a[n/2];
    }	
    else      
    { 

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
    
    standardDev = sqrt(variance(arr, sizeS));
} 


////////////////////////////////////////////////////////////////////////
void *average(void *vargp) 
{ 
  //  sleep(1); 
    int *arr = (int*)vargp;
  
    long double sum = 0; 
    for(int i=0; i<sizeS; i++)
    {
   	sum = sum + arr[i];
    } 
    long double avg = (long double)sum/(long double)3;
	mean1 = avg = (long double)sum/sizeS;

   
    return NULL; 
} 
////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) 
{   
   	/* the size (in bytes) of shared memory object */
          ifstream file;
	  char c;

	  string word, t,q,filename, NOE;
	  string inputString, replacement;
	  vector<string> data, My_Cache;
	  vector<long int> array;
	  int numberOfEntries = 0;	
	  ofstream myFile;
	  filename = "MultiThreading.txt";
	  myFile.open(filename.c_str());

	  filename = argv[1];
	  time_t time;
		
	  file.open(filename.c_str());
	  int count = 0, iter = 0;

	  file >> word;

	  int index = atoi(word.c_str());
	  int *arr = new int[index];
	  while (file >> word)
 	  {
		arr[iter] = atoi(word.c_str());
		iter = iter + 1;
	  }

	  cout << "\n";

/////////////////////////////////////////////////////////

    //printf("Before Thread\n");
    pthread_t thread_id, thread_id1, thread_id2;
    sizeS = index;
    
    time = clock();
    pthread_create(&thread_id, NULL, average, (void*)arr);   //avg
    pthread_create(&thread_id1, NULL, standardDeviation, (void*)arr);

     //////////////////////////////////////////
/////////               mean

    int n = sizeS;
    sort(arr, arr+n); 
    // check for even case 
    if (n % 2 != 0) 
    {  
    
       median = (double)arr[n/2];
    }	
    else      
    { 
	 median = (double)arr[n/2];
    }

    time = clock() - time; 
    pthread_join(thread_id, NULL);
    pthread_join(thread_id1, NULL);
    double duration = ((double)time)/CLOCKS_PER_SEC;
    
 

    myFile << "the average value is " << mean1 << "\n";
    myFile << "the standard deviation value is " << standardDev << "\n";
    myFile << "the median values is " << median << "\n"; 
 
    delete arr;
}

