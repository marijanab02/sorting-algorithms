#include <stdio.h>
#include <stdlib.h>

// Funkcija za ispis niza
void static printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
// Funkcija koja spaja dva podniza arr[]
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1; 
    int n2 = right - middle;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Neuspješno alociranje memorije!\n");
        exit(EXIT_FAILURE);
    }

    // Kopiranje podataka u privremene nizove L[] i R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    // Spajanje natrag u arr[]
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

    // Kopiranje preostalih elemenata iz L[] i R[], ako ih ima
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
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Sortiranje prve i druge polovice
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Spajanje sortiranih polovica
        merge(arr, left, middle, right);
    }
}