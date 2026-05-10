#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

struct Barang {
    char kode[10];
    char nama[25];
    int stok;
    int harga;
    Barang *next;
};

Barang *head = NULL;

// HEADER
void header() {
    cout << "\n==================================================\n";
    cout << "         SISTEM INVENTARIS TOKO ATK\n";
    cout << "==================================================\n";
}

// TAMBAH
void tambahBarang() {
    Barang *baru = new Barang();

    cout << "\n--- Tambah Data Barang ---\n";
    cout << "Kode  : "; cin >> baru->kode;
    cout << "Nama  : "; cin.ignore(); cin.getline(baru->nama, 25);
    cout << "Stok  : "; cin >> baru->stok;
    cout << "Harga : "; cin >> baru->harga;

    baru->next = head;
    head = baru;

    cout << "\nData berhasil ditambahkan.\n";
}

// TAMPIL (TABEL RAPI)
void tampilBarang() {
    if (head == NULL) {
        cout << "\nData inventaris masih kosong.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << left << setw(10) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "============================================================\n";

    Barang *temp = head;
    while (temp != NULL) {
        cout << left << setw(10) << temp->kode
             << setw(25) << temp->nama
             << setw(10) << temp->stok
             << setw(15) << temp->harga << endl;
        temp = temp->next;
    }

    cout << "============================================================\n";
}

// CARI
void cariBarang() {
    char kode[10];
    cout << "\n--- Pencarian Barang ---\n";
    cout << "Masukkan kode barang: ";
    cin >> kode;

    Barang *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->kode, kode) == 0) {
            cout << "\nData ditemukan:\n";
            cout << "Kode  : " << temp->kode << endl;
            cout << "Nama  : " << temp->nama << endl;
            cout << "Stok  : " << temp->stok << endl;
            cout << "Harga : " << temp->harga << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "\nData tidak ditemukan.\n";
}

// HAPUS
void hapusBarang() {
    char kode[10];
    cout << "\n--- Hapus Barang ---\n";
    cout << "Masukkan kode barang: ";
    cin >> kode;

    Barang *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->kode, kode) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "\nData tidak ditemukan.\n";
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    delete temp;
    cout << "\nData berhasil dihapus.\n";
}

// SIMPAN KE FILE (menggunakan fwrite - sesuai modul hal 4)
void simpanFile() {
    FILE *file = fopen("data.dat", "wb");
    
    if (file == NULL) {
        cout << "\nFile gagal dibuka!\n";
        return;
    }
    
    Barang *temp = head;
    int jumlah = 0;
    
    while (temp != NULL) {
        fwrite(temp, sizeof(Barang), 1, file);
        temp = temp->next;
        jumlah++;
    }
    
    fclose(file);
    cout << "\n" << jumlah << " data berhasil disimpan ke file.\n";
}

// BACA DARI FILE (menggunakan fread - sesuai modul hal 4)
void bacaFile() {
    FILE *file = fopen("data.dat", "rb");
    
    if (file == NULL) {
        return;
    }
    
    while (1) {
        Barang *baru = new Barang();
        int hasil = fread(baru, sizeof(Barang), 1, file);
        
        if (hasil != 1) {
            delete baru;
            break;
        }
        
        baru->next = head;
        head = baru;
    }
    
    fclose(file);
    
    if (head != NULL) {
        cout << "\nData dari file berhasil dimuat.\n";
    }
}

// MENU
void menu() {
    cout << "\nMenu Utama\n";
    cout << "----------------------------------\n";
    cout << "1. Tambah Data Barang\n";
    cout << "2. Tampilkan Data Barang\n";
    cout << "3. Cari Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Simpan ke File\n";
    cout << "0. Keluar\n";
    cout << "----------------------------------\n";
    cout << "Pilih menu: ";
}

int main() {
    int pilih;
    
    bacaFile();

    do {
        header();
        menu();
        cin >> pilih;

        switch(pilih) {
            case 1: tambahBarang(); break;
            case 2: tampilBarang(); break;
            case 3: cariBarang(); break;
            case 4: hapusBarang(); break;
            case 5: simpanFile(); break;
            case 0: cout << "\nProgram selesai.\n"; break;
            default: cout << "\nPilihan tidak valid.\n";
        }

    } while (pilih != 0);

    return 0;
}
