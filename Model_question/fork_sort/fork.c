#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
// Function to print an array
void printArray(int arr[], int size)
{
    printf("Sorted array :");
    for (int i = 0; i < size; i++)
        printf(" %d",arr[i]);
    printf("\n");
}

void bubbleSortasc(int arr[], int n)
{
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
                swapped = 1;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == 0)
            break;
    }
    printArray(arr,n);
}

void bubbleSortdesc(int arr[], int n)
{
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
                swapped = 1;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == 0)
            break;
    }
    printArray(arr,n);
}

int main()
{
	int size;
    printf("Enter the size : ");
    scanf("%d",&size);
    int array[size];
    printf("Enter the array elements :");
    for(int i = 0;i < size;i++)
        scanf("%d",&array[i]);
    int pid;
	pid = fork();
	if(pid<0){
		printf("Error\n");
	}
	else if(pid==0){
		printf("\nChild process\n");
		bubbleSortasc(array,size);
	}
	else{
		wait(NULL);
		printf("\nParent process\n");
		bubbleSortdesc(array,size);		
	}
	return 0;	
}