#include <iostream>
#include "tubes.h"

using namespace std;

void menu() {
    cout << "\n==============================\n";
    cout << "  PROGRAM MANAJEMEN BENGKEL\n";
    cout << "==============================\n";
    cout << "1. Tambah Mekanik\n";
    cout << "2. Tambah Servis\n";
    cout << "3. Tambah Sparepart\n";
    cout << "4. Hubungkan Mekanik dengan Servis\n";
    cout << "5. Tampilkan Semua Mekanik\n";
    cout << "6. Tampilkan Semua Servis\n";
    cout << "7. Tampilkan Semua Sparepart\n";
    cout << "8. Tampilkan Semua Relasi\n";
    cout << "9. Tampilkan Servis dari Mekanik\n";
    cout << "10. Tampilkan Mekanik dari Servis\n";
    cout << "11. Hapus Mekanik\n";
    cout << "12. Hapus Servis\n";
    cout << "13. Hapus Sparepart\n";
    cout << "14. Hapus Relasi\n";
    cout << "0. Keluar\n";
    cout << "==============================\n";
    cout << "Pilih menu: ";
}

int main() {
    listMekanik LM;
    listServis LS;
    listSparepart LP;

    createListMekanik(LM);
    createListServis(LS);
    createListSparepart(LP);

    int pilihan;

    while (true) {
        menu();
        cin >> pilihan;

        // keluar program
        if (pilihan == 0) {
            cout << "Program selesai.\n";
            break;
        }

        // =============================
        // 1. Tambah Mekanik
        // =============================
        if (pilihan == 1) {
            elmMekanik data;
            cout << "ID Mekanik: ";
            cin >> data.IDMekanik;
            cout << "Nama Mekanik: ";
            cin.ignore();
            getline(cin, data.namaMekanik);
            cout << "Jam Kerja: ";
            cin >> data.jamKerja;

            adrMekanik M = createElmMekanik(data);
            insertMekanik(LM, M);
        }

        // =============================
        // 2. Tambah Servis
        // =============================
        else if (pilihan == 2) {
            elmServis data;
            cout << "ID Servis: ";
            cin >> data.IDServis;
            cout << "Nama Kendaraan: ";
            cin.ignore();
            getline(cin, data.namaKendaraan);
            cout << "Biaya Servis: ";
            cin >> data.biayaServis;

            adrServis S = createElmServis(data);
            insertServis(LS, S);
        }

        // =============================
        // 3. Tambah Sparepart
        // =============================
        else if (pilihan == 3) {
            elmSparepart data;
            cout << "ID Sparepart: ";
            cin >> data.IDSparepart;
            cout << "Nama Sparepart: ";
            cin.ignore();
            getline(cin, data.namaSparepart);
            cout << "Harga: ";
            cin >> data.harga;

            nodeSparepart* P = createElmSparepart(data);
            insertSparepart(LP, P);
        }

        // =============================
        // 4. Relasi Mekanik - Servis
        // =============================
        else if (pilihan == 4) {
            string idM, idS;
            cout << "ID Mekanik: ";
            cin >> idM;
            cout << "ID Servis: ";
            cin >> idS;

            adrMekanik M = findMekanik(LM, idM);
            adrServis S = findServis(LS, idS);

            if (M != NULL && S != NULL) {
                insertRelasi(M, S);
                cout << "Relasi berhasil dibuat.\n";
            } else {
                cout << "Mekanik atau Servis tidak ditemukan!\n";
            }
        }

        // =============================
        // 5. Show Mekanik
        // =============================
        else if (pilihan == 5) {
            showAllMekanik(LM);
        }

        // =============================
        // 6. Show Servis
        // =============================
        else if (pilihan == 6) {
            showAllServis(LS);
        }

        // =============================
        // 7. Show Sparepart
        // =============================
        else if (pilihan == 7) {
            showAllSparepart(LP);
        }

        // =============================
        // 8. Show Semua Relasi
        // =============================
        else if (pilihan == 8) {
            showAllRelasi(LM);
        }

        // =============================
        // 9. Show Servis dari Mekanik
        // =============================
        else if (pilihan == 9) {
            void showServisDariMekanik(adrMekanik mekanik);
        }

        // =============================
        // 10. Show Mekanik dari Servis
        // =============================
        else if (pilihan == 10) {
            string id;
            cout << "ID Servis: ";
            cin >> id;
            showMekanikdariServis(LM, id);
        }

        // =============================
        // 11. Delete Mekanik
        // =============================
        else if (pilihan == 11) {
            string id;
            cout << "ID Mekanik yang dihapus: ";
            cin >> id;
            deleteMekanik(LM, id);
        }

        // =============================
        // 12. Delete Servis
        // =============================
        else if (pilihan == 12) {
            string id;
            cout << "ID Servis yang dihapus: ";
            cin >> id;
            deleteServis(LS, id);
        }

        // =============================
        // 13. Delete Sparepart
        // =============================
        else if (pilihan == 13) {
            string id;
            cout << "ID Sparepart yang dihapus: ";
            cin >> id;
            deleteSparepart(LP, id);
        }

        // =============================
        // 14. Delete Relasi
        // =============================
        else if (pilihan == 14) {
            string idM, idS;
            cout << "ID Mekanik: ";
            cin >> idM;
            cout << "ID Servis: ";
            cin >> idS;

            adrMekanik M = findMekanik(LM, idM);
            if (M != NULL) {
                deleteRelasi(M, idS);
            } else {
                cout << "Mekanik tidak ditemukan!\n";
            }
        }

        // =============================
        // DEFAULT
        // =============================
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
