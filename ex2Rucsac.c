#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int MAX = i;
    int stanga = 2 * i + 1;
    int dreapta = 2 * i + 2;

    if (stanga < n && arr[stanga] > arr[MAX]) MAX = stanga;
    if (dreapta < n && arr[dreapta] > arr[MAX]) MAX = dreapta;

    if (MAX != i) {
        swap(&arr[i], &arr[MAX]);
        heapify(arr, n, MAX);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vector initial: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    heapSort(arr, n);

    printf("\nVector sortat: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
