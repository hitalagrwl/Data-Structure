#include <stdio.h>

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    int i, temp;

    // Build max heap
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Delete elements from heap
    for (i = n - 1; i > 0; i--) {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main() {
    int a[] = {35, 33, 42, 10, 14, 19, 27, 44, 26, 31};
    int n = 10;

    heapSort(a, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}