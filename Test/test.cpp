#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
#include "../QuickSort/quicksort.h"
#include "../MergeSort/mergesort.h"
#include "../CountingSort/countingsort.h"
#include "../RadixSort/radixsort.h"  
#include "../HeapSort/heapsort.h"  
using namespace std;

// Funkcija za dobivanje trenutnog vremena u mikrosekundama
int64_t rtime_us() {
    return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now()
        .time_since_epoch())
        .count();
}

void read_numbers_from_file(const char* filename, vector<int>& numbers) {
    ifstream infile(filename);
    int number;
    while (infile >> number) {
        numbers.push_back(number);
    }
}

void test_heapsort(std::vector<int> numbers) {
    int size = numbers.size();

    auto start = rtime_us();
    heapSort(&numbers[0], size);
    
    std::cout << "Vrijeme trajanja heapsort funkcije: " 
              << rtime_us() - start << " mikrosekundi" << std::endl;
}

void test_mergesort(std::vector<int> numbers) {
    int size = numbers.size();

    auto start = rtime_us();
    mergeSort(&numbers[0], 0, size - 1);
    
    std::cout << "Vrijeme trajanja mergesort funkcije: " 
              << rtime_us() - start << " mikrosekundi" << std::endl;
}

void test_quicksort(std::vector<int> numbers) {
    int size = numbers.size();

    auto start = rtime_us();
    quickSort(&numbers[0], 0, size - 1);
    
    std::cout << "Vrijeme trajanja quicksort funkcije: " 
              << rtime_us() - start << " mikrosekundi" << std::endl;

}

void test_countingsort(std::vector<int> numbers) {
    int size = numbers.size();

    auto start = rtime_us();
    countingSort(&numbers[0], size);
    
    std::cout << "Vrijeme trajanja countingsort funkcije: " 
              << rtime_us() - start << " mikrosekundi" << std::endl;
}

void test_radixsort(std::vector<int> numbers) {
    int size = numbers.size();

    auto start = rtime_us();
    radixSort(&numbers[0], size);
    
    std::cout << "Vrijeme trajanja radixsort funkcije: " 
              << rtime_us() - start << " mikrosekundi" << std::endl;

}

void test_algorithms(const vector<string>& filenames) {
    for (const auto& filename : filenames) {
        vector<int> numbers;
        read_numbers_from_file(filename.c_str(), numbers);

        if (numbers.empty()) {
            cerr << "Datoteka " << filename << " je prazna ili nije pronađena!" << endl;
            continue;
        }

        cout << "Testiranje Heapsort-a za datoteku " << filename << ":" << endl;
        test_heapsort(numbers);
        
        cout << "Testiranje MergeSort-a za datoteku " << filename << ":" << endl;
        test_mergesort(numbers);

        cout << "Testiranje QuickSort-a za datoteku " << filename << ":" << endl;
        test_quicksort(numbers);

        cout << "Testiranje CountingSort-a za datoteku " << filename << ":" << endl;
        test_countingsort(numbers);

        cout << "Testiranje RadixSort-a za datoteku " << filename << ":" << endl;
        test_radixsort(numbers);

    }
}

int main() {
    vector<string> filenames = {
        "../Generate/numbers_1000.txt",
        "../Generate/numbers_10000.txt",
        "../Generate/numbers_50000.txt",
        "../Generate/numbers_100000.txt",
        "../Generate/numbers_1000000.txt",
        "../Generate/numbers_10000000.txt",
        "../Generate/sorted_numbers_10000000.txt",
        "../Generate/partially_sorted_numbers_10000000.txt",
        "../Generate/sorted_numbers_10000000_desc.txt",
        "../Generate/partially_sorted_numbers_10000000_desc.txt",
    };

    test_algorithms(filenames);
    return 0;
}
