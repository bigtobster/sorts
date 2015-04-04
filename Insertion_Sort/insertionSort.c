#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
   
void shuffleArray(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
		for (i = 0; i < n - 1; i++) 
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
    }
}

int * generateArray(size_t arraySize)
{
	size_t n = arraySize;
	int *myArray = (int *)malloc(n * sizeof(int*));
	size_t i;
	for(i = 0; i < n; i++)
	{
		myArray[i] = i;
	}
	return myArray;
}

void printArray(int *myArrayPtr)
{
	printf("The 5th element of the array is now: %d", myArrayPtr[5]);
	printf("\n");
}

void fullPrintArray(int *myArrayPtr, size_t arrayLength)
{
	int i;
	for(i = 0; i < arrayLength; i++)
	{
		printf("Array Value at element %d is: %d\n", i, myArrayPtr[i]);
	}
}

void insertionSort(int *arrayPtr, size_t arraySize)
{
	int *myArrayPtr = arrayPtr;
	int i;
	for (i = 1; i < arraySize; i++)
	{
		//loop through array instances
		if(myArrayPtr[i] < myArrayPtr[i-1])
		{
			//Is the number that is supposed to be bigger...
			//Actually bigger than the number that is supposed
			//to be smaller?
			int tempInt = myArrayPtr[i];
			myArrayPtr[i] = myArrayPtr[i-1];
			int ii;
			for(ii = i-1; ii >= 0; ii--)
			{
				//Start search for correct position at i-2
					//NOT i because i is DEFINITELY greater than tempInt
					//NOT i-1 because i is DEFINITELY greater than tempInt
				// Go no further than index 0 (obviously)
				if(myArrayPtr[ii] <= tempInt)
				{
					//Looks for insertion spot
					//Insertion point AT myArrayPtr[ii+1]
					myArrayPtr[ii+1] = tempInt;
					ii = 0;
				}
				else if(ii == 0)
				{
					myArrayPtr[ii] = tempInt;
				}
				else
				{
					myArrayPtr[ii+1] = myArrayPtr[ii];
					//If not insertion point, increment position
				}
			}
			//find correct position
			//Increment all positions of array
				//Starting at correct position index
				//Ending at discovery index
			//Insert in the correct position
			//Continue loop
		}
		//Else
			//Carry on, no action needed
	}
}

void getSystemTime(double *time)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);

	*time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
    // convert tv_sec & tv_usec to millisecond
    //printf("Sys time: %fm\n", *time);         
}

int main()
{
	double preSortTime = 0;
	double postSortTime = 0;
	size_t arraySize = 10000000;
	int *myArrayPtr = generateArray(arraySize);
	printf("Array Generated\n");
	//fullPrintArray(myArrayPtr, arraySize);
	shuffleArray(myArrayPtr, arraySize);
	printf("Array Shuffled\n");
	//fullPrintArray(myArrayPtr, arraySize);
	getSystemTime(&preSortTime);
	insertionSort(myArrayPtr, arraySize);
	getSystemTime(&postSortTime);
	printf("Array Sorted in %f milliseconds\n", postSortTime - preSortTime);
	//fullPrintArray(myArrayPtr, arraySize);
	free(myArrayPtr);
	return 0;
}
