#include <stdio.h>
#include <stdlib.h>

int static findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
void countingSort(int arr[], int size) {
    int max = findMax(arr, size), i;
    int* count = (int*)calloc(max + 1, sizeof(int));
    int* output = (int*)malloc(size * sizeof(int));

    if (count == NULL || output == NULL) {
        fprintf(stderr, "Neuspješno alociranje memorije!\n");
        exit(EXIT_FAILURE);
    }

    // Brojanje pojavljivanja svakog broja
    for (i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    // Kumulativni zbroj
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
    // Izgradnja sortirane verzije ulaznog niza
    for (i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Kopiranje sortirane verzije u originalni niz
    for (i = 0; i < size; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}