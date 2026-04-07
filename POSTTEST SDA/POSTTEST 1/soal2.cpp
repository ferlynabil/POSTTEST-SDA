#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {

    const int n = 5;
    Mahasiswa mhs[n];

    cout << "=== INPUT DATA MAHASISWA ===" << endl;
    for(int i = 0; i < n; i++) {
        cout << "\nMahasiswa ke-" << i+1 << endl;
        cout << "Nama : ";
        cin >> mhs[i].nama;
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
    }

    float ipkTertinggi = mhs[0].ipk;
    int indeks = 0;

    for(int i = 1; i < n; i++) {
        if(mhs[i].ipk > ipkTertinggi) {
            ipkTertinggi = mhs[i].ipk;
            indeks = i;
        }
    }

    cout << "\n=== MAHASISWA DENGAN IPK TERTINGGI ===" << endl;
    cout << "Nama : " << mhs[indeks].nama << endl;
    cout << "NIM  : " << mhs[indeks].nim << endl;
    cout << "IPK  : " << mhs[indeks].ipk << endl;

    return 0;
}