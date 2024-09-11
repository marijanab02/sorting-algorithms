// generate_random_files.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_SIZE 1000  // Početna veličina za dinamičko alociranje
#define GROWTH_FACTOR 10   // Faktor rasta kapaciteta
#define MAX_SWAP_PERCENTAGE 8

void generate_random_file(const char* filename, int num_elements) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Ne mogu otvoriti datoteku %s za pisanje!\n", filename);
        return;
    }
	int i;
    srand(time(0));
    for (i = 0; i < num_elements; i++) {
        fprintf(fp, "%d\n", rand() % 1000000);  // Generira brojeve u rasponu od 0 do 999999
    }

    fclose(fp);
}
int* read_numbers_from_file(const char* filename, int* num_elements) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Ne mogu otvoriti datoteku %s za čitanje!\n", filename);
        return NULL;
    }

    // Početni kapacitet za memoriju
    int capacity = 1000;
    int *numbers = malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        printf("Nema dovoljno memorije za pohranu brojeva!\n");
        fclose(fp);
        return NULL;
    }

    *num_elements = 0;
    while (fscanf(fp, "%d", &numbers[*num_elements]) == 1) {
        (*num_elements)++;
        if (*num_elements >= capacity) {
            capacity *= 10;  // Povećaj kapacitet za faktor rasta
            int *temp = realloc(numbers, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Ne može se alocirati više memorije!\n");
                free(numbers);
                fclose(fp);
                return NULL;
            }
            numbers = temp;
        }
    }

    fclose(fp);
    return numbers;
}
// Funkcija za pohranu brojeva u datoteku
void write_numbers_to_file(const char* filename, int* numbers, int num_elements) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Ne mogu otvoriti datoteku %s za pisanje!\n", filename);
        return;
    }

    for (int i = 0; i < num_elements; i++) {
        fprintf(fp, "%d\n", numbers[i]);
    }

    fclose(fp);
}

// Funkcija za usporedbu dvaju brojeva (uzlazno sortiranje)
int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Funkcija za usporedbu dvaju brojeva (silazno sortiranje)
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}
// Funkcija za zamjenu elemenata u nizu
void swap_elements(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


void sort_numbers_file(const char* input_filename, const char* output_filename, int ascending) {
    int num_elements;
    int *numbers = read_numbers_from_file(input_filename, &num_elements);
    if (numbers == NULL) return;

    // Odaberi funkciju usporedbe na temelju željenog redoslijeda
    int (*compare_func)(const void*, const void*) = ascending ? compare_asc : compare_desc;

    // Sortiraj brojeve
    qsort(numbers, num_elements, sizeof(int), compare_func);

    // Spremi sortirane brojeve u novu datoteku
    write_numbers_to_file(output_filename, numbers, num_elements);

    free(numbers);

    printf("Datoteka %s je sortirana i spremljena kao %s.\n", input_filename, output_filename);
}

void generate_partially_sorted_file(const char* input_filename, const char* output_filename) {
    int num_elements;
    int *numbers = read_numbers_from_file(input_filename, &num_elements);
    if (numbers == NULL) return;

    // Broj elemenata koji se mogu zamijeniti
    int max_swaps = (num_elements * MAX_SWAP_PERCENTAGE) / 100;

    // Nasumično zamijeniti do 8% elemenata
    srand(time(NULL));
    for (int i = 0; i < max_swaps; i++) {
        int idx1 = rand() % num_elements;
        int idx2 = rand() % num_elements;
        swap_elements(numbers, idx1, idx2);
    }

    // Spremi donekle sortirane brojeve u novu datoteku
    write_numbers_to_file(output_filename, numbers, num_elements);

    free(numbers);

    printf("Donekle sortirana datoteka %s je uspješno kreirana kao %s.\n", input_filename, output_filename);
}



int main() {
    generate_random_file("numbers_1000.txt", 1000);
    generate_random_file("numbers_10000.txt", 10000);
    generate_random_file("numbers_50000.txt", 50000);
    generate_random_file("numbers_100000.txt", 100000);
    generate_random_file("numbers_1000000.txt", 1000000);
    generate_random_file("numbers_10000000.txt", 10000000);
    sort_numbers_file("numbers_10000000.txt", "sorted_numbers_10000000.txt", 1);
    sort_numbers_file("numbers_10000000.txt", "sorted_numbers_10000000_desc.txt", 0);
    generate_partially_sorted_file("sorted_numbers_10000000.txt", "partially_sorted_numbers_10000000.txt");
    generate_partially_sorted_file("sorted_numbers_10000000_desc.txt", "partially_sorted_numbers_10000000_desc.txt"); 

    printf("Datoteke su uspjesno generirane.\n");
    return 0;
}
