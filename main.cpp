#include <iostream>
#include "tubes.h"
#include "tubes.cpp"

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "     SISTEM MANAJEMEN BENGKEL\n";
    cout << "   MEKANIK-SERVIS-SPAREPART (TIPE A)\n";
    cout << "========================================\n";
    cout << "a.  Insert element parent (Mekanik)\n";
    cout << "b.  Insert element child (Servis)\n";
    cout << "c.  Insert element relation\n";
    cout << "d.  Delete element parent (Mekanik)\n";
    cout << "e.  Delete element child (Servis)\n";
    cout << "f.  Delete element relation\n";
    cout << "g.  Find element Parent (Mekanik)\n";
    cout << "h.  Find element child (Servis)\n";
    cout << "i.  Find element relation\n";
    cout << "j.  Show all data di List Parent\n";
    cout << "k.  Show all data di List Child\n";
    cout << "l.  Show data child dari parent tertentu\n";
    cout << "m.  Show setiap data parent beserta child yang berelasi\n";
    cout << "n.  Show data child beserta data parent yang dimiliki\n";
    cout << "o.  Show data parent yang berelasi dengan child tertentu\n";
    cout << "p.  Count relation dari setiap element parent\n";
    cout << "q.  Count relation yang dimiliki oleh child tertentu\n";
    cout << "r.  Count element child yang tidak memiliki relasi\n";
    cout << "s.  Edit relasi / mengganti child dari parent tertentu\n";
    cout << "x.  Tampilkan Menu\n";
    cout << "0.  Keluar\n";
    cout << "========================================\n";
    cout << "Pilihan: ";
}

