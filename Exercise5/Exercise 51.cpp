/// Νικόλαος Παναγιώτης Κούκουρας - ICSD14093
/// Αλέξανδρος Γέροντας - ICSD15029

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Sorter
{
private:
    unsigned long int *arr,cmp;
    int size;
    double elapsed;

public:
    Sorter() /// Aρχικοποίηση τιμών.
    {
        cmp=0;
        elapsed = 0;
        cout << "Dose megethos: ";
        cin >> size;
    }

    void initializeArray() /// Aρχικοποίηση πίνακα μεγέθους size.
    {
        arr = new unsigned long int[size];

        for (int i=0; i<size; i++)
            arr[i] = rand() % 50001;
    }

    /// Ιnsertion Sort

    void insertionSort()
    {
        int j;
        clock_t start = clock();

        for (int i=1; i<size; i++)
        {
            j = i;

            /// Tαξινόμηση στοιχείων πίνακα arr[] από 0 ως j.
            while (j > 0 && arr[j] < arr[j-1])
            {
                cmp++; /// Μετρητής συγκρίσεων
                swap(arr[j--],arr[j-1]);
            }
        }

        /// Yπολογισμός χρόνου εκτέλεσης
        elapsed += ((double) (clock() - start)) / CLOCKS_PER_SEC;
    }

    /// Quick Sort

    bool compare(int lhs,int rhs) /// Σύγκριση ενός στοιχείου του πίνακα με το pivot και αύξηση του μετρητή συγκρίσεων.
    {
        cmp++;
        return lhs < rhs;
    }

    void quickSort(int left, int right)
    {
        /// Με βάση την μεταβλητή pivot θα χωρίσουμε τον πίνακα σε δύο μέρη.
        /// Δεν είναι απαραίτητο να oρίσουμε ένα συγκεκριμένο στοιχείο του πίνακα στo pivot,
        /// ώστωσο η επιλογή του είναι κρίσιμη καθώς σε αυτό βασίζεται ο χρόνος εκτέλεσης του αλγόριθμου.
        int pivot = arr[(left + right) / 2];
        int i = left, j = right;

        /// Xωρισμός του πίνακα arr[] σε δύο μέρη όπου το πρώτο μέρος έχει στοιχεία
        /// μικρότερα η ίσα του pivot ενώ το δεύτερο έχει στοιχεία μεγαλύτερα ή ίσα του pivot.
        while (i <= j)
        {
            while (compare(arr[i],pivot)) i++;
            while (compare(pivot,arr[j])) j--;

            if (i <= j) swap(arr[i++],arr[j--]);
        };

        /// Aναδρομή για την ταξινόμηση του πρώτου και του δεύτερου μέρους του πίνακα.
        if (left < j) quickSort(left, j);
        if (i < right) quickSort(i, right);
    }

    void quickSort()
    {
        clock_t start = clock();
        quickSort(0,size-1);
        elapsed += ((double) (clock() - start)) / CLOCKS_PER_SEC;
    }

    /// Merge Sort
    void merger(int low, int mid, int high)
    {
        int i, j, k;
        int n1 = mid - low + 1;
        int n2 = high - mid;

        /// Δημιουργίοα προσωρινών πινάκων.
        unsigned long int *L = new unsigned long int[n1];
        unsigned long int *H = new unsigned long int[n2];

        /// Αντιγραφή δεδομένων απο τον πίνακα arr[] στους προσωρινούς πίνακες.
        for (i = 0; i < n1; i++) L[i] = arr[low + i];
        for (j = 0; j < n2; j++) H[j] = arr[mid + 1+ j];

        i = 0; /// Mετρητής αντεγραμένων μεταβλητών από τον πρώτο προσωρινό πίνακα στον arr[].
        j = 0; /// Mετρητής αντεγραμένων μεταβλητών από τον δεύτερο προσωρινό πίνακα στον arr[].
        k = low; /// Mετρητής μεταβλητών που αντιγράφτηκαν στον πίνακα arr[] και από τους δύο προσωρινούς πίνακες.

        /// Συνένωση προσωρινών πινάκων στον πίνακα arr[].
        while (i < n1 && j < n2)
        {
            if (L[i] <= H[j]) arr[k++] = L[i++];
            else arr[k++] = H[j++];
            cmp++;
        }

        /// Αντιγραφή υπολειπόμενων δεδομένων από τους προσωρινούς πίνακες, αν υπάρχουν.
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = H[j++];
    }

    void mergeSort(int low, int high)
    {
        if (low < high)
        {
            int mid = low+(high-low)/2;

            /// Xωρισμός του πίνακα σε δύο ίσα μέρη
            /// και αναδρομή για να ταξινομηθούν.
            mergeSort(low,mid);
            mergeSort(mid+1,high);
            merger(low, mid, high); /// Ταξινόμηση και συνένωση των δύο πίνακων.
        }
    }

    void mergeSort()
    {
        clock_t start = clock();
        mergeSort(0,size-1);
        elapsed += ((double) (clock() - start)) / CLOCKS_PER_SEC;
    }

    /// Αποτελέσματα.

    void display()
    {
        for (int i=0; i<size; i++)
            cout << arr[i] << endl;
    }

    void results()
    {
        cout << "Mesos arithmos sigriseon: " << cmp/100 << endl;
        cout << "Mesos xronos taksinomisis: " << elapsed/100 << endl;
    }
};

int main()
{
    Sorter *sort = new Sorter();
    srand(time(NULL));
    int choice = -1;

    cout << "1.Algorithmos <<Insertion Sort>> \n";
    cout << "2.Algorithmos <<Merge Sort>> \n";
    cout << "3.Algorithmos <<Quick Sort>> \n";
    cout << "0.Eksodos\n>>";

    cin >> choice;

    for (int i=0; i<100; i++)
    {
        sort->initializeArray();

        if (choice == 1) sort->insertionSort();
        else if (choice == 2) sort->mergeSort();
        else if (choice == 3) sort->quickSort();
        else break;

        sort->display();
    }

    if (choice != 0) sort->results();

    return 0;
}
