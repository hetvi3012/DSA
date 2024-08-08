//Name : Hetvi Bagdai
//Entry Number: 2023CSB1123

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void quicksort(int *arr, int start, int end);
int median_of_medians(int *arr, int start, int end, int k);
int select_pivot(int *arr, int start, int end, int k);
int pivot(int *arr, int n);

//for reading file
void readFile(const char *filename, int **arr, int *n, int *k) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);
    *arr = malloc((*n) * sizeof(int)); // memory allocation for array
    fscanf(file, "%d", k); // Read the value of K

    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d", &((*arr)[i])); // Read each element into the array
    }

    fclose(file);
}

// Quicksort function with pivot as the last element
void quicksort(int *arr, int start, int end) {
    if (start >= end) return; // Base case: no need to sort

    int pivot = arr[end]; // Choosing the last element as pivot
    int ct_left = 0, ct_right = 0;  // counting how many elements are greater than and less than pivot
    int *left = (int *)malloc((end - start + 1) * sizeof(int)); //left array to store elements less than pivot
    int *right = (int *)malloc((end - start + 1) * sizeof(int)); //right array to store elements greatet than pivot

    // Partitioning: elements less than pivot go to the left, more go to the right
    for (int i = start; i < end; i++) {
        if (arr[i] < pivot)
            left[ct_left++] = arr[i];
        else if (arr[i] > pivot)
            right[ct_right++] = arr[i];
    }

    // Recursive sort of left and right subarrays
    quicksort(left, 0, ct_left - 1);
    quicksort(right, 0, ct_right - 1);

    // Merging back into original array
    int k = start;
    for (int i = 0; i < ct_left; i++) {
        arr[k++] = left[i];
    }
    arr[k++] = pivot; // Placing pivot in its correct position
    for (int i = 0; i < ct_right; i++) {
        arr[k++] = right[i];
    }

    // Free allocated memory
    free(left);
    free(right);
}

// Median-of-medians function
int select(int *arr, int start, int end, int k)  //median of medians algorithm to find kth smallest
{
    int pivot = select_pivot(arr + start, 0, end - start, (end - start + 1) / 2); //choosing pivot from pivot function
    int ct_right = 0;      //counting elements less than pivot and more than pivot
    int ct_left = 0;
    for (int i = start; i <= end; i++)
    {
        if (arr[i] > pivot)
            ct_right++;
        else if (arr[i] < pivot)
            ct_left++;
    }
    int *left = (int *)malloc((ct_left + 1) * sizeof(int));
    int *right = (int *)malloc((ct_right + 1) * sizeof(int));

    // making two arrays
    int left_index = 0;
    int right_index = 0;
    for (int i = start; i <= end; i++) {
        if (arr[i] < pivot)
            left[left_index++] = arr[i];
        else if (arr[i] > pivot)
            right[right_index++] = arr[i];
    }

    //recurrsively call select to find kth smallest element
    int result;
    if (ct_left == k - 1)
        result = pivot;
    else if (ct_left >= k)
        result = select(left, 0, ct_left - 1, k);
    else
        result = select(right, 0, ct_right - 1, k - ct_left - 1);

    free(left);
    free(right);

    return result;
}



// select pivot function
int select_pivot(int *arr, int start, int end, int k)
{
    int n = end - start + 1;
    if (n <= 5)
    {
        quicksort(arr, start, end); // using quicksot to sort the array
        return arr[start + n / 2];
    }
    int med[(n + 4) / 5];
    int pt = 0;
    for (int i = 0; i < n / 5; i++)
    {
        int *bucket = (int *)malloc(5 * sizeof(int));
        for (int j = 0; j < 5; j++)
            bucket[j] = arr[start + i * 5 + j];
        quicksort(bucket, 0, 4); // using quicksort to sort each bucket
        med[pt++] = bucket[5 / 2];
        free(bucket);
    }

    int v = n % 5;
    if (v > 0)
    {
        int *bucket = (int *)malloc(v * sizeof(int));
        for (int j = 0; j < v; j++)
        {
            bucket[j] = arr[end - v + 1 + j];
        }
        quicksort(bucket, 0, v - 1); // Use your quicksort function
        med[pt++] = bucket[v / 2];
        free(bucket);
    }

    return select(med, 0, pt - 1, pt / 2); // Recursively calculate the median of medians
}


int func1(int *arr, int n, int k) {
    quicksort(arr, 0, n - 1);  // calling quicksort function
    return arr[k - 1];
}

int func2(int *arr, int n, int k) {       // calling select function
        return select(arr, 0, n - 1, k);
}

// main function
int main() {
    int n, k;
    int *arr;

    readFile("ExampleFile.txt", &arr, &n, &k);  // calling readFile

    printf("The size of the array is %d\n", n);     // printing size
    printf("The value of K is %d\n", k);      // printing k

    int *arr1 = malloc(n * sizeof(int));
    memcpy(arr1, arr, n * sizeof(int));          //copying arr to arr1

    clock_t start, end;         //for calculating time
    double cpu_time_used;

    printf("Calling func1:\n");
    start = clock();      // starting time
    int result1 = func1(arr1, n, k);        // calling quicksort by function 1
    end = clock();        // stopping time
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The %d-th smallest element returned by func1 is %d\n", k, result1);       // printing result
    printf("The time taken by func1 is %.1f\n", cpu_time_used);  //printing time

    printf("Calling func2:\n");
    start = clock();     //start time
    int result2 = func2(arr, n, k);     //calling median of medians .
    end = clock();         //ending time
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The %d-th smallest element returned by func2 is %d\n", k, result2);    //printing result
    printf("The time taken by func2 is %.1f\n", cpu_time_used); //printing time

    free(arr);
    free(arr1);
    return 0;
}
