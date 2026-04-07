
// Analisis Kompleksitas Waktu FindMin

// Best Case:
// Terjadi ketika array sudah terurut menaik.
// Tidak pernah terjadi update min.

// T(n) = 2n + 2
// Big-O = O(n)

// Worst Case:
// Terjadi ketika array terurut menurun.
// Selalu terjadi update min sebanyak n-1 kali.

// T(n) = 4n - 1
// Big-O = O(n)

// Kesimpulan:
// Tmin(n) = O(n)
// Tmax(n) = O(n)
// Kompleksitas Ruang = O(1)

#include <iostream>
using namespace std;

int FindMin(int A[], int n, int &indexMin)
{
    int min = A[0];
    indexMin = 0;

    for(int i = 1; i < n; i++)
    {
        if(A[i] < min)
        {
            min = A[i];
            indexMin = i;
        }
    }

    return min;
}

int main()
{
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indeks;

    cout << "Array Fibonacci: ";
    for(int i = 0; i < 8; i++)
    {
        cout << A[i] << " ";
    }

    cout << endl;

    int minimum = FindMin(A, 8, indeks);

    cout << "Nilai minimum  = " << minimum << endl;
    cout << "Indeks minimum = " << indeks << endl;

    return 0;
}