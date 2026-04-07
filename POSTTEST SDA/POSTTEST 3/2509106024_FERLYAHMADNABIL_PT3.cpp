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

struct Penumpang {
    string namaPenumpang;
    string nomorKereta;
    string namaKereta;
    string asalKota;
    string tujuanKota;
    int    hargaTiket;
};

const int MAKSIMAL    = 100;
const int MAX_ANTRIAN = 50;
const int MAX_RIWAYAT = 50;

Kereta    daftarKereta[MAKSIMAL];
int       jumlahKereta = 0;
int       iterasiMerge = 0;

Penumpang antrianTiket[MAX_ANTRIAN];
int       frontAntrian = -1;
int       rearAntrian  = -1;

Penumpang riwayatTransaksi[MAX_RIWAYAT];
int       topRiwayat = -1;

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void cetakGaris(char karakter, int lebar) {
    cout << setfill(karakter) << setw(lebar) << karakter << setfill(' ') << endl;
}

bool isAntrianPenuh() {
    return rearAntrian == MAX_ANTRIAN - 1;
}

bool isAntrianKosong() {
    return frontAntrian == -1 || frontAntrian > rearAntrian;
}

bool isRiwayatPenuh() {
    return topRiwayat >= MAX_RIWAYAT - 1;
}

bool isRiwayatKosong() {
    return topRiwayat == -1;
}

