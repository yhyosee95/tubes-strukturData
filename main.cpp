#include <iostream>
#include "tubes.h"
using namespace std;

int main() {
    listMekanik LM;
    listServis LS;
    listSparepart LP;

    createListMekanik(LM);
    createListServis(LS);
    createListSparepart(LP);

    int pilih = -1;

    while (true) {
        cout << "\n=== MENU BENGKEL ===\n";
        cout << "1. Tambah Mekanik\n";
        cout << "2. Tambah Servis\n";
        cout << "3. Tambah Sparepart\n";
        cout << "4. Hubungkan Mekanik - Servis\n";
        cout << "5. Tampilkan Semua Relasi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 0) {
            cout << "Program selesai\n";
            break;
        }

        if (pilih == 1) {
            elmMekanik m;
            cout << "ID Mekanik: "; cin >> m.IDMekanik;
            cin.ignore();
            cout << "Nama Mekanik: "; getline(cin, m.namaMekanik);
            cout << "Jam Kerja: "; cin >> m.jamKerja;
            insertMekanik(LM, createElmMekanik(m));
        }

        if (pilih == 2) {
            elmServis s;
            cout << "ID Servis: "; cin >> s.IDServis;
            cin.ignore();
            cout << "Nama Kendaraan: "; getline(cin, s.namaKendaraan);
            cout << "Biaya Servis: "; cin >> s.biayaServis;
            insertServis(LS, createElmServis(s));
        }

        if (pilih == 3) {
            elmSparepart p;
            cout << "ID Sparepart: "; cin >> p.IDSparepart;
            cin.ignore();
            cout << "Nama Sparepart: "; getline(cin, p.namaSparepart);
            cout << "Harga: "; cin >> p.harga;
            insertSparepart(LP, createElmSparepart(p));
        }

        if (pilih == 4) {
            string idM, idS;
            cout << "ID Mekanik: "; cin >> idM;
            cout << "ID Servis: "; cin >> idS;
            adrMekanik M = findMekanik(LM, idM);
            adrServis S = findServis(LS, idS);
            if (M && S) insertRelasi(M, S);
            else cout << "Data tidak ditemukan\n";
        }

        if (pilih == 5) {
            showAllRelasi(LM);
        }
    }
    return 0;
}
