#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Kereta {
    string nomorKereta;
    string namaKereta;
    string asalKota;
    string tujuanKota;
    string jamBerangkat;
    string jamTiba;
    int    hargaTiket;
    int    kursiTersedia;
};

const int MAKSIMAL = 100;
Kereta daftarKereta[MAKSIMAL];
int    jumlahKereta = 0;
int    iterasiMerge = 0;

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void cetakGaris(char karakter, int lebar) {
    cout << setfill(karakter) << setw(lebar) << karakter << setfill(' ') << endl;
}

void tampilkanJadwal(Kereta* arr, int n) {
    system("cls");
    cout << "--- JADWAL SEMUA KERETA API ---" << endl;
    if (n == 0) {
        cout << "Belum ada data kereta." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 108);
    cout << left
         << setw(4)  << "No"
         << setw(10) << "No.KA"
         << setw(22) << "Nama Kereta"
         << setw(14) << "Asal"
         << setw(14) << "Tujuan"
         << setw(11) << "Berangkat"
         << setw(8)  << "Tiba"
         << setw(15) << "Harga (Rp)"
         << setw(8)  << "Kursi" << endl;
    cetakGaris('-', 108);
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(4)  << i + 1
             << setw(10) << (arr + i)->nomorKereta
             << setw(22) << (arr + i)->namaKereta
             << setw(14) << (arr + i)->asalKota
             << setw(14) << (arr + i)->tujuanKota
             << setw(11) << (arr + i)->jamBerangkat
             << setw(8)  << (arr + i)->jamTiba
             << setw(15) << (arr + i)->hargaTiket
             << setw(8)  << (arr + i)->kursiTersedia << endl;
    }
    cetakGaris('=', 108);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tambahKereta(Kereta*& arr, int& jumlah) {
    system("cls");
    if (jumlah >= MAKSIMAL) {
        cout << "Data kereta sudah penuh!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cout << "--- TAMBAH DATA KERETA BARU ---" << endl;
    cout << "Nomor Kereta   : "; cin >> (arr + jumlah)->nomorKereta;
    cin.ignore();
    cout << "Nama Kereta    : "; getline(cin, (arr + jumlah)->namaKereta);
    cout << "Kota Asal      : "; getline(cin, (arr + jumlah)->asalKota);
    cout << "Kota Tujuan    : "; getline(cin, (arr + jumlah)->tujuanKota);
    cout << "Jam Berangkat  : "; cin >> (arr + jumlah)->jamBerangkat;
    cout << "Jam Tiba       : "; cin >> (arr + jumlah)->jamTiba;
    cout << "Harga Tiket    : "; cin >> (arr + jumlah)->hargaTiket;
    cout << "Kursi Tersedia : "; cin >> (arr + jumlah)->kursiTersedia;
    jumlah++;
    cout << "\nData kereta berhasil ditambahkan!" << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void linearSearchRute(Kereta* arr, int n, string asal, string tujuan) {
    system("cls");
    cout << "--- LINEAR SEARCH: CARI BERDASARKAN RUTE ---" << endl;
    cout << "Rute yang dicari : " << asal << " --> " << tujuan << endl;
    cetakGaris('-', 75);

    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        cout << "Iterasi " << setw(2) << i + 1
             << " | [" << setw(6) << (arr + i)->nomorKereta << "]"
             << " | " << setw(12) << (arr + i)->asalKota
             << " -> " << setw(12) << (arr + i)->tujuanKota;
        if ((arr + i)->asalKota == asal && (arr + i)->tujuanKota == tujuan) {
            cout << " --> COCOK!" << endl;
            ditemukan = true;
        } else {
            cout << " --> Lewati" << endl;
        }
    }

    cout << endl;
    if (ditemukan) {
        cout << "=== HASIL PENCARIAN ===" << endl;
        cetakGaris('=', 108);
        cout << left
             << setw(4)  << "No"
             << setw(10) << "No.KA"
             << setw(22) << "Nama Kereta"
             << setw(14) << "Asal"
             << setw(14) << "Tujuan"
             << setw(11) << "Berangkat"
             << setw(8)  << "Tiba"
             << setw(15) << "Harga (Rp)"
             << setw(8)  << "Kursi" << endl;
        cetakGaris('-', 108);
        int no = 1;
        for (int i = 0; i < n; i++) {
            if ((arr + i)->asalKota == asal && (arr + i)->tujuanKota == tujuan) {
                cout << left
                     << setw(4)  << no++
                     << setw(10) << (arr + i)->nomorKereta
                     << setw(22) << (arr + i)->namaKereta
                     << setw(14) << (arr + i)->asalKota
                     << setw(14) << (arr + i)->tujuanKota
                     << setw(11) << (arr + i)->jamBerangkat
                     << setw(8)  << (arr + i)->jamTiba
                     << setw(15) << (arr + i)->hargaTiket
                     << setw(8)  << (arr + i)->kursiTersedia << endl;
            }
        }
        cetakGaris('=', 108);
    } else {
        cout << "Tidak ada kereta dengan rute " << asal << " --> " << tujuan << "." << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void sortByNomor(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nomorKereta > (arr + j + 1)->nomorKereta) {
                swapKereta(arr + j, arr + j + 1);
            }
        }
    }
}

