#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void func()
{

    srand(time(0));

    clock_t start, end;

    double elapsed = 0;

    int N,r;

    int cmp = 0,found = 0;

    cout << "dose to megethos tou pinaka" << endl;

    cin >> N;

    int *A = new int[N];

    for (int i = 0; i < N; i++)
    {
        *(A+i) = (rand() % 30000) + 1;
        //cout << *(A+i) << endl;
    }

    for (int i = 0; i < 1000; i++)
    {
        r = (rand() % 30000) + 1;

        start = clock();

        for (int j = 0; j < N; j++)
        {
            cmp++;

            if ( A[j] == r )
            {
                found++;
                break;
            }

        }

        end = clock();

        elapsed += ((double) (end - start)) / CLOCKS_PER_SEC;

    }

    cout << "mesos arithmos sigriseon: " << cmp / 1000 << endl;
    cout << "mesos xronos anazitisis: " << elapsed/1000 << endl;
    cout << "pososto epitiximenon anazitiseon: " << found/10 << "%" << endl;

}

void linearSearch()
{
    int N;

    srand(time(0));

    cout << "dose to megethos tou pinaka" << endl;
    cin >> N;

    int mid;

    int *A = new int[N];

    int cmp = 0,found = 0;

    clock_t start, end;

    double elapsed = 0;

    A[0] = 1 + (rand() % 3);

    for (int i = 1; i < N; i++){
        A[i] = A[i - 1] + 1 + rand() % 3;//}
        cout << A[i] << endl;}

    int r;

    for (int i = 0; i < 1000; i++)
    {

        int low = 0;
        int up = N - 1;

        r = rand() % A[up];

        start = clock();

        while (low <= up)
        {
            mid = (low + up) / 2;

            cmp++;

            if ( A[mid] == r )
            {
                found++;
                break;
            }

            else if (A[mid] > r) up = mid - 1;
            else low = mid + 1;

        }

        end = clock();
        elapsed += ((double) (end - start)) / CLOCKS_PER_SEC;

    }

    cout << "mesos arithmos sigriseon: " << cmp / 1000 << endl;
    cout << "mesos xronos anazitisis: " << elapsed/1000 << endl;
    cout << "pososto epitiximenon anazitiseon: " << found/10 << "%" << endl;

}

int main()
{
    //func();

    linearSearch();

    return 0;
}
