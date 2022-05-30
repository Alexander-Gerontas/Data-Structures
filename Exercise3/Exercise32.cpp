/// ÃÝñïíôáò ÁëÝîáíäñïò - 321/2015029

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void printArray(int *array, int size) /// ÅìöÜíéóç ðßíáêá óùñïý.
{
    for (int i = 1; i < size; i++)
        cout << i <<". " << array[i] << endl;
}

void printHeapTree(int *array, int size) /// ÅìöÜíéóç óùñïý óå «äåíäñïåéäÞ» áíáðáñÜóôáóç.
{
    int x = 1;

    for (int i = 1; i < size; i++)
    {
        cout << array[i] << " ";

        if ( i == 2*x + 1 || i == 1 )
        {
            cout << endl;
            x = i;
        }
    }

    cout << endl << endl;
}

int Left(int i) /// ÅðéóôñïöÞ áñéóôåñïý ðáéäéïý.
{
    return 2*i;
}

int Right(int i) /// ÅðéóôñïöÞ äåîéïý ðáéäéïý.
{
    return (2*i) + 1;
}

int Parent(int i) /// ÅðéóôñïöÞ ôïõ ãïíÝá.
{
    return i/2;
}

void createArray(int* array, int size) /// Äçìéïõñãßá ðßíáêá ôõ÷áßùí.
{
    srand(time(NULL));

    for (int i = 1; i < size; i++)
        array[i] = rand () % 100 + 1;
}

void fixHeap(int* array,int size, int i) /// Óõãñßíåé ôïí ðáôåñá ôïõ õðüäåíôñïõ ìå ôá ðáéäéÜ ôïõ êáé êÜíåé swap ìå ôï ìåãáëýôåñï ðáéäß.
{
    int largest = i;
    int left = Left(i);
    int right = Right(i);

    if (left < size && array[left] > array[largest]) largest = left;
    if (right < size && array[right] > array[largest]) largest = right;

    if (largest != i)
    {
        swap(array[i], array[largest]);
        fixHeap(array,size,largest); /// H fixHeap ëåéôïõñãåß áíáäñïìéêÜ, êáé óôáìáôÜåé üôáí ôï óôïé÷åßï ôïðïèåôçèåé óôç óùóôç èÝóç.
    }
}

void createHeap(int *array,int size) /// Äçìéïõñãßá óùñïý áðü ðßíáêá.
{
    for (int i = size/2; i > 0; i--)
        fixHeap(array,size,i);
}

void heapSort(int *array,int size) /// Ôáîéíüìçóç êé åìöÜíéóç ôáîéíïìçìÝíïõ ðßíáêá.
{
    //createHeap(array,size);

    for (int i = size - 1; i > 0; i--)
    {
        swap(array[1],array[i]);
        fixHeap(array,i,1);
    }

    printArray(array,size);
}

void resize(int *&array, int& size) /// Äçìéïõñãéá êáéíïýñéïõ ðßíáêá ìå ìÝãåèïò size + 1.
{
    int *tempArray = array;
    array = new int[++size];

    for (int i = 1; i < size - 1; i++)
        array[i] = tempArray[i];
}

void insertHeap(int *&array, int &size) /// ÐñïóèÞêç íÝïõ óôïé÷åßïõ óôï óùñü.
{
    int value;

    cout << "Dose ton arithmo pou thes na eisageis: ";
    cin >> value;

    resize(array,size);
    array[size - 1] = value;

    int i = size - 1;

    while (i > 1 && array[Parent(i)] < array[i])
    {
        swap(array[Parent(i)],array[i]);
        i = Parent(i);
    }
}

int main()
{
    int size = 21;
    int *array = NULL;
    int choice = -1;

    while (choice != 0)
    {
        cout << "1. Dimiourgia pinaka tixaion\n";
        cout << "2. Dimiourgia sorou apo pinaka.\n";
        cout << "3. Prosthiki neou stoixeiou sto soro \n";
        cout << "4. Emfanisi pinaka sorou\n";
        cout << "5. Emfanisi sorou se <<dentroeidi>> anaparastasi\n";
        cout << "6. Taksinomisi ki emfanisi taksinomimenou pinaka\n";
        cout << "0. Eksodos\n";

        cin >> choice;

        if (choice == 1) createArray(array = new int[size],size);
        else if (array == NULL)  cout << "Dn exete dimiourgisi pinaka tixaion\n";
        else if (choice == 2 && array != NULL) createHeap(array,size);
        else if (choice == 3) insertHeap(array,size);
        else if (choice == 4) printArray(array,size);
        else if (choice == 5) printHeapTree(array,size);
        else if (choice == 6) heapSort(array,size);
    }

    return 0;
}

