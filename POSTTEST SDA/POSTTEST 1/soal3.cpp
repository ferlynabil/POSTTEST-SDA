#include <iostream>
using namespace std;

void reverseArray(int* arr, int n)
{
    int* awal = arr;           
    int* akhir = arr + n - 1;  
    while(awal < akhir)
    {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

int main()
{
    int data[7] = {2, 3, 5, 7, 11, 13, 17};

    for(int i = 0; i < 7; i++)
    {
        cout << "Nilai: " << data[i]
             << " | Alamat: " << &data[i] << endl;
    }

    reverseArray(data, 7);

    for(int i = 0; i < 7; i++)
    {
        cout << "Nilai: " << data[i]
             << " | Alamat: " << &data[i] << endl;
    }

    return 0;
}