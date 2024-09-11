#include <stdio.h>
#include <stdlib.h>

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
// Funkcija za ispis hrpe
void printTree(int arr[], int size, int i, int indent) {
    if (i >= size)
        return;
    
    printTree(arr, size, 2 * i + 2, indent + 4);

    if (indent) 
        printf("%*s", indent, " ");
    
    printf("%d\n", arr[i]);

    printTree(arr, size, 2 * i + 1, indent + 4);
}

void heapify(int arr[], int size, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    // Ako je lijevo dijete veće od korijena
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // Ako je desno dijete veće od trenutnog najvećeg
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // Ako najveći nije korijen
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        
        // Rekurzivno heapify pod-pod-stablo
        heapify(arr, size, largest);
    }

}

void heapSort(int arr[], int size) {
    // Izgradi max heap
    for (int i = size / 2 - 1; i >= 0; i--){
        heapify(arr, size, i);
    }
    // Jedan po jedan element izvadi iz hrpe
    for (int i = size - 1; i >= 0; i--) {
        // Pomakni trenutni korijen u kraj
        swap(&arr[0], &arr[i]);

        // Pozovi heapify na smanjenoj hrpi
        heapify(arr, i, 0);
    }
}