int main() {
    listMekanik LM;
    listServis LS;

    createListMekanik(LM);
    createListServis(LS);

    string pilihan;

    displayMenu();

    do {
        cout << "\nMasukkan pilihan (x untuk menu): ";
        getline(cin, pilihan);

        if (pilihan == "a") {
            elmMekanik mekanik;
            cout << "=== TAMBAH MEKANIK (PARENT) ===\n";
            cout << "ID Mekanik: ";
            getline(cin, mekanik.IDMekanik);
            cout << "Nama Mekanik: ";
            getline(cin, mekanik.namaMekanik);
            cout << "Jam Kerja: ";
            cin >> mekanik.jamKerja;
            cin.ignore();

            insertMekanik(LM, mekanik);

        } else if (pilihan == "b") {
            elmServis servis;
            cout << "=== TAMBAH SERVIS (CHILD) ===\n";
            cout << "ID Servis: ";
            getline(cin, servis.IDServis);
            cout << "Nama Kendaraan: ";
            getline(cin, servis.namaKendaraan);
            cout << "Biaya Servis: ";
            cin >> servis.biayaServis;
            cin.ignore();

            insertServis(LS, servis);

        } else if (pilihan == "c") {
            string idMekanik, idServis;
            cout << "=== TAMBAH RELASI MEKANIK-SERVIS ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);
            cout << "ID Servis: ";
            getline(cin, idServis);

            insertRelationMekanikServis(LM, LS, idMekanik, idServis);

        } else if (pilihan == "d") {
            string idMekanik;
            cout << "=== HAPUS MEKANIK ===\n";
            cout << "ID Mekanik yang akan dihapus: ";
            getline(cin, idMekanik);

            deleteMekanik(LM, idMekanik);

        } else if (pilihan == "e") {
            string idServis;
            cout << "=== HAPUS SERVIS ===\n";
            cout << "ID Servis yang akan dihapus: ";
            getline(cin, idServis);

            deleteServis(LS, idServis);

        } else if (pilihan == "f") {
            string idMekanik, idServis;
            cout << "=== HAPUS RELASI MEKANIK-SERVIS ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);
            cout << "ID Servis: ";
            getline(cin, idServis);

            adrMekanik M = findMekanik(LM, idMekanik);
            if (M != NULL) {
                deleteRelationMekanikServis(M, idServis);
            } else {
                cout << "Mekanik tidak ditemukan.\n";
            }

        } else if (pilihan == "g") {
            string idMekanik;
            cout << "=== CARI MEKANIK ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);

            adrMekanik M = findMekanik(LM, idMekanik);
            if (M != NULL) {
                cout << "Mekanik ditemukan:\n";
                cout << "ID: " << M->infoMekanik.IDMekanik
                     << " | Nama: " << M->infoMekanik.namaMekanik
                     << " | Jam Kerja: " << M->infoMekanik.jamKerja << " jam\n";
            } else {
                cout << "Mekanik tidak ditemukan.\n";
            }

        } else if (pilihan == "h") {
            string idServis;
            cout << "=== CARI SERVIS ===\n";
            cout << "ID Servis: ";
            getline(cin, idServis);

            adrServis S = findServis(LS, idServis);
            if (S != NULL) {
                cout << "Servis ditemukan:\n";
                cout << "ID: " << S->infoServis.IDServis
                     << " | Kendaraan: " << S->infoServis.namaKendaraan
                     << " | Biaya: Rp " << S->infoServis.biayaServis << "\n";
            } else {
                cout << "Servis tidak ditemukan.\n";
            }

        } else if (pilihan == "i") {
            string idMekanik, idServis;
            cout << "=== CARI RELASI MEKANIK-SERVIS ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);
            cout << "ID Servis: ";
            getline(cin, idServis);

            adrMekanik M = findMekanik(LM, idMekanik);
            if (M != NULL) {
                if (findRelationMekanikServis(M, idServis)) {
                    cout << "Relasi ditemukan.\n";
                } else {
                    cout << "Relasi tidak ditemukan.\n";
                }
            } else {
                cout << "Mekanik tidak ditemukan.\n";
            }

        } else if (pilihan == "j") {
            showAllMekanik(LM);

        } else if (pilihan == "k") {
            showAllServis(LS);

        } else if (pilihan == "l") {
            string idMekanik;
            cout << "=== TAMPILKAN SERVIS DARI MEKANIK ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);

            adrMekanik M = findMekanik(LM, idMekanik);
            if (M != NULL) {
                showServisFromMekanik(M);
            } else {
                cout << "Mekanik tidak ditemukan.\n";
            }

        } else if (pilihan == "m") {
            showAllMekanikWithServis(LM);

        } else if (pilihan == "n") {
            showAllServisWithMekanik(LM, LS);

        } else if (pilihan == "o") {
            string idServis;
            cout << "=== TAMPILKAN MEKANIK DARI SERVIS ===\n";
            cout << "ID Servis: ";
            getline(cin, idServis);

            showMekanikFromServis(LM, idServis);

        } else if (pilihan == "p") {
            cout << "=== COUNT RELASI DARI SETIAP MEKANIK ===\n";
            adrMekanik M = LM.firstMekanik;
            if (M == NULL) {
                cout << "Tidak ada data mekanik.\n";
            } else {
                while (M != NULL) {
                    int count = countRelationMekanikServis(M);
                    cout << "Mekanik " << M->infoMekanik.namaMekanik
                         << " menangani " << count << " servis\n";
                    M = M->nextMekanik;
                }
            }

        } else if (pilihan == "q") {
            string idServis;
            cout << "=== COUNT RELASI DARI SERVIS ===\n";
            cout << "ID Servis: ";
            getline(cin, idServis);

            int count = countRelationFromServis(LM, idServis);
            cout << "Servis " << idServis << " ditangani oleh "
                 << count << " mekanik\n";

        } else if (pilihan == "r") {
            cout << "=== COUNT SERVIS TANPA RELASI ===\n";
            int count = countServisWithoutRelation(LM, LS);
            cout << "Jumlah servis yang tidak memiliki relasi: "
                 << count << "\n";

        } else if (pilihan == "s") {
            string idMekanik, idServisLama, idServisBaru;
            cout << "=== EDIT RELASI MEKANIK-SERVIS ===\n";
            cout << "ID Mekanik: ";
            getline(cin, idMekanik);
            cout << "ID Servis Lama: ";
            getline(cin, idServisLama);
            cout << "ID Servis Baru: ";
            getline(cin, idServisBaru);

            adrMekanik M = findMekanik(LM, idMekanik);
            if (M != NULL) {
                editRelationMekanikServis(M, idServisLama, idServisBaru, LS);
            } else {
                cout << "Mekanik tidak ditemukan.\n";
            }

        } else if (pilihan == "x") {
            displayMenu();

        } else if (pilihan == "0") {
            cout << "Terima kasih! Program selesai.\n";

        } else {
            cout << "Pilihan tidak valid. Masukkan 'x' untuk melihat menu.\n";
        }

    } while (pilihan != "0");

    return 0;
}
