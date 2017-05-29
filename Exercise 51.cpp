/// �������� ���������� ��������� - ICSD14093
/// ���������� �������� - ICSD15029

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
    Sorter() /// A����������� �����.
    {
        cmp=0;
        elapsed = 0;
        cout << "Dose megethos: ";
        cin >> size;
    }

    void initializeArray() /// A����������� ������ �������� size.
    {
        arr = new unsigned long int[size];

        for (int i=0; i<size; i++)
            arr[i] = rand() % 50001;
    }

    /// �nsertion Sort

    void insertionSort()
    {
        int j;
        clock_t start = clock();

        for (int i=1; i<size; i++)
        {
            j = i;

            /// T��������� ��������� ������ arr[] ��� 0 �� j.
            while (j > 0 && arr[j] < arr[j-1])
            {
                cmp++; /// �������� ����������
                swap(arr[j--],arr[j-1]);
            }
        }

        /// Y���������� ������ ���������
        elapsed += ((double) (clock() - start)) / CLOCKS_PER_SEC;
    }

    /// Quick Sort

    bool compare(int lhs,int rhs) /// �������� ���� ��������� ��� ������ �� �� pivot ��� ������ ��� ������� ����������.
    {
        cmp++;
        return lhs < rhs;
    }

    void quickSort(int left, int right)
    {
        /// �� ���� ��� ��������� pivot �� ��������� ��� ������ �� ��� ����.
        /// ��� ����� ���������� �� o������� ��� ������������ �������� ��� ������ ��o pivot,
        /// ������ � ������� ��� ����� ������� ����� �� ���� ��������� � ������ ��������� ��� ����������.
        int pivot = arr[(left + right) / 2];
        int i = left, j = right;

        /// X������� ��� ������ arr[] �� ��� ���� ���� �� ����� ����� ���� ��������
        /// ��������� � ��� ��� pivot ��� �� ������� ���� �������� ���������� � ��� ��� pivot.
        while (i <= j)
        {
            while (compare(arr[i],pivot)) i++;
            while (compare(pivot,arr[j])) j--;

            if (i <= j) swap(arr[i++],arr[j--]);
        };

        /// A������� ��� ��� ���������� ��� ������ ��� ��� �������� ������ ��� ������.
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

        /// ����������� ���������� �������.
        unsigned long int *L = new unsigned long int[n1];
        unsigned long int *H = new unsigned long int[n2];

        /// ��������� ��������� ��� ��� ������ arr[] ����� ����������� �������.
        for (i = 0; i < n1; i++) L[i] = arr[low + i];
        for (j = 0; j < n2; j++) H[j] = arr[mid + 1+ j];

        i = 0; /// M������� ������������ ���������� ��� ��� ����� ��������� ������ ���� arr[].
        j = 0; /// M������� ������������ ���������� ��� ��� ������� ��������� ������ ���� arr[].
        k = low; /// M������� ���������� ��� ������������� ���� ������ arr[] ��� ��� ���� ��� ����������� �������.

        /// �������� ���������� ������� ���� ������ arr[].
        while (i < n1 && j < n2)
        {
            if (L[i] <= H[j]) arr[k++] = L[i++];
            else arr[k++] = H[j++];
            cmp++;
        }

        /// ��������� ������������� ��������� ��� ���� ����������� �������, �� ��������.
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = H[j++];
    }

    void mergeSort(int low, int high)
    {
        if (low < high)
        {
            int mid = low+(high-low)/2;

            /// X������� ��� ������ �� ��� ��� ����
            /// ��� �������� ��� �� ������������.
            mergeSort(low,mid);
            mergeSort(mid+1,high);
            merger(low, mid, high); /// ���������� ��� �������� ��� ��� �������.
        }
    }

    void mergeSort()
    {
        clock_t start = clock();
        mergeSort(0,size-1);
        elapsed += ((double) (clock() - start)) / CLOCKS_PER_SEC;
    }

    /// ������������.

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
