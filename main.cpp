#include <iostream>
#include "tubes.h"
#include "tubes.cpp"

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   SISTEM MANAJEMEN BENGKEL\n";
    cout << "   MEKANIK-SERVIS-SPAREPART\n";
    cout << "========================================\n";
    cout << "a.  Insert element parent (Mekanik)\n";
    cout << "b.  Insert element child (Servis/Sparepart)\n";
    cout << "c.  Insert element relation\n";
    cout << "d.  Delete element parent (Mekanik)\n";
    cout << "e.  Delete element child (Servis/Sparepart)\n";
    cout << "f.  Delete element relation\n";
    cout << "g.  Find element Parent (Mekanik)\n";
    cout << "h.  Find element child (Servis/Sparepart)\n";
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
    listSparepart LSP;

    createListMekanik(LM);
    createListServis(LS);
    createListSparepart(LSP);

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
            char jenis;
            cout << "=== TAMBAH CHILD ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                elmServis servis;
                cout << "=== TAMBAH SERVIS ===\n";
                cout << "ID Servis: ";
                getline(cin, servis.IDServis);
                cout << "Nama Kendaraan: ";
                getline(cin, servis.namaKendaraan);
                cout << "Biaya Servis: ";
                cin >> servis.biayaServis;
                cin.ignore();
                insertServis(LS, servis);
            } else if (jenis == '2') {
                elmSparepart sparepart;
                cout << "=== TAMBAH SPAREPART ===\n";
                cout << "ID Sparepart: ";
                getline(cin, sparepart.IDSparepart);
                cout << "Nama Sparepart: ";
                getline(cin, sparepart.namaSparepart);
                cout << "Harga: ";
                cin >> sparepart.harga;
                cout << "Stok: ";
                cin >> sparepart.stok;
                cin.ignore();
                insertSparepart(LSP, sparepart);
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "c") {
            char jenis;
            cout << "=== TAMBAH RELASI ===\n";
            cout << "Pilih jenis relasi:\n";
            cout << "1. Mekanik-Servis\n";
            cout << "2. Servis-Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idMekanik, idServis;
                cout << "=== TAMBAH RELASI MEKANIK-SERVIS ===\n";
                cout << "ID Mekanik: ";
                getline(cin, idMekanik);
                cout << "ID Servis: ";
                getline(cin, idServis);
                insertRelationMekanikServis(LM, LS, idMekanik, idServis);
            } else if (jenis == '2') {
                string idServis, idSparepart;
                int jumlah;
                cout << "=== TAMBAH RELASI SERVIS-SPAREPART ===\n";
                cout << "ID Servis: ";
                getline(cin, idServis);
                cout << "ID Sparepart: ";
                getline(cin, idSparepart);
                cout << "Jumlah: ";
                cin >> jumlah;
                cin.ignore();
                insertRelationServisSparepart(LS, LSP, idServis, idSparepart, jumlah);
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "d") {
            string idMekanik;
            cout << "=== HAPUS MEKANIK ===\n";
            cout << "ID Mekanik yang akan dihapus: ";
            getline(cin, idMekanik);
            deleteMekanik(LM, idMekanik);

        } else if (pilihan == "e") {
            char jenis;
            cout << "=== HAPUS CHILD ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idServis;
                cout << "ID Servis yang akan dihapus: ";
                getline(cin, idServis);
                deleteServis(LS, idServis);
            } else if (jenis == '2') {
                string idSparepart;
                cout << "ID Sparepart yang akan dihapus: ";
                getline(cin, idSparepart);
                deleteSparepart(LSP, idSparepart);
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "f") {
            char jenis;
            cout << "=== HAPUS RELASI ===\n";
            cout << "Pilih jenis relasi:\n";
            cout << "1. Mekanik-Servis\n";
            cout << "2. Servis-Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idMekanik, idServis;
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
            } else if (jenis == '2') {
                string idServis, idSparepart;
                cout << "ID Servis: ";
                getline(cin, idServis);
                cout << "ID Sparepart: ";
                getline(cin, idSparepart);
                adrServis S = findServis(LS, idServis);
                if (S != NULL) {
                    deleteRelationServisSparepart(S, idSparepart);
                } else {
                    cout << "Servis tidak ditemukan.\n";
                }
            } else {
                cout << "Pilihan tidak valid.\n";
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
            char jenis;
            cout << "=== CARI CHILD ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idServis;
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
            } else if (jenis == '2') {
                string idSparepart;
                cout << "ID Sparepart: ";
                getline(cin, idSparepart);
                adrSparepart SP = findSparepart(LSP, idSparepart);
                if (SP != NULL) {
                    cout << "Sparepart ditemukan:\n";
                    cout << "ID: " << SP->infoSparepart.IDSparepart
                         << " | Nama: " << SP->infoSparepart.namaSparepart
                         << " | Harga: Rp " << SP->infoSparepart.harga
                         << " | Stok: " << SP->infoSparepart.stok << "\n";
                } else {
                    cout << "Sparepart tidak ditemukan.\n";
                }
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "i") {
            char jenis;
            cout << "=== CARI RELASI ===\n";
            cout << "Pilih jenis relasi:\n";
            cout << "1. Mekanik-Servis\n";
            cout << "2. Servis-Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idMekanik, idServis;
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
            } else if (jenis == '2') {
                string idServis, idSparepart;
                cout << "ID Servis: ";
                getline(cin, idServis);
                cout << "ID Sparepart: ";
                getline(cin, idSparepart);
                adrServis S = findServis(LS, idServis);
                if (S != NULL) {
                    if (findRelationServisSparepart(S, idSparepart)) {
                        cout << "Relasi ditemukan.\n";
                    } else {
                        cout << "Relasi tidak ditemukan.\n";
                    }
                } else {
                    cout << "Servis tidak ditemukan.\n";
                }
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "j") {
            showAllMekanik(LM);

        } else if (pilihan == "k") {
            char jenis;
            cout << "=== TAMPILKAN CHILD ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                showAllServis(LS);
            } else if (jenis == '2') {
                showAllSparepart(LSP);
            } else {
                cout << "Pilihan tidak valid.\n";
            }

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
            char jenis;
            cout << "=== COUNT RELASI DARI CHILD ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idServis;
                cout << "ID Servis: ";
                getline(cin, idServis);
                int count = countRelationFromServis(LM, idServis);
                cout << "Servis " << idServis << " ditangani oleh "
                     << count << " mekanik\n";
            } else if (jenis == '2') {
                string idSparepart;
                cout << "ID Sparepart: ";
                getline(cin, idSparepart);
                int count = countRelationFromSparepart(LS, idSparepart);
                cout << "Sparepart " << idSparepart << " digunakan dalam "
                     << count << " servis\n";
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "r") {
            char jenis;
            cout << "=== COUNT CHILD TANPA RELASI ===\n";
            cout << "Pilih jenis child:\n";
            cout << "1. Servis\n";
            cout << "2. Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                int count = countServisWithoutRelation(LM, LS);
                cout << "Jumlah servis yang tidak memiliki relasi: "
                     << count << "\n";
            } else if (jenis == '2') {
                int count = countSparepartWithoutRelation(LS, LSP);
                cout << "Jumlah sparepart yang tidak memiliki relasi: "
                     << count << "\n";
            } else {
                cout << "Pilihan tidak valid.\n";
            }

        } else if (pilihan == "s") {
            char jenis;
            cout << "=== EDIT RELASI ===\n";
            cout << "Pilih jenis relasi:\n";
            cout << "1. Mekanik-Servis\n";
            cout << "2. Servis-Sparepart\n";
            cout << "Pilihan (1/2): ";
            cin >> jenis;
            cin.ignore();

            if (jenis == '1') {
                string idMekanik, idServisLama, idServisBaru;
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
            } else if (jenis == '2') {
                string idServis, idSparepartLama, idSparepartBaru;
                int jumlahBaru;
                cout << "ID Servis: ";
                getline(cin, idServis);
                cout << "ID Sparepart Lama: ";
                getline(cin, idSparepartLama);
                cout << "ID Sparepart Baru: ";
                getline(cin, idSparepartBaru);
                cout << "Jumlah Baru: ";
                cin >> jumlahBaru;
                cin.ignore();
                adrServis S = findServis(LS, idServis);
                if (S != NULL) {
                    editRelationServisSparepart(S, idSparepartLama, idSparepartBaru, LSP, jumlahBaru);
                } else {
                    cout << "Servis tidak ditemukan.\n";
                }
            } else {
                cout << "Pilihan tidak valid.\n";
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
