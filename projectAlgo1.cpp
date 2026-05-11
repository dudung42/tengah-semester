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

void header() {
    cout << "\n==================================================\n";
    cout << "         SISTEM INVENTARIS TOKO ATK\n";
    cout << "==================================================\n";
}

void sortingBarang() {
    // sorting dengan metode bubble sort berdasarkan kode barang
    if (head == NULL) {
        cout << "\nData inventaris masih kosong.\n";
        return;
    }
    Barang *temp1, *temp2;
    char tempKode[10], tempNama[25];    
    int tempStok, tempHarga;
    for (temp1 = head; temp1 != NULL; temp1 = temp1->next) {
        for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {
            if (strcmp(temp1->kode, temp2->kode) > 0) {

                strcpy(tempKode, temp1->kode);
                strcpy(temp1->kode, temp2->kode);
                strcpy(temp2->kode, tempKode);

                strcpy(tempNama, temp1->nama);
                strcpy(temp1->nama, temp2->nama);
                strcpy(temp2->nama, tempNama);

                tempStok = temp1->stok;
                temp1->stok = temp2->stok;
                temp2->stok = tempStok;

                tempHarga = temp1->harga;
                temp1->harga = temp2->harga;
                temp2->harga = tempHarga;
            }
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan kode barang.\n";
}

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

void menu() {
    cout << "\nMenu Utama\n";
    cout << "----------------------------------\n";
    cout << "1. Tambah Data Barang\n";
    cout << "2. Tampilkan Data Barang\n";
    cout << "3. Sorting Data Barang\n";
    cout << "4. Cari Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Simpan ke File\n";
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
            case 3: sortingBarang(); break;
            case 4: cariBarang(); break;
            case 5: hapusBarang(); break;
            case 6: simpanFile(); break;
            case 0: cout << "\nProgram selesai.\n"; break;
            default: cout << "\nPilihan tidak valid.\n";
        }

    } while (pilih != 0);

    return 0;
}