void jumpSearchNomor(Kereta* arr, int n, string nomorCari) {
    system("cls");
    cout << "--- JUMP SEARCH: CARI BERDASARKAN NOMOR KERETA ---" << endl;
    cout << "Nomor yang dicari: " << nomorCari << endl;

    // jump Search mensyaratkan data terurut terlebih dahulu.
    // maka data diurutkan dulu berdasarkan nomorKereta (ascending)
    // menggunakan Bubble Sort di dalam sortByNomor().
    cout << "\nMengurutkan data berdasarkan nomor kereta dahulu..." << endl;
    sortByNomor(arr, n);
    cout << "Urutan setelah sort: ";
    for (int i = 0; i < n; i++)
        cout << (arr + i)->nomorKereta << (i < n - 1 ? " | " : "\n");

    // menentukan ukuran langkah (step) optimal untuk Jump Search.
    // rumus: step = sqrt(n), sehingga kompleksitas menjadi O(sqrt(n)).
    // contoh: n=6 -> step = sqrt(6) ~ 2
    int step  = (int)sqrt((double)n);
    int prev  = 0;   // menyimpan indeks awal blok saat ini
    int iterasi = 1;
    cout << "\nJumlah data: " << n << " | Step Jump: " << step << endl;
    cetakGaris('-', 68);

    // fase 1
    // algoritma melompat sebesar 'step' indeks sekali jalan.
    // selama elemen di ujung blok masih LEBIH KECIL dari target,
    // terus melompat ke blok berikutnya.
    // tujuan: mempersempit rentang pencarian menjadi satu blok saja.
    int batas = (step < n ? step : n) - 1;
    while ((arr + batas)->nomorKereta < nomorCari) {
        cout << "Jump Iterasi " << setw(2) << iterasi++
             << " | Indeks [" << setw(2) << batas << "]"
             << " | [" << (arr + batas)->nomorKereta << "] < " << nomorCari
             << " --> Lompat!" << endl;
        // geser 'prev' ke posisi 'step' saat ini,
        // lalu tambah 'step' lagi untuk blok berikutnya.
        prev   = step;
        step  += (int)sqrt((double)n);
        batas  = (step < n ? step : n) - 1;

        // jika 'prev' sudah melewati ujung array,
        // berarti elemen tidak ada di seluruh data.
        if (prev >= n) {
            cout << "\nNomor kereta [" << nomorCari << "] tidak ditemukan." << endl;
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();
            return;
        }
    }

    // fase 2
    // setelah blok target ditemukan (elemen di batas >= target),
    // lakukan pencarian linear dari indeks 'prev' sampai 'batas'.
    // rentang ini dijamin kecil (maksimal sqrt(n) elemen),
    // sehingga tetap efisien.
    int akhir = (step < n ? step : n);
    cout << "\nFase Linear Search dari indeks " << prev << " hingga " << akhir - 1 << ":" << endl;
    while (prev < akhir) {
        cout << "Linear Iterasi " << setw(2) << iterasi++
             << " | Indeks [" << setw(2) << prev << "]"
             << " | [" << (arr + prev)->nomorKereta << "]";

        // bandingkan satu per satu hingga nomor kereta cocok.
        if ((arr + prev)->nomorKereta == nomorCari) {
            cout << " --> DITEMUKAN!" << endl;
            cetakGaris('=', 60);
            cout << "Nomor Kereta   : " << (arr + prev)->nomorKereta   << endl;
            cout << "Nama Kereta    : " << (arr + prev)->namaKereta    << endl;
            cout << "Rute           : " << (arr + prev)->asalKota
                                        << " --> " << (arr + prev)->tujuanKota << endl;
            cout << "Jam Berangkat  : " << (arr + prev)->jamBerangkat  << endl;
            cout << "Jam Tiba       : " << (arr + prev)->jamTiba       << endl;
            cout << "Harga Tiket    : Rp " << (arr + prev)->hargaTiket << endl;
            cout << "Kursi Tersedia : " << (arr + prev)->kursiTersedia << endl;
            cetakGaris('=', 60);
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();
            return;
        }
        cout << " --> Tidak cocok" << endl;
        prev++;
    }

    // jika seluruh blok sudah diperiksa dan tidak ada yang cocok, maka elemen memang tidak ada dalam data.
    cout << "\nNomor kereta [" << nomorCari << "] tidak ditemukan." << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; i++) *(L + i) = *(arr + l + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + m + 1 + j);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((L + i)->namaKereta <= (R + j)->namaKereta) {
            *(arr + k) = *(L + i); i++;
        } else {
            *(arr + k) = *(R + j); j++;
        }
        k++;
    }
    while (i < n1) { *(arr + k) = *(L + i); i++; k++; }
    while (j < n2) { *(arr + k) = *(R + j); j++; k++; }
    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        iterasiMerge++;
        cout << "Merge Iterasi " << iterasiMerge
             << " : Gabung [" << l << ".." << m << "] + [" << m + 1 << ".." << r << "]" << endl;
        cout << "  Sebelum : ";
        for (int i = l; i <= r; i++)
            cout << (arr + i)->namaKereta << (i < r ? " | " : "\n");
        merge(arr, l, m, r);
        cout << "  Sesudah : ";
        for (int i = l; i <= r; i++)
            cout << (arr + i)->namaKereta << (i < r ? " | " : "\n");
    }
}

void mergeSortMenu(Kereta* arr, int n) {
    system("cls");
    cout << "--- MERGE SORT: URUTKAN NAMA KERETA (A-Z) ---" << endl;
    if (n == 0) {
        cout << "Belum ada data." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cout << "Data sebelum diurutkan:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  " << i + 1 << ". " << (arr + i)->namaKereta << endl;
    cout << endl;
    iterasiMerge = 0;
    mergeSort(arr, 0, n - 1);
    cout << "\nData setelah diurutkan:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  " << i + 1 << ". " << (arr + i)->namaKereta << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void selectionSort(Kereta* arr, int n) {
    system("cls");
    cout << "--- SELECTION SORT: URUTKAN HARGA TIKET (TERMURAH) ---" << endl;
    if (n == 0) {
        cout << "Belum ada data." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cout << "Data sebelum diurutkan:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  " << i + 1 << ". " << (arr + i)->namaKereta
             << " - Rp" << (arr + i)->hargaTiket << endl;
    cout << endl;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        cout << "Iterasi " << i + 1
             << " | Acuan: [" << (arr + i)->namaKereta
             << " Rp" << (arr + i)->hargaTiket << "]" << endl;
        for (int j = i + 1; j < n; j++) {
            cout << "  Cek indeks [" << j << "] "
                 << (arr + j)->namaKereta << " Rp" << (arr + j)->hargaTiket
                 << " vs minimum [" << (arr + minIdx)->namaKereta
                 << " Rp" << (arr + minIdx)->hargaTiket << "]";
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket) {
                minIdx = j;
                cout << " --> Minimum baru!" << endl;
            } else {
                cout << " --> Tetap" << endl;
            }
        }
        if (minIdx != i) {
            cout << "  Swap: [" << (arr + i)->namaKereta
                 << "] <-> [" << (arr + minIdx)->namaKereta << "]" << endl;
            swapKereta(arr + i, arr + minIdx);
        } else {
            cout << "  Tidak perlu swap, posisi sudah minimum." << endl;
        }
        cout << "  Hasil : ";
        for (int k = 0; k < n; k++)
            cout << (arr + k)->namaKereta << "(Rp" << (arr + k)->hargaTiket << ")"
                 << (k < n - 1 ? " | " : "\n");
        cout << endl;
    }

    cout << "Data setelah diurutkan:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  " << i + 1 << ". " << (arr + i)->namaKereta
             << " - Rp" << (arr + i)->hargaTiket << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

int main() {
    daftarKereta[jumlahKereta++] = {"KA001", "Mulawarman Express",  "Balikpapan", "Samarinda",  "06:00", "08:00", 85000,  60};
    daftarKereta[jumlahKereta++] = {"KA002", "Borneo Intercity",    "Samarinda",  "Bontang",    "09:00", "11:30", 110000, 55};
    daftarKereta[jumlahKereta++] = {"KA003", "Mahakam Pagi",        "Balikpapan", "Tenggarong", "07:30", "10:00", 95000,  70};
    daftarKereta[jumlahKereta++] = {"KA004", "Kutai Jaya",          "Tenggarong", "Berau",      "11:00", "15:00", 150000, 50};
    daftarKereta[jumlahKereta++] = {"KA005", "Paser Raya",          "Balikpapan", "Tanah Grogot","08:00","10:30", 75000,  65};
    daftarKereta[jumlahKereta++] = {"KA006", "Sangatta Ekspres",    "Bontang",    "Sangatta",   "13:00", "14:30", 60000,  80};

    Kereta* ptrKereta = daftarKereta;

    bool jalan = true;
    while (jalan) {
        system("cls");
        cout << "==============================================" << endl;
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN KERETA API   " << endl;
        cout << "==============================================" << endl;
        cout << "1. Tampilkan Jadwal Semua Kereta" << endl;
        cout << "2. Tambah Data Kereta Baru" << endl;
        cout << "3. Cari Kereta Berdasarkan Rute (Linear Search)" << endl;
        cout << "4. Cari Kereta Berdasarkan Nomor (Jump Search)" << endl;
        cout << "5. Urutkan Nama Kereta A-Z (Merge Sort)" << endl;
        cout << "6. Urutkan Harga Tiket Termurah (Selection Sort)" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilihan: ";
        int pilihan; cin >> pilihan;

        if (pilihan == 1) {
            tampilkanJadwal(ptrKereta, jumlahKereta);
        } else if (pilihan == 2) {
            tambahKereta(ptrKereta, jumlahKereta);
        } else if (pilihan == 3) {
            system("cls");
            string asal, tujuan;
            cin.ignore();
            cout << "Kota Asal   : "; getline(cin, asal);
            cout << "Kota Tujuan : "; getline(cin, tujuan);
            linearSearchRute(ptrKereta, jumlahKereta, asal, tujuan);
        } else if (pilihan == 4) {
            system("cls");
            string nomor;
            cout << "Nomor Kereta: "; cin >> nomor;
            jumpSearchNomor(ptrKereta, jumlahKereta, nomor);
        } else if (pilihan == 5) {
            mergeSortMenu(ptrKereta, jumlahKereta);
        } else if (pilihan == 6) {
            selectionSort(ptrKereta, jumlahKereta);
        } else if (pilihan == 7) {
            system("cls");
            cout << "Terima kasih telah menggunakan sistem ini!" << endl;
            jalan = false;
        }
    }
    return 0;
}