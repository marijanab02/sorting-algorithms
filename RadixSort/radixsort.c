#include <stdio.h>
#include <stdlib.h>

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Funkcija za implementaciju Counting Sorta prema danom eksponentu (znamenki)
void counting(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int i;
    int count[10] = {0}; //Niz od 10 elemenata (Dekadski sustav)

    if (output == NULL) {
        fprintf(stderr, "Neuspješno alociranje memorije!\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void radixSort(int arr[], int size) {
    int m = findMax(arr, size);

    // Sortiraj prema svakoj znamenki pomoću Counting Sorta
    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting(arr, size, exp);
    }
}