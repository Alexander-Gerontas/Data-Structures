/// Αλέξανδρος Γέροντας - ICSD15029

#include <iostream>
#include <cstdlib>
#include <ctime>

#define LIMIT 30000

clock_t start, end;
int key;

// Αποτελέσματα
void printResults(double elapsed, double cmps, double found) {
    std::cout << "Μέσος όρος συγκρίσεων: " << cmps/1000 << std::endl;
    std::cout << "Μέσος χρόνος αναζητήσεων: " << elapsed/1000 << std::endl;
    std::cout << "Ποσοστό επιτυχημένων αναζητήσεων: " << found/10 << "%" << std::endl;
}

// Συνάρτηση γραμμικής
void linearSearch (int arraySize) {
    int *A = new int[arraySize];
    double elapsed=0, found=0, cmps=0;

    for (int i=0; i<arraySize; i++)
        // Τυχαίοι ακεραίοι διαστήματος [0,LIMIT]
        A[i] = rand() % LIMIT;

    for (int i=0; i<1000; i++) {
        key = rand() % LIMIT;

        start = clock();

        for (int j = 0; j < arraySize; j++) {
            cmps++;

            if (A[j] == key) {
                found++;
                break;
            }
        }

        end = clock();

        elapsed += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    printResults(elapsed, cmps, found);
}

// Συνάρτη δυαδικής
void binarySearch (int arraySize) {
    int *A = new int[arraySize];
    double elapsed=0, found=0, cmps=0;
    int low, mid, high;

    A[0] = 1 + rand() % 3;

    for (int i = 1; i < arraySize; i++ )
        A[i] = A[i - 1] + 1 + rand() % 3;

    for (int i=0; i<1000; i++) {
        // To low και το high αρχικοποιούνται
        // για κάθε αναζήτηση
        low = 0;
        high = arraySize - 1;

        // Σαν όριο του διαστήματος δίνεται
        // ο μεγαλύτερος αριθμός του πίνακα
        key = rand() % A[high];

        start = clock();

        while (low <= high) {
            mid = (low + high) / 2;
            cmps++;

            if (A[mid] == key) {
                found++;
                break;
            }

            else if (A[mid] > key) high = mid - 1;

            else low = mid + 1;
        }

        end = clock();

        elapsed += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    printResults(elapsed, cmps, found);
}

int main (void) {
    // Δώθηκε η time για να αλλάζουν τα αποτελέσματα
    srand(time(NULL));
    int arraySize, choice;

    std::cout << "Array size: ";
    std::cin >> arraySize;

    std::cout << "1. Linear search" << std::endl;
    std::cout << "2. Binary search" << std::endl;
    std::cout << ">> ";

    std::cin >> choice;

    if (choice == 1) {
        std::cout << std::endl << "Linear search results:" << std::endl;
        linearSearch(arraySize);
    }

    if (choice == 2) {
        std::cout << std::endl << "Binary search results:" << std::endl;
        binarySearch(arraySize);
    }

    return 0;
}
