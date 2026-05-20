#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
using namespace std;

// ======================= STRUCT =======================
struct Barang {
    char kode[10];
    char nama[30];
    int stok;
    int harga;
    Barang *next;
};

// Struct khusus file (tanpa pointer)
struct DataBarang {
    char kode[10];
    char nama[30];
    int stok;
    int harga;
};

Barang *head = NULL;

// ======================= HEADER =======================
void header() {
    cout << "+=====+================================+\n";
    cout << "|      SISTEM INVENTARIS TOKO ATK      |\n";
    cout << "+=====+================================+\n";
}

// ======================= VALIDASI =======================
int inputAngka(string pesan) {
    int nilai;

    while (true) {
        cout << pesan;
        cin >> nilai;

        if (cin.fail() || nilai < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid!\n";
        } else {
            return nilai;
        }
    }
}

// ======================= CEK KODE =======================
bool cekKode(char kode[]) {
    Barang *temp = head;

    while (temp != NULL) {
        if (strcmp(temp->kode, kode) == 0) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// ======================= AUTO SAVE =======================
void simpanFile() {

    FILE *file = fopen("data.dat", "wb");

    if (file == NULL) {
        cout << "\nFile gagal dibuka!\n";
        return;
    }

    Barang *temp = head;
    DataBarang data;

    while (temp != NULL) {

        strcpy(data.kode, temp->kode);
        strcpy(data.nama, temp->nama);
        data.stok = temp->stok;
        data.harga = temp->harga;

        fwrite(&data, sizeof(DataBarang), 1, file);

        temp = temp->next;
    }

    fclose(file);
}

// ======================= LOAD FILE =======================
void bacaFile() {

    FILE *file = fopen("data.dat", "rb");

    if (file == NULL) {
        return;
    }

    DataBarang data;

    while (fread(&data, sizeof(DataBarang), 1, file)) {

        Barang *baru = new Barang();

        strcpy(baru->kode, data.kode);
        strcpy(baru->nama, data.nama);
        baru->stok = data.stok;
        baru->harga = data.harga;

        baru->next = NULL;

        if (head == NULL) {
            head = baru;
        } else {

            Barang *temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = baru;
        }
    }

    fclose(file);
}

// ======================= CREATE =======================
void tambahBarang() {

    Barang *baru = new Barang();

    cout << "\n--- Tambah Barang ---\n";

    cout << "Kode Barang : ";
    cin >> baru->kode;

    if (cekKode(baru->kode)) {
        cout << "\nKode barang sudah ada!\n";
        delete baru;
        return;
    }

    cin.ignore();

    cout << "Nama Barang : ";
    cin.getline(baru->nama, 30);

    baru->stok = inputAngka("Stok Barang : ");
    baru->harga = inputAngka("Harga Barang: ");

    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {

        Barang *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = baru;
    }

    simpanFile(); // AUTO SAVE

    cout << "\nData berhasil ditambahkan.\n";
}

// ======================= READ =======================
void tampilBarang() {
    if (head == NULL) {
        cout << "\nData inventaris kosong.\n";
        return;
    }

    Barang *temp = head;

    cout << "\n";
    cout << "+----+------------+------------------------------+--------+------------------+\n";
    cout << "| No | Kode       | Nama Barang                  |  Stok  | Harga            |\n";
    cout << "+----+------------+------------------------------+--------+------------------+\n";

    int no = 1;
    while (temp != NULL) {
        cout << "| "
             << left  << setw(2)  << no           << " | "
             << left  << setw(10) << temp->kode   << " | "
             << left  << setw(28) << temp->nama   << " | "
             << left << setw(6)  << temp->stok   << " | "
             << left << setw(16) << temp->harga  << " |\n";
        temp = temp->next;
        no++;
    }

    cout << "+----+------------+------------------------------+--------+------------------+\n";
}

// ======================= SEARCH =======================
void cariBarang() {

    char kode[10];

    cout << "\n--- Cari Barang ---\n";
    cout << "Masukkan kode barang : ";
    cin >> kode;

    Barang *temp = head;

    while (temp != NULL) {

        if (strcmp(temp->kode, kode) == 0) {

            cout << "\nData ditemukan\n";
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

// ======================= UPDATE =======================
void editBarang() {

    char kode[10];

    cout << "\n--- Edit Barang ---\n";
    cout << "Masukkan kode barang : ";
    cin >> kode;

    Barang *temp = head;

    while (temp != NULL) {

        if (strcmp(temp->kode, kode) == 0) {

            cin.ignore();

            cout << "Nama Baru  : ";
            cin.getline(temp->nama, 30);

            temp->stok = inputAngka("Stok Baru  : ");
            temp->harga = inputAngka("Harga Baru : ");

            simpanFile(); // AUTO SAVE

            cout << "\nData berhasil diupdate.\n";
            return;
        }

        temp = temp->next;
    }

    cout << "\nData tidak ditemukan.\n";
}

// ======================= DELETE =======================
void hapusBarang() {

    char kode[10];

    cout << "\n--- Hapus Barang ---\n";
    cout << "Masukkan kode barang : ";
    cin >> kode;

    Barang *temp = head;
    Barang *prev = NULL;

    while (temp != NULL && strcmp(temp->kode, kode) != 0) {

        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "\nData tidak ditemukan.\n";
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;

    simpanFile(); // AUTO SAVE

    cout << "\nData berhasil dihapus.\n";
}

// ======================= SORTING =======================
void sortHargaAscending() {

    if (head == NULL) {
        cout << "\nData kosong.\n";
        return;
    }

    Barang *i, *j;
    DataBarang temp;

    for (i = head; i != NULL; i = i->next) {

        for (j = i->next; j != NULL; j = j->next) {

            if (i->harga > j->harga) {

                strcpy(temp.kode, i->kode);
                strcpy(temp.nama, i->nama);
                temp.stok = i->stok;
                temp.harga = i->harga;

                strcpy(i->kode, j->kode);
                strcpy(i->nama, j->nama);
                i->stok = j->stok;
                i->harga = j->harga;

                strcpy(j->kode, temp.kode);
                strcpy(j->nama, temp.nama);
                j->stok = temp.stok;
                j->harga = temp.harga;
            }
        }
    }

    simpanFile();

    cout << "\nData berhasil diurutkan ascending.\n";
}

void sortHargaDescending() {

    if (head == NULL) {
        cout << "\nData kosong.\n";
        return;
    }

    Barang *i, *j;
    DataBarang temp;

    for (i = head; i != NULL; i = i->next) {

        for (j = i->next; j != NULL; j = j->next) {

            if (i->harga < j->harga) {

                strcpy(temp.kode, i->kode);
                strcpy(temp.nama, i->nama);
                temp.stok = i->stok;
                temp.harga = i->harga;

                strcpy(i->kode, j->kode);
                strcpy(i->nama, j->nama);
                i->stok = j->stok;
                i->harga = j->harga;

                strcpy(j->kode, temp.kode);
                strcpy(j->nama, temp.nama);
                j->stok = temp.stok;
                j->harga = temp.harga;
            }
        }
    }

    simpanFile();

    cout << "\nData berhasil diurutkan descending.\n";
}

// ======================= HAPUS MEMORI =======================
void hapusSemua() {

    Barang *temp;

    while (head != NULL) {

        temp = head;
        head = head->next;

        delete temp;
    }
}

// ======================= MENU =======================
void menu() {

    cout << "\n";
    cout << "+=====+================================+\n";
    cout << "| No  |          MENU UTAMA            |\n";
    cout << "+=====+================================+\n";
    cout << "| [1] |  Tambah Barang                 |\n";
    cout << "| [2] |  Tampilkan Barang              |\n";
    cout << "| [3] |  Cari Barang                   |\n";
    cout << "| [4] |  Edit Barang                   |\n";
    cout << "| [5] |  Hapus Barang                  |\n";
    cout << "| [6] |  Sort Harga Termurah           |\n";
    cout << "| [7] |  Sort Harga Termahal           |\n";
    cout << "+=====+================================+\n";
    cout << "| [0] |  Keluar                        |\n";
    cout << "+=====+================================+\n";
    cout << "Pilih menu : ";
}

// ======================= MAIN =======================
int main() {

    int pilih;

    bacaFile();

    do {

        header();
        menu();

        pilih = inputAngka("");

        switch (pilih) {

            case 1:
                tambahBarang();
                break;

            case 2:
                tampilBarang();
                break;

            case 3:
                cariBarang();
                break;

            case 4:
                editBarang();
                break;

            case 5:
                hapusBarang();
                break;

            case 6:
                sortHargaAscending();
                break;

            case 7:
                sortHargaDescending();
                break;

            case 0:
                simpanFile();
                hapusSemua();
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nMenu tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}
