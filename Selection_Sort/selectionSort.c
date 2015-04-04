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

void selectionSort(int *arrayPtr, size_t arraySize)
{
	//List of unsorted values
	//Look for the smallest value
	//Swap it with the first value
	//Look for next smallest
	//Swap with second value
	//etc
	int marker;
	for(marker = 0; marker < arraySize; marker++)
	{
		//Loop through array
		int i;
		int smallestValue = arrayPtr[marker];
		int smallestValueIndex = marker;
		int tempValue = 0;
		for(i = marker+1; i < arraySize; i++)
		{
			//look for smallest value
			if(arrayPtr[i] < smallestValue)
			{
				smallestValue = arrayPtr[i];
				smallestValueIndex = i;
			}
		}
		tempValue = arrayPtr[marker];
		arrayPtr[marker] = smallestValue;
		arrayPtr[smallestValueIndex] = tempValue;
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
	size_t arraySize = 100000;
	int *myArrayPtr = generateArray(arraySize);
	printf("Array Generated\n");
	//fullPrintArray(myArrayPtr, arraySize);
	shuffleArray(myArrayPtr, arraySize);
	printf("Array Shuffled\n");
	//fullPrintArray(myArrayPtr, arraySize);
	getSystemTime(&preSortTime);
	selectionSort(myArrayPtr, arraySize);
	getSystemTime(&postSortTime);
	printf("Array Sorted in %f milliseconds\n", postSortTime - preSortTime);
	//fullPrintArray(myArrayPtr, arraySize);
	free(myArrayPtr);
	return 0;
}
