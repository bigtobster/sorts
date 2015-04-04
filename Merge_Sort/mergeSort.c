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

void fullPrintArray(int *myArrayPtr, size_t arrayLength)
{
	int i;
	for(i = 0; i < arrayLength; i++)
	{
		printf("Array Value at element %d is: %d\n", i, myArrayPtr[i]);
	}
}

int * splitArray(int *array, int startPoint, int endPoint)
{
	int *splitArray = (int *)malloc(((endPoint-startPoint)+1) * sizeof(int*));
	int i;
	for(i = 0; i <= endPoint - startPoint; i++)
	{
		splitArray[i] = array[startPoint + i];
	}
	return splitArray;
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

int * merge(int *array1, size_t array1Size, int *array2, size_t array2Size)
{
	//Combine arrays
	//Generate new array of correct length
	//Add element from each array in correct order
	//Free parameter arrays
	int *combinedArray = (int *)malloc((array1Size+array2Size) * sizeof(int*));
	int i;
	size_t array1Index = 0;
	size_t array2Index = 0;
	for(i = 0; i < array1Size + array2Size; i++)
	{
		if(array1Index == array1Size)
		{
			combinedArray[i] = array2[array2Index];
			array2Index++;
		}
		else if(array2Index == array2Size)
		{
			combinedArray[i] = array1[array1Index];
			array1Index++;
		}
		else
		{
			if(array1[array1Index] <= array2[array2Index])
			{
				combinedArray[i] = array1[array1Index];
				array1Index++;
			}
			else
			{
				combinedArray[i] = array2[array2Index];
				array2Index++;
			}
		}
	}
	return combinedArray;
}

int * mergeSort(int *array, size_t arraySize)
{
	//If single value
		//return
	//Else
		//Split
		//Merge Sort
		//Merge
	if(arraySize <= 1)
	{
		return array;
	}
	else
	{
		int middlePoint = arraySize/2;
		int *array1 = splitArray(array, 0, middlePoint-1);
		int *array2 = splitArray(array, middlePoint, arraySize-1);
		array1 = mergeSort(array1, middlePoint);
		array2 = mergeSort(array2, arraySize - middlePoint);
		return merge(array1, middlePoint, array2, arraySize - middlePoint);
	}
}

void getSystemTime(double *time)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);

	*time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
    // convert tv_sec & tv_usec to millisecond     
}

int main()
{
	double preSortTime = 0;
	double postSortTime = 0;
	size_t arraySize = 100000;
	int *myArrayPtr = generateArray(arraySize);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Generated\n\n");
	shuffleArray(myArrayPtr, arraySize);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Shuffled\n\n");
	getSystemTime(&preSortTime);
	myArrayPtr = mergeSort(myArrayPtr, arraySize);
	getSystemTime(&postSortTime);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Sorted in %f milliseconds\n\n", postSortTime - preSortTime);
	free(myArrayPtr);
	return 0;
}
