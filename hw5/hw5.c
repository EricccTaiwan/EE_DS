#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define LEN (1 * 10000) // 陣列長度

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {       //check each number
        for (int j = 0; j < n-1-i; j++) { //compare each number
            if (arr[j] > arr[j+1]) {      //前面num > 後面num
                swap(&arr[j], &arr[j+1]); //前後交換
            }
        }
    }
}

int partition(int arr[], int start, int end) 
{ 
    int pivot = arr[start]; //首項當pivot
    int i = start; 
    int j = end; 
    while (i < j) { 
        do i++; while (arr[i] <= pivot); //找到比pivot大的數
        do j--; while (arr[j] > pivot);  //找到比pivot小的數
        if (i < j) { 
            swap(&arr[i], &arr[j]); //交換
        } 
    } 
    swap(&arr[start], &arr[j]); //pivot與j交換
    return j; 
} 

void quicksort(int arr[], int start, int end) 
{ 
    if (start < end) { 
        int pivot = partition(arr, start, end); //找出pivot
        quicksort(arr, start, pivot - 1); //pivot左邊
        quicksort(arr, pivot + 1, end);   //pivot右邊
    } 
} 

void merge(int arr[], int l, int q, int r) {
    int i, j, k;
    int n1 = q - l + 1;
    int n2 = r - q;
    int L[n1+1], R[n2+1];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];  //左邊
    for (j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j]; //右邊
    L[n1] = INT_MAX; //sentinel
    R[n2] = INT_MAX; //sentinel
    i = 0;
    j = 0;
    k = l;
    while (k <= r) {
        if (L[i] <= R[j]) {  //左邊小於等於右邊
            arr[k] = L[i];   //放左邊的元素
            i++;
        } 
        else {
            arr[k] = R[j]; //放右邊的元素
            j++;  
        }
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int q = l + (r - l) / 2;  //中間
        mergeSort(arr, l, q);     //左邊，包含q
        mergeSort(arr, q + 1, r); //右邊
        merge(arr, l, q, r);      //merge
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