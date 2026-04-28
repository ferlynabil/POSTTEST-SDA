#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Perpustakaan
struct BukuNode {
    string judulBuku;
    BukuNode* next;

    // Constructor
    BukuNode(string judul) {
        judulBuku = judul;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List
BukuNode* tambahBuku(BukuNode* head, string judul) {
    BukuNode* newNode = new BukuNode(judul);

    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }

    BukuNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

/**
 * @brief Fungsi untuk mencari buku berdasarkan judulnya dalam Circular Linked List.
 * @param head Pointer ke node pertama (head).
 * @param judulDicari String judul buku yang ingin dicari.
 * @return boolean true jika buku ditemukan, false jika tidak ditemukan.
 * @logic
 * 1. Jika list kosong (head == nullptr), kembalikan false.
 * 2. Mulai penelusuran dari head menggunakan pointer temp.
 * 3. Selama penelusuran, cek apakah temp->judulBuku sama dengan judulDicari.
 *    Jika ya, langsung kembalikan true.
 * 4. Lanjutkan ke node berikutnya. Berhenti jika temp kembali mencapai head.
 * 5. Jika seluruh list sudah ditelusuri dan tidak ditemukan, kembalikan false.
 */
bool cariBuku(BukuNode* head, string judulDicari) {
    // 1. Jika list kosong, kembalikan false
    if (head == nullptr) return false;

    // 2. Mulai dari head
    BukuNode* temp = head;

    // 3 & 4. Gunakan do-while agar head juga ikut dicek
    do {
        if (temp->judulBuku == judulDicari) return true;
        temp = temp->next;
    } while (temp != head);

    // 5. Tidak ditemukan
    return false;
}

// Fungsi tambahan: tampilkan semua buku dalam list
void tampilkanSemuaBuku(BukuNode* head) {
    if (head == nullptr) {
        cout << "List kosong." << endl;
        return;
    }

    cout << "Daftar Buku:" << endl;
    BukuNode* temp = head;
    int no = 1;
    do {
        cout << no++ << ". " << temp->judulBuku << endl;
        temp = temp->next;
    } while (temp != head);
}

// Fungsi tambahan: hapus semua node (free memory)
void hapusSemua(BukuNode* head) {
    if (head == nullptr) return;

    BukuNode* temp = head;
    BukuNode* nextNode;

    // Putus siklus dulu
    do {
        nextNode = temp->next;
        delete temp;
        temp = nextNode;
    } while (temp != head);
}

int main() {
    BukuNode* head = nullptr;

    // Tambah data buku
    head = tambahBuku(head, "Struktur Data dengan C++");
    head = tambahBuku(head, "Pengantar Algoritma");
    head = tambahBuku(head, "Pemrograman Berorientasi Objek");
    head = tambahBuku(head, "Sistem Basis Data");

    // Tampilkan semua buku
    tampilkanSemuaBuku(head);
    cout << endl;

    // Pencarian buku
    string buku1 = "Pengantar Algoritma";
    string buku2 = "Kalkulus Lanjut";

    cout << "Mencari buku '" << buku1 << "': "
         << (cariBuku(head, buku1) ? "Ditemukan" : "Tidak Ditemukan") << endl;
    // Output: Ditemukan

    cout << "Mencari buku '" << buku2 << "': "
         << (cariBuku(head, buku2) ? "Ditemukan" : "Tidak Ditemukan") << endl;
    // Output: Tidak Ditemukan

    // Bersihkan memori
    hapusSemua(head);
    head = nullptr;

    return 0;
}