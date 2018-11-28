#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/shm.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <math.h>
using namespace std;

void merge(vector<int> &arr,int l , int m ,int r)
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
  //printf("ee");
}
void mergesort(vector<int> &arr, int l , int r)
{
  if(l<r)
  {
    int m = (l+r)/2;
    mergesort(arr,l,m);	
    mergesort(arr,m+1,r);
    merge(arr,l,m,r);
  }
}

/////////////////////////////////////////////////////////////////////

long double findMedian(vector<int> a) 
{ 
    // First we sort the array
    //int *a = (int*)vargp; 
    int n = a.size();
    mergesort(a, 0,a.size()-1); 
  
    // check for even case 
    if (n % 2 != 0) 
    {  
     //  cout<< "median = "<< (double)a[n/2] << "\n"; 
       long double median = (long double)a[n/2];
       return median;
    }	
    else      
    { 
      // cout <<"median = " << (double)(a[(n-1)/2] + a[n/2])/2.0 << "\n"; 
       long double median = (long double)a[n/2];
       return median;
    }
} 
/////////////////////////////////////////////////////////////////////

long double variance(vector<int> a) 
{ 
    // Compute mean (average of elements) 
    int sum = 0, n=a.size(); 
    for (int i = 0; i < n; i++) 
	{    
	  //  cout << a[i] << " "; 
	    sum += a[i]; 
	}
	
    long double mean = (long double)sum / (long double)n; 
  	//cout << "mean in var = "<< mean << "\n\n";
    // Compute sum squared  
    // differences with mean. 
    long double sqDiff = 0; 
    for (int i = 0; i < n; i++)  
    {
	cout << (a.at(i) - mean) << " ";
        sqDiff += (a[i] - mean) * (a[i] - mean); 
    }
	cout << "\n" <<  (long double)sqDiff / (long double)n << " \n";
    return (long double)sqDiff / (long double)n  ; 
} 
  
long double standardDeviation(vector<int> arr) 
{ 
    return sqrt(variance(arr));
} 

////////////////////////////////////////////////////////////////////////
long double average(vector<int> arr) 
{ 
    int sum = 0; 
  
    for(int i=0; i<arr.size(); i++)
    {
   	sum = sum + arr[i];
    } 
    long double avg = (long double)sum/(long double)arr.size();
  
  
    return avg; 
} 

//////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv)
{
		/* the size (in bytes) of shared memory object */
          ifstream file;
	  char c;

	  string word, t,q,filename, NOE;
	  string inputString, replacement;
	  vector<string> data, My_Cache;
	  vector<int> array;
	  int numberOfEntries = 0;	

	  filename = argv[1];
		
	  file.open(filename.c_str());
	  int count = 0;

	  while (file >> word)
 	  {
      		data.push_back(word);
	  }

     	 // cout << data.at(3);
	
	for(int i=1; i<data.size(); i++)
	{
		int num = atoi(data.at(i).c_str());
		array.push_back(num);
	}
	  
	int SIZE = 4096;
		/* name of the shared memory object */
	const char *name = "OS";

	int shm_fd;

	//struct timeval *start, end;	
	
	long double *vals;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd, SIZE);
	
	vals = (long double*)mmap(0, SIZE,PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
			

	pid_t pid1, pid2;
	pid1 = fork();
	pid2 = fork();
	
	if (pid1 < 0 || pid2 < 0)         // error condition
	{ 	
		cout  << " fork failed\n"; 		
		return 1;	
	}	

	else if (pid1 == 0 && pid2 >0)   // child 1
	{ 	
		long double avg = average(array);
		vals[0] =  avg;	
	}
	
	else if(pid1 > 0 && pid2 == 0)  // child 2
	{	
		long double deviation =  standardDeviation(array);
		vals[1] = deviation;	
	}

	else if(pid1 == 0 && pid2 == 0)  // child 3
	{
		long double med = findMedian(array);
		vals[2] = med;

	}

	else if(pid1 > 0 && pid2 > 0)    // parent process
	{
		wait(NULL);
		cout << "the mean value is " << vals[0] << "\n";
		cout << "the standard deviation value is " << vals[1] << "\n";
		cout << "the median value is " << vals[2] << "\n";		
		
		
	}

}

