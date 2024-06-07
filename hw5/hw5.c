#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN (1 * 10000) // 陣列長度

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j+1]);
            }
        }
    }
}

int partition(int arr[], int low, int high) 
{ 
    int pivot = arr[low]; 
    int i = low; 
    int j = high; 

    while (i < j) { 
        while (arr[i] <= pivot && i <= high - 1) { 
            i++; 
        } 
        // condition 2: find the first element smaller than 
        // the pivot (from last) 
        while (arr[j] > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[low], &arr[j]); 
    return j; 
} 

void quicksort(int arr[], int low, int high) 
{ 
    if (low < high) { 
        int partitionIndex = partition(arr, low, high); 
        // Recursively call quickSort() for left and right 
        // half based on partition Index 
        quicksort(arr, low, partitionIndex - 1); 
        quicksort(arr, partitionIndex + 1, high); 
    } 
} 

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
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

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(NULL)); // seed
    int a[LEN]={0};
    int b[LEN]={0};
    int c[LEN]={0};
    printf("Count = %d\n", LEN);

    for (int i = 0; i < LEN; i++) {
        a[i] = rand() % 100000 + 1; // 1~100000
        b[i] = a[i];
        c[i] = a[i];
    }
    clock_t t;
    t = clock();
    bubblesort(a, LEN);
    t = clock() - t;
    printf("Bubble_sort time: %f (s)\n", ((float)t)/CLOCKS_PER_SEC);

    t = clock();
    quicksort(b, 0, LEN-1);
    t = clock() - t;
    printf("Quick_sort time: %f (s)\n", ((float)t)/CLOCKS_PER_SEC);

    t = clock();
    mergeSort(c, 0, LEN-1);
    t = clock() - t;
    printf("Merge_sort time: %f (s)\n", ((float)t)/CLOCKS_PER_SEC);
    return 0;
}