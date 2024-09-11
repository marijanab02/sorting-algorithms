#include <stdio.h>

void static swap(int* x, int* y) {
    int t = *x;
    *x = *y;
    *y = t;
}
void static printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
// Funkcija za pronalaženje medijana od tri broja
int medianOfThree(int a, int b, int c) {
    if ((a > b) != (a > c)) {
        return a;
    } else if ((b > a) != (b > c)) {
        return b;
    } else {
        return c;
    }
}

// Funkcija za particioniranje niza koristeći medijan od tri elementa kao pivot
int partition(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    int pivot = medianOfThree(arr[low], arr[mid], arr[high]);

    // Zamjena pivota s posljednjim elementom kako bi pivot bio na kraju
    if (pivot == arr[mid]) {
        swap(&arr[mid], &arr[high]);
    } else if (pivot == arr[low]) {
        swap(&arr[low], &arr[high]);
    }
    
    pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        //Sortiranje elemenata prije i poslje p
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

