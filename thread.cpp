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
    int n = sizeS;
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
    standardDev = sqrt(variance(arr, sizeS));
} 


////////////////////////////////////////////////////////////////////////
void *average(void *vargp) 
{ 
  //  sleep(1); 
    int *arr = (int*)vargp;
  //  printf("Printing GeeksQuiz from Thread \n");
    long double sum = 0; 
    for(int i=0; i<sizeS; i++)
    {
   	sum = sum + arr[i];
    } 
    long double avg = (long double)sum/(long double)3;
	mean1 = avg = (long double)sum/sizeS;
  //  cout << "average = " << avg << "\n";
   
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

	  filename = argv[1];
		
	  file.open(filename.c_str());
	  int count = 0, iter = 0;

	  file >> word;
//	  cout << "word - " << word << "\n";
	  int index = atoi(word.c_str());
	  int *arr = new int[index];
	  while (file >> word)
 	  {
		arr[iter] = atoi(word.c_str());
		iter = iter + 1;
	  }

          for(int i=0; i< index; i++)
	  {
		cout << arr[i] << " ";

	  }
	  cout << "\n";
	
     	//  cout << "size = "<<data.size()<< "\n";
	//int index = atoi(data.at(0).c_str());	

//	for(int i=1; i<data.size(); i++)
//	{
//		int num = atoi(data.at(i).c_str());
//		array.push_back(num);
//	}

//	cout << "array size = "<< array.size() << "\n";
/////////////////////////////////////////////////////////

    //printf("Before Thread\n");
    pthread_t thread_id, thread_id1, thread_id2;
//    cout << "tread size = "<< index << "\n"; 
    
    
        for(int i=0; i<array.size(); i++)
	{
		arr[i] = array.at(i);
	}
    sizeS = index;

    pthread_create(&thread_id, NULL, average, (void*)arr);   //avg
    pthread_create(&thread_id1, NULL, standardDeviation, (void*)arr); 
    pthread_create(&thread_id2, NULL, findMedian, (void*)arr); 
    pthread_join(thread_id, NULL); 
//    printf("After Thread\n"); 
   // exit(0); 

    cout << "the average value is " << mean1 << "\n";
    cout << "the standard deviation value is " << standardDev << "\n";
    cout << "the median values is " << median << "\n"; 
    delete arr;
}

