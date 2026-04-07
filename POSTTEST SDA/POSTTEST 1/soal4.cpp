#include <iostream>
using namespace std;

void tukarNilai(int *angka1, int *angka2) {
    int penyimpananSementara;

    penyimpananSementara = *angka1;
    *angka1 = *angka2;
    *angka2 = penyimpananSementara;
}

int main() {
    int bilanganA, bilanganB;

    cout << "===== PROGRAM PERTUKARAN NILAI (POINTER) =====" << endl;
    cout << "Masukkan nilai pertama  : ";
    cin >> bilanganA;
    cout << "Masukkan nilai kedua    : ";
    cin >> bilanganB;

    cout << "\nSebelum ditukar:" << endl;
    cout << "Nilai pertama  = " << bilanganA << endl;
    cout << "Nilai kedua    = " << bilanganB << endl;

    tukarNilai(&bilanganA, &bilanganB);

    cout << "\nSesudah ditukar:" << endl;
    cout << "Nilai pertama  = " << bilanganA << endl;
    cout << "Nilai kedua    = " << bilanganB << endl;

    return 0;
}