void enqueue(Penumpang* antrian, int& front, int& rear, Penumpang* p) {
    if (isAntrianPenuh()) {
        cout << "[OVERFLOW] Antrian penuh! Kapasitas maksimum " << MAX_ANTRIAN << " penumpang." << endl;
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    *(antrian + rear) = *p;
    cout << "Penumpang [" << p->namaPenumpang << "] berhasil masuk antrian." << endl;
    cout << "Posisi dalam antrian: " << (rear - front + 1) << " dari " << MAX_ANTRIAN << endl;
}

void dequeue(Penumpang* antrian, int& front, int& rear,
             Penumpang* riwayat, int& top) {
    if (isAntrianKosong()) {
        cout << "[UNDERFLOW] Antrian kosong! Tidak ada penumpang yang bisa diproses." << endl;
        return;
    }
    Penumpang diproses = *(antrian + front);
    front++;
    if (isAntrianKosong()) {
        front = rear = -1;
    }

    cout << "Memproses tiket untuk: [" << diproses.namaPenumpang << "]" << endl;
    cetakGaris('-', 50);
    cout << "Nama Penumpang : " << diproses.namaPenumpang << endl;
    cout << "Kereta         : " << diproses.namaKereta << " (" << diproses.nomorKereta << ")" << endl;
    cout << "Rute           : " << diproses.asalKota << " --> " << diproses.tujuanKota << endl;
    cout << "Harga Tiket    : Rp " << diproses.hargaTiket << endl;
    cetakGaris('-', 50);

    if (isRiwayatPenuh()) {
        cout << "[OVERFLOW] Riwayat penuh! Transaksi tidak dapat disimpan ke riwayat." << endl;
        return;
    }
    top++;
    *(riwayat + top) = diproses;
    cout << "Tiket berhasil diproses dan dicatat ke riwayat." << endl;
}

void pushRiwayat(Penumpang* riwayat, int& top, Penumpang* p) {
    if (isRiwayatPenuh()) {
        cout << "[OVERFLOW] Riwayat penuh! Kapasitas maksimum " << MAX_RIWAYAT << " transaksi." << endl;
        return;
    }
    top++;
    *(riwayat + top) = *p;
    cout << "Transaksi [" << p->namaPenumpang << "] berhasil ditambahkan ke riwayat." << endl;
}

void popRiwayat(Penumpang* riwayat, int& top) {
    if (isRiwayatKosong()) {
        cout << "[UNDERFLOW] Riwayat kosong! Tidak ada transaksi yang bisa dibatalkan." << endl;
        return;
    }
    Penumpang dibatalkan = *(riwayat + top);
    top--;
    cout << "Transaksi terakhir berhasil dibatalkan." << endl;
    cetakGaris('-', 50);
    cout << "Nama Penumpang : " << dibatalkan.namaPenumpang << endl;
    cout << "Kereta         : " << dibatalkan.namaKereta << " (" << dibatalkan.nomorKereta << ")" << endl;
    cout << "Rute           : " << dibatalkan.asalKota << " --> " << dibatalkan.tujuanKota << endl;
    cout << "Harga Tiket    : Rp " << dibatalkan.hargaTiket << endl;
    cetakGaris('-', 50);
    cout << "Sisa riwayat   : " << top + 1 << " transaksi." << endl;
}

void peekAntrian(Penumpang* antrian, int front, int rear,
                 Penumpang* riwayat, int top) {
    system("cls");
    cout << "--- PEEK: PENUMPANG TERDEPAN & TRANSAKSI TERAKHIR ---" << endl;
    cetakGaris('=', 55);

    cout << "[ANTRIAN - FRONT]" << endl;
    if (isAntrianKosong()) {
        cout << "  Antrian sedang kosong." << endl;
    } else {
        Penumpang* p = antrian + front;
        cout << "  Nama Penumpang : " << p->namaPenumpang << endl;
        cout << "  Kereta         : " << p->namaKereta << " (" << p->nomorKereta << ")" << endl;
        cout << "  Rute           : " << p->asalKota << " --> " << p->tujuanKota << endl;
        cout << "  Harga Tiket    : Rp " << p->hargaTiket << endl;
    }

    cetakGaris('-', 55);

    cout << "[RIWAYAT - TOP]" << endl;
    if (isRiwayatKosong()) {
        cout << "  Riwayat masih kosong." << endl;
    } else {
        Penumpang* r = riwayat + top;
        cout << "  Nama Penumpang : " << r->namaPenumpang << endl;
        cout << "  Kereta         : " << r->namaKereta << " (" << r->nomorKereta << ")" << endl;
        cout << "  Rute           : " << r->asalKota << " --> " << r->tujuanKota << endl;
        cout << "  Harga Tiket    : Rp " << r->hargaTiket << endl;
    }

    cetakGaris('=', 55);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tampilkanAntrian(Penumpang* antrian, int front, int rear) {
    system("cls");
    cout << "--- TAMPIL SEMUA ANTRIAN PEMBELIAN TIKET ---" << endl;
    if (isAntrianKosong()) {
        cout << "Antrian kosong." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 75);
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Penumpang"
         << setw(10) << "No.KA"
         << setw(20) << "Nama Kereta"
         << setw(20) << "Rute" << endl;
    cetakGaris('-', 75);
    for (int i = front; i <= rear; i++) {
        Penumpang* p = antrian + i;
        string rute = p->asalKota + "->" + p->tujuanKota;
        cout << left
             << setw(5)  << (i - front + 1)
             << setw(20) << p->namaPenumpang
             << setw(10) << p->nomorKereta
             << setw(20) << p->namaKereta
             << setw(20) << rute << endl;
    }
    cetakGaris('=', 75);
    cout << "Total penumpang dalam antrian: " << (rear - front + 1) << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tampilkanRiwayat(Penumpang* riwayat, int top) {
    system("cls");
    cout << "--- TAMPIL SEMUA RIWAYAT TRANSAKSI ---" << endl;
    if (isRiwayatKosong()) {
        cout << "Riwayat transaksi masih kosong." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 80);
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Penumpang"
         << setw(10) << "No.KA"
         << setw(20) << "Nama Kereta"
         << setw(15) << "Rute"
         << setw(12) << "Harga" << endl;
    cetakGaris('-', 80);
    for (int i = top; i >= 0; i--) {
        Penumpang* r = riwayat + i;
        string rute = r->asalKota + "->" + r->tujuanKota;
        cout << left
             << setw(5)  << (top - i + 1)
             << setw(20) << r->namaPenumpang
             << setw(10) << r->nomorKereta
             << setw(20) << r->namaKereta
             << setw(15) << rute
             << setw(12) << r->hargaTiket << endl;
    }
    cetakGaris('=', 80);
    cout << "Total riwayat transaksi: " << top + 1 << endl;
    cout << "(Ditampilkan dari transaksi terbaru ke terlama)" << endl;
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
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

    cout << "\nMengurutkan data berdasarkan nomor kereta dahulu..." << endl;
    sortByNomor(arr, n);
    cout << "Urutan setelah sort: ";
    for (int i = 0; i < n; i++)
        cout << (arr + i)->nomorKereta << (i < n - 1 ? " | " : "\n");

    int step    = (int)sqrt((double)n);
    int prev    = 0;
    int iterasi = 1;
    cout << "\nJumlah data: " << n << " | Step Jump: " << step << endl;
    cetakGaris('-', 68);

    int batas = (step < n ? step : n) - 1;
    while ((arr + batas)->nomorKereta < nomorCari) {
        cout << "Jump Iterasi " << setw(2) << iterasi++
             << " | Indeks [" << setw(2) << batas << "]"
             << " | [" << (arr + batas)->nomorKereta << "] < " << nomorCari
             << " --> Lompat!" << endl;
        prev   = step;
        step  += (int)sqrt((double)n);
        batas  = (step < n ? step : n) - 1;
        if (prev >= n) {
            cout << "\nNomor kereta [" << nomorCari << "] tidak ditemukan." << endl;
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();
            return;
        }
    }

    int akhir = (step < n ? step : n);
    cout << "\nFase Linear Search dari indeks " << prev << " hingga " << akhir - 1 << ":" << endl;
    while (prev < akhir) {
        cout << "Linear Iterasi " << setw(2) << iterasi++
             << " | Indeks [" << setw(2) << prev << "]"
             << " | [" << (arr + prev)->nomorKereta << "]";
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

void menuAntrian(Kereta* daftarKereta, int jumlahKereta) {
    bool kembali = false;
    while (!kembali) {
        system("cls");
        cout << "==============================================" << endl;
        cout << "     MENU ANTRIAN & RIWAYAT TIKET KERETA    " << endl;
        cout << "==============================================" << endl;
        cout << "1. Tambah Penumpang ke Antrian  (Enqueue)" << endl;
        cout << "2. Proses Penumpang Terdepan    (Dequeue)" << endl;
        cout << "3. Batalkan Transaksi Terakhir  (Pop)" << endl;
        cout << "4. Peek Antrian & Riwayat" << endl;
        cout << "5. Tampilkan Semua Antrian" << endl;
        cout << "6. Tampilkan Semua Riwayat" << endl;
        cout << "7. Kembali ke Menu Utama" << endl;
        cout << "Pilihan: ";
        int pilihan; cin >> pilihan;

        if (pilihan == 1) {
            system("cls");
            cout << "--- TAMBAH PENUMPANG KE ANTRIAN ---" << endl;

            if (jumlahKereta == 0) {
                cout << "Belum ada data kereta tersedia." << endl;
                cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                continue;
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
            for (int i = 0; i < jumlahKereta; i++) {
                cout << left
                     << setw(4)  << i + 1
                     << setw(10) << (daftarKereta + i)->nomorKereta
                     << setw(22) << (daftarKereta + i)->namaKereta
                     << setw(14) << (daftarKereta + i)->asalKota
                     << setw(14) << (daftarKereta + i)->tujuanKota
                     << setw(11) << (daftarKereta + i)->jamBerangkat
                     << setw(8)  << (daftarKereta + i)->jamTiba
                     << setw(15) << (daftarKereta + i)->hargaTiket
                     << setw(8)  << (daftarKereta + i)->kursiTersedia << endl;
            }
            cetakGaris('=', 108);

            int pilihanKereta;
            cout << "Pilih nomor kereta (1-" << jumlahKereta << "): ";
            cin >> pilihanKereta;

            if (pilihanKereta < 1 || pilihanKereta > jumlahKereta) {
                cout << "Pilihan tidak valid!" << endl;
                cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                continue;
            }

            Kereta* k = daftarKereta + (pilihanKereta - 1);

            if (k->kursiTersedia <= 0) {
                cout << "Maaf, kursi kereta [" << k->namaKereta << "] sudah habis!" << endl;
                cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                continue;
            }

            Penumpang p;
            cin.ignore();
            cout << "Nama Penumpang : "; getline(cin, p.namaPenumpang);
            p.nomorKereta = k->nomorKereta;
            p.namaKereta  = k->namaKereta;
            p.asalKota    = k->asalKota;
            p.tujuanKota  = k->tujuanKota;
            p.hargaTiket  = k->hargaTiket;
            k->kursiTersedia--;

            enqueue(antrianTiket, frontAntrian, rearAntrian, &p);
            cout << "Sisa kursi kereta [" << k->namaKereta << "]: " << k->kursiTersedia << endl;
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();

        } else if (pilihan == 2) {
            system("cls");
            cout << "--- PROSES PENUMPANG TERDEPAN (DEQUEUE) ---" << endl;
            dequeue(antrianTiket, frontAntrian, rearAntrian, riwayatTransaksi, topRiwayat);
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();

        } else if (pilihan == 3) {
            system("cls");
            cout << "--- BATALKAN TRANSAKSI TERAKHIR (POP) ---" << endl;
            popRiwayat(riwayatTransaksi, topRiwayat);
            cout << "\nTekan Enter..."; cin.ignore(); cin.get();

        } else if (pilihan == 4) {
            peekAntrian(antrianTiket, frontAntrian, rearAntrian, riwayatTransaksi, topRiwayat);

        } else if (pilihan == 5) {
            tampilkanAntrian(antrianTiket, frontAntrian, rearAntrian);

        } else if (pilihan == 6) {
            tampilkanRiwayat(riwayatTransaksi, topRiwayat);

        } else if (pilihan == 7) {
            kembali = true;
        }
    }
}

int main() {
    daftarKereta[jumlahKereta++] = {"KA001", "Mulawarman Express",  "Balikpapan", "Samarinda",    "06:00", "08:00", 85000,  60};
    daftarKereta[jumlahKereta++] = {"KA002", "Borneo Intercity",    "Samarinda",  "Bontang",      "09:00", "11:30", 110000, 55};
    daftarKereta[jumlahKereta++] = {"KA003", "Mahakam Pagi",        "Balikpapan", "Tenggarong",   "07:30", "10:00", 95000,  70};
    daftarKereta[jumlahKereta++] = {"KA004", "Kutai Jaya",          "Tenggarong", "Berau",        "11:00", "15:00", 150000, 50};
    daftarKereta[jumlahKereta++] = {"KA005", "Paser Raya",          "Balikpapan", "Tanah Grogot", "08:00", "10:30", 75000,  65};
    daftarKereta[jumlahKereta++] = {"KA006", "Sangatta Ekspres",    "Bontang",    "Sangatta",     "13:00", "14:30", 60000,  80};

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
        cout << "7. Antrian & Riwayat Tiket (Queue & Stack)" << endl;
        cout << "8. Keluar" << endl;
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
            menuAntrian(ptrKereta, jumlahKereta);
        } else if (pilihan == 8) {
            system("cls");
            cout << "Terima kasih telah menggunakan sistem ini!" << endl;
            jalan = false;
        }
    }
    return 0;
}