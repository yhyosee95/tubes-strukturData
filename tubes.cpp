#include "tubes.h"
#include <iostream>
using namespace std;

/* ================= INISIALISASI ================= */
void createListMekanik(listMekanik &LM) {
    LM.firstMekanik = NULL;
}

void createListServis(listServis &LS) {
    LS.firstServis = NULL;
}

void createListSparepart(listSparepart &LSP) {
    LSP.firstSparepart = NULL;
}

/* ================= FUNGSI UTAMA ================= */

// a. Insert element parent (Mekanik)
void insertMekanik(listMekanik &LM, elmMekanik data) {
    adrMekanik M = new nodeMekanik;
    M->infoMekanik = data;
    M->nextMekanik = NULL;
    M->firstRelasiMekanikServis = NULL;

    if (LM.firstMekanik == NULL) {
        LM.firstMekanik = M;
    } else {
        adrMekanik curr = LM.firstMekanik;
        while (curr->nextMekanik != NULL) {
            curr = curr->nextMekanik;
        }
        curr->nextMekanik = M;
    }
    cout << "Mekanik berhasil ditambahkan.\n";
}

// b. Insert element child (Servis)
void insertServis(listServis &LS, elmServis data) {
    adrServis S = new nodeServis;
    S->infoServis = data;
    S->nextServis = NULL;
    S->firstRelasiServisSparepart = NULL;

    if (LS.firstServis == NULL) {
        LS.firstServis = S;
    } else {
        adrServis curr = LS.firstServis;
        while (curr->nextServis != NULL) {
            curr = curr->nextServis;
        }
        curr->nextServis = S;
    }
    cout << "Servis berhasil ditambahkan.\n";
}

// b. Insert element child (Sparepart)
void insertSparepart(listSparepart &LSP, elmSparepart data) {
    adrSparepart SP = new nodeSparepart;
    SP->infoSparepart = data;
    SP->nextSparepart = NULL;

    if (LSP.firstSparepart == NULL) {
        LSP.firstSparepart = SP;
    } else {
        adrSparepart curr = LSP.firstSparepart;
        while (curr->nextSparepart != NULL) {
            curr = curr->nextSparepart;
        }
        curr->nextSparepart = SP;
    }
    cout << "Sparepart berhasil ditambahkan.\n";
}

// c. Insert element relation (Mekanik-Servis)
void insertRelationMekanikServis(listMekanik &LM, listServis &LS, string IDMekanik, string IDServis) {
    adrMekanik M = findMekanik(LM, IDMekanik);
    adrServis S = findServis(LS, IDServis);

    if (M == NULL) {
        cout << "Mekanik dengan ID " << IDMekanik << " tidak ditemukan.\n";
        return;
    }

    if (S == NULL) {
        cout << "Servis dengan ID " << IDServis << " tidak ditemukan.\n";
        return;
    }

    // Cek apakah relasi sudah ada
    if (findRelationMekanikServis(M, IDServis)) {
        cout << "Relasi antara mekanik " << IDMekanik << " dan servis " << IDServis << " sudah ada.\n";
        return;
    }

    // Buat node relasi baru
    adrRelasiMekanikServis R = new nodeRelasiMekanikServis;
    R->servis = S;
    R->nextRelasiMekanikServis = NULL;

    // Tambahkan relasi ke list relasi mekanik
    if (M->firstRelasiMekanikServis == NULL) {
        M->firstRelasiMekanikServis = R;
    } else {
        adrRelasiMekanikServis curr = M->firstRelasiMekanikServis;
        while (curr->nextRelasiMekanikServis != NULL) {
            curr = curr->nextRelasiMekanikServis;
        }
        curr->nextRelasiMekanikServis = R;
    }

    cout << "Relasi antara mekanik " << IDMekanik << " dan servis " << IDServis << " berhasil dibuat.\n";
}

// c. Insert element relation (Servis-Sparepart)
void insertRelationServisSparepart(listServis &LS, listSparepart &LSP, string IDServis, string IDSparepart, int jumlah) {
    adrServis S = findServis(LS, IDServis);
    adrSparepart SP = findSparepart(LSP, IDSparepart);

    if (S == NULL) {
        cout << "Servis dengan ID " << IDServis << " tidak ditemukan.\n";
        return;
    }

    if (SP == NULL) {
        cout << "Sparepart dengan ID " << IDSparepart << " tidak ditemukan.\n";
        return;
    }

    // Cek apakah stok cukup
    if (SP->infoSparepart.stok < jumlah) {
        cout << "Stok sparepart tidak mencukupi. Stok tersedia: " << SP->infoSparepart.stok << "\n";
        return;
    }

    // Cek apakah relasi sudah ada
    if (findRelationServisSparepart(S, IDSparepart)) {
        cout << "Relasi antara servis " << IDServis << " dan sparepart " << IDSparepart << " sudah ada.\n";
        return;
    }

    // Buat node relasi baru
    adrRelasiServisSparepart R = new nodeRelasiServisSparepart;
    R->sparepart = SP;
    R->jumlah = jumlah;
    R->nextRelasiServisSparepart = NULL;

    // Kurangi stok sparepart
    SP->infoSparepart.stok -= jumlah;

    // Tambahkan relasi ke list relasi servis
    if (S->firstRelasiServisSparepart == NULL) {
        S->firstRelasiServisSparepart = R;
    } else {
        adrRelasiServisSparepart curr = S->firstRelasiServisSparepart;
        while (curr->nextRelasiServisSparepart != NULL) {
            curr = curr->nextRelasiServisSparepart;
        }
        curr->nextRelasiServisSparepart = R;
    }

    cout << "Relasi antara servis " << IDServis << " dan sparepart " << IDSparepart << " berhasil dibuat.\n";
}

// d. Delete element parent (Mekanik)
void deleteMekanik(listMekanik &LM, string IDMekanik) {
    if (LM.firstMekanik == NULL) {
        cout << "List mekanik kosong.\n";
        return;
    }

    adrMekanik M = LM.firstMekanik;
    adrMekanik prev = NULL;

    // Cari mekanik yang akan dihapus
    while (M != NULL && M->infoMekanik.IDMekanik != IDMekanik) {
        prev = M;
        M = M->nextMekanik;
    }

    if (M == NULL) {
        cout << "Mekanik dengan ID " << IDMekanik << " tidak ditemukan.\n";
        return;
    }

    // Hapus semua relasi yang terkait
    adrRelasiMekanikServis R = M->firstRelasiMekanikServis;
    while (R != NULL) {
        adrRelasiMekanikServis temp = R;
        R = R->nextRelasiMekanikServis;
        delete temp;
    }

    // Hapus mekanik dari list
    if (prev == NULL) {
        LM.firstMekanik = M->nextMekanik;
    } else {
        prev->nextMekanik = M->nextMekanik;
    }

    delete M;
    cout << "Mekanik dengan ID " << IDMekanik << " berhasil dihapus.\n";
}

// e. Delete element child (Servis)
void deleteServis(listServis &LS, string IDServis) {
    if (LS.firstServis == NULL) {
        cout << "List servis kosong.\n";
        return;
    }

    adrServis S = LS.firstServis;
    adrServis prev = NULL;

    // Cari servis yang akan dihapus
    while (S != NULL && S->infoServis.IDServis != IDServis) {
        prev = S;
        S = S->nextServis;
    }

    if (S == NULL) {
        cout << "Servis dengan ID " << IDServis << " tidak ditemukan.\n";
        return;
    }

    // Hapus semua relasi sparepart yang terkait dan kembalikan stok
    adrRelasiServisSparepart R = S->firstRelasiServisSparepart;
    while (R != NULL) {
        R->sparepart->infoSparepart.stok += R->jumlah;
        adrRelasiServisSparepart temp = R;
        R = R->nextRelasiServisSparepart;
        delete temp;
    }

    // Hapus servis dari list
    if (prev == NULL) {
        LS.firstServis = S->nextServis;
    } else {
        prev->nextServis = S->nextServis;
    }

    delete S;
    cout << "Servis dengan ID " << IDServis << " berhasil dihapus.\n";
}

// e. Delete element child (Sparepart)
void deleteSparepart(listSparepart &LSP, string IDSparepart) {
    if (LSP.firstSparepart == NULL) {
        cout << "List sparepart kosong.\n";
        return;
    }

    adrSparepart SP = LSP.firstSparepart;
    adrSparepart prev = NULL;

    // Cari sparepart yang akan dihapus
    while (SP != NULL && SP->infoSparepart.IDSparepart != IDSparepart) {
        prev = SP;
        SP = SP->nextSparepart;
    }

    if (SP == NULL) {
        cout << "Sparepart dengan ID " << IDSparepart << " tidak ditemukan.\n";
        return;
    }

    // Hapus sparepart dari list
    if (prev == NULL) {
        LSP.firstSparepart = SP->nextSparepart;
    } else {
        prev->nextSparepart = SP->nextSparepart;
    }

    delete SP;
    cout << "Sparepart dengan ID " << IDSparepart << " berhasil dihapus.\n";
}

// f. Delete element relation (Mekanik-Servis)
void deleteRelationMekanikServis(adrMekanik mekanik, string IDServis) {
    if (mekanik == NULL) {
        cout << "Mekanik tidak valid.\n";
        return;
    }

    if (mekanik->firstRelasiMekanikServis == NULL) {
        cout << "Mekanik tidak memiliki relasi servis.\n";
        return;
    }

    adrRelasiMekanikServis R = mekanik->firstRelasiMekanikServis;
    adrRelasiMekanikServis prev = NULL;

    // Cari relasi yang akan dihapus
    while (R != NULL && R->servis->infoServis.IDServis != IDServis) {
        prev = R;
        R = R->nextRelasiMekanikServis;
    }

    if (R == NULL) {
        cout << "Relasi dengan servis " << IDServis << " tidak ditemukan pada mekanik ini.\n";
        return;
    }

    // Hapus relasi
    if (prev == NULL) {
        mekanik->firstRelasiMekanikServis = R->nextRelasiMekanikServis;
    } else {
        prev->nextRelasiMekanikServis = R->nextRelasiMekanikServis;
    }

    delete R;
    cout << "Relasi dengan servis " << IDServis << " berhasil dihapus dari mekanik.\n";
}

// f. Delete element relation (Servis-Sparepart)
void deleteRelationServisSparepart(adrServis servis, string IDSparepart) {
    if (servis == NULL) {
        cout << "Servis tidak valid.\n";
        return;
    }

    if (servis->firstRelasiServisSparepart == NULL) {
        cout << "Servis tidak memiliki relasi sparepart.\n";
        return;
    }

    adrRelasiServisSparepart R = servis->firstRelasiServisSparepart;
    adrRelasiServisSparepart prev = NULL;

    // Cari relasi yang akan dihapus
    while (R != NULL && R->sparepart->infoSparepart.IDSparepart != IDSparepart) {
        prev = R;
        R = R->nextRelasiServisSparepart;
    }

    if (R == NULL) {
        cout << "Relasi dengan sparepart " << IDSparepart << " tidak ditemukan pada servis ini.\n";
        return;
    }

    // Kembalikan stok sparepart
    R->sparepart->infoSparepart.stok += R->jumlah;

    // Hapus relasi
    if (prev == NULL) {
        servis->firstRelasiServisSparepart = R->nextRelasiServisSparepart;
    } else {
        prev->nextRelasiServisSparepart = R->nextRelasiServisSparepart;
    }

    delete R;
    cout << "Relasi dengan sparepart " << IDSparepart << " berhasil dihapus dari servis.\n";
}

// g. Find element Parent (Mekanik)
adrMekanik findMekanik(listMekanik LM, string IDMekanik) {
    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        if (M->infoMekanik.IDMekanik == IDMekanik) {
            return M;
        }
        M = M->nextMekanik;
    }
    return NULL;
}

// h. Find element child (Servis)
adrServis findServis(listServis LS, string IDServis) {
    adrServis S = LS.firstServis;
    while (S != NULL) {
        if (S->infoServis.IDServis == IDServis) {
            return S;
        }
        S = S->nextServis;
    }
    return NULL;
}

// h. Find element child (Sparepart)
adrSparepart findSparepart(listSparepart LSP, string IDSparepart) {
    adrSparepart SP = LSP.firstSparepart;
    while (SP != NULL) {
        if (SP->infoSparepart.IDSparepart == IDSparepart) {
            return SP;
        }
        SP = SP->nextSparepart;
    }
    return NULL;
}

// i. Find element relation (Mekanik-Servis)
bool findRelationMekanikServis(adrMekanik mekanik, string IDServis) {
    if (mekanik == NULL) return false;

    adrRelasiMekanikServis R = mekanik->firstRelasiMekanikServis;
    while (R != NULL) {
        if (R->servis->infoServis.IDServis == IDServis) {
            return true;
        }
        R = R->nextRelasiMekanikServis;
    }
    return false;
}

// i. Find element relation (Servis-Sparepart)
bool findRelationServisSparepart(adrServis servis, string IDSparepart) {
    if (servis == NULL) return false;

    adrRelasiServisSparepart R = servis->firstRelasiServisSparepart;
    while (R != NULL) {
        if (R->sparepart->infoSparepart.IDSparepart == IDSparepart) {
            return true;
        }
        R = R->nextRelasiServisSparepart;
    }
    return false;
}

// j. Show all data di List Parent (Mekanik)
void showAllMekanik(listMekanik LM) {
    cout << "\n=== DATA SEMUA MEKANIK (PARENT) ===\n";
    if (LM.firstMekanik == NULL) {
        cout << "Tidak ada data mekanik.\n";
        return;
    }

    adrMekanik M = LM.firstMekanik;
    int no = 1;
    while (M != NULL) {
        cout << no << ". ID: " << M->infoMekanik.IDMekanik
             << " | Nama: " << M->infoMekanik.namaMekanik
             << " | Jam Kerja: " << M->infoMekanik.jamKerja << " jam"
             << " | Jumlah Servis: " << countRelationMekanikServis(M) << "\n";
        M = M->nextMekanik;
        no++;
    }
}

// k. Show all data di List Child (Servis)
void showAllServis(listServis LS) {
    cout << "\n=== DATA SEMUA SERVIS (CHILD) ===\n";
    if (LS.firstServis == NULL) {
        cout << "Tidak ada data servis.\n";
        return;
    }

    adrServis S = LS.firstServis;
    int no = 1;
    while (S != NULL) {
        cout << no << ". ID: " << S->infoServis.IDServis
             << " | Kendaraan: " << S->infoServis.namaKendaraan
             << " | Biaya: Rp " << S->infoServis.biayaServis << "\n";
        S = S->nextServis;
        no++;
    }
}

// k. Show all data di List Child (Sparepart)
void showAllSparepart(listSparepart LSP) {
    cout << "\n=== DATA SEMUA SPAREPART (CHILD) ===\n";
    if (LSP.firstSparepart == NULL) {
        cout << "Tidak ada data sparepart.\n";
        return;
    }

    adrSparepart SP = LSP.firstSparepart;
    int no = 1;
    while (SP != NULL) {
        cout << no << ". ID: " << SP->infoSparepart.IDSparepart
             << " | Nama: " << SP->infoSparepart.namaSparepart
             << " | Harga: Rp " << SP->infoSparepart.harga
             << " | Stok: " << SP->infoSparepart.stok << "\n";
        SP = SP->nextSparepart;
        no++;
    }
}

// l. Show data child dari parent tertentu (Servis dari Mekanik)
void showServisFromMekanik(adrMekanik mekanik) {
    if (mekanik == NULL) {
        cout << "Mekanik tidak valid.\n";
        return;
    }

    cout << "\n=== SERVIS YANG DITANGANI OLEH: " << mekanik->infoMekanik.namaMekanik << " ===\n";
    if (mekanik->firstRelasiMekanikServis == NULL) {
        cout << "Mekanik ini tidak menangani servis apapun.\n";
        return;
    }

    adrRelasiMekanikServis R = mekanik->firstRelasiMekanikServis;
    int no = 1;
    while (R != NULL) {
        cout << no << ". ID: " << R->servis->infoServis.IDServis
             << " | Kendaraan: " << R->servis->infoServis.namaKendaraan
             << " | Biaya: Rp " << R->servis->infoServis.biayaServis << "\n";
        R = R->nextRelasiMekanikServis;
        no++;
    }
}

// m. Show setiap data parent beserta data child yang berelasi dengannya
void showAllMekanikWithServis(listMekanik LM) {
    cout << "\n=== SEMUA MEKANIK BESERTA SERVIS YANG DITANGANI ===\n";
    if (LM.firstMekanik == NULL) {
        cout << "Tidak ada data mekanik.\n";
        return;
    }

    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        cout << "\nMekanik: " << M->infoMekanik.namaMekanik
             << " (ID: " << M->infoMekanik.IDMekanik << ")\n";

        if (M->firstRelasiMekanikServis == NULL) {
            cout << "  - Tidak menangani servis\n";
        } else {
            adrRelasiMekanikServis R = M->firstRelasiMekanikServis;
            while (R != NULL) {
                cout << "  - " << R->servis->infoServis.namaKendaraan
                     << " (ID: " << R->servis->infoServis.IDServis << ")\n";
                R = R->nextRelasiMekanikServis;
            }
        }
        M = M->nextMekanik;
    }
}

// n. Show data child beserta data parent yang masing-masing child miliki
void showAllServisWithMekanik(listMekanik LM, listServis LS) {
    cout << "\n=== SEMUA SERVIS BESERTA MEKANIK YANG MENANGANI ===\n";
    if (LS.firstServis == NULL) {
        cout << "Tidak ada data servis.\n";
        return;
    }

    adrServis S = LS.firstServis;
    while (S != NULL) {
        cout << "\nServis: " << S->infoServis.namaKendaraan
             << " (ID: " << S->infoServis.IDServis << ")\n";

        // Cari semua mekanik yang menangani servis ini
        adrMekanik M = LM.firstMekanik;
        bool ditangani = false;

        while (M != NULL) {
            adrRelasiMekanikServis R = M->firstRelasiMekanikServis;
            while (R != NULL) {
                if (R->servis->infoServis.IDServis == S->infoServis.IDServis) {
                    cout << "  - Ditangani oleh: " << M->infoMekanik.namaMekanik
                         << " (ID: " << M->infoMekanik.IDMekanik << ")\n";
                    ditangani = true;
                    break;
                }
                R = R->nextRelasiMekanikServis;
            }
            M = M->nextMekanik;
        }

        if (!ditangani) {
            cout << "  - Tidak ditangani oleh mekanik manapun\n";
        }

        S = S->nextServis;
    }
}

// o. Show data parent yang berelasi dengan child tertentu
void showMekanikFromServis(listMekanik LM, string IDServis) {
    cout << "\n=== MEKANIK YANG MENANGANI SERVIS ID: " << IDServis << " ===\n";

    adrMekanik M = LM.firstMekanik;
    bool ditemukan = false;

    while (M != NULL) {
        adrRelasiMekanikServis R = M->firstRelasiMekanikServis;
        while (R != NULL) {
            if (R->servis->infoServis.IDServis == IDServis) {
                cout << "  - " << M->infoMekanik.namaMekanik
                     << " (ID: " << M->infoMekanik.IDMekanik
                     << ", Jam Kerja: " << M->infoMekanik.jamKerja << " jam)\n";
                ditemukan = true;
                break;
            }
            R = R->nextRelasiMekanikServis;
        }
        M = M->nextMekanik;
    }

    if (!ditemukan) {
        cout << "Servis ini tidak ditangani oleh mekanik manapun.\n";
    }
}

// p. Count relation dari setiap element parent
int countRelationMekanikServis(adrMekanik mekanik) {
    if (mekanik == NULL) return 0;

    int count = 0;
    adrRelasiMekanikServis R = mekanik->firstRelasiMekanikServis;
    while (R != NULL) {
        count++;
        R = R->nextRelasiMekanikServis;
    }
    return count;
}

// q. Count relation yang dimiliki oleh child tertentu
int countRelationFromServis(listMekanik LM, string IDServis) {
    int count = 0;

    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        adrRelasiMekanikServis R = M->firstRelasiMekanikServis;
        while (R != NULL) {
            if (R->servis->infoServis.IDServis == IDServis) {
                count++;
                break;
            }
            R = R->nextRelasiMekanikServis;
        }
        M = M->nextMekanik;
    }

    return count;
}

// r. Count element child yang tidak memiliki relasi
int countServisWithoutRelation(listMekanik LM, listServis LS) {
    int count = 0;

    adrServis S = LS.firstServis;
    while (S != NULL) {
        if (countRelationFromServis(LM, S->infoServis.IDServis) == 0) {
            count++;
        }
        S = S->nextServis;
    }

    return count;
}

// s. Edit relasi / mengganti child dari parent tertentu
void editRelationMekanikServis(adrMekanik mekanik, string IDServisLama, string IDServisBaru, listServis LS) {
    if (mekanik == NULL) {
        cout << "Mekanik tidak valid.\n";
        return;
    }

    // Cek apakah servis lama ada di relasi mekanik
    if (!findRelationMekanikServis(mekanik, IDServisLama)) {
        cout << "Servis lama (" << IDServisLama << ") tidak ditemukan dalam relasi mekanik ini.\n";
        return;
    }

    // Cek apakah servis baru ada di list servis
    adrServis SBaru = findServis(LS, IDServisBaru);
    if (SBaru == NULL) {
        cout << "Servis baru (" << IDServisBaru << ") tidak ditemukan.\n";
        return;
    }

    // Hapus relasi lama
    deleteRelationMekanikServis(mekanik, IDServisLama);

    // Tambahkan relasi baru
    adrRelasiMekanikServis R = new nodeRelasiMekanikServis;
    R->servis = SBaru;
    R->nextRelasiMekanikServis = NULL;

    if (mekanik->firstRelasiMekanikServis == NULL) {
        mekanik->firstRelasiMekanikServis = R;
    } else {
        adrRelasiMekanikServis curr = mekanik->firstRelasiMekanikServis;
        while (curr->nextRelasiMekanikServis != NULL) {
            curr = curr->nextRelasiMekanikServis;
        }
        curr->nextRelasiMekanikServis = R;
    }

    cout << "Relasi berhasil diedit: " << IDServisLama << " -> " << IDServisBaru << "\n";
}

/* ================= FUNGSI TAMBAHAN UNTUK SERVIS-SPAREPART ================= */

void showSparepartFromServis(adrServis servis) {
    if (servis == NULL) {
        cout << "Servis tidak valid.\n";
        return;
    }

    cout << "\n=== SPAREPART YANG DIGUNAKAN DALAM SERVIS: " << servis->infoServis.namaKendaraan << " ===\n";
    if (servis->firstRelasiServisSparepart == NULL) {
        cout << "Servis ini tidak menggunakan sparepart apapun.\n";
        return;
    }

    adrRelasiServisSparepart R = servis->firstRelasiServisSparepart;
    int no = 1;
    int totalBiaya = 0;
    while (R != NULL) {
        int subtotal = R->sparepart->infoSparepart.harga * R->jumlah;
        cout << no << ". ID: " << R->sparepart->infoSparepart.IDSparepart
             << " | Nama: " << R->sparepart->infoSparepart.namaSparepart
             << " | Jumlah: " << R->jumlah
             << " | Harga: Rp " << R->sparepart->infoSparepart.harga
             << " | Subtotal: Rp " << subtotal << "\n";
        totalBiaya += subtotal;
        R = R->nextRelasiServisSparepart;
        no++;
    }
    cout << "Total biaya sparepart: Rp " << totalBiaya << "\n";
}

void showAllServisWithSparepart(listServis LS) {
    cout << "\n=== SEMUA SERVIS BESERTA SPAREPART YANG DIGUNAKAN ===\n";
    if (LS.firstServis == NULL) {
        cout << "Tidak ada data servis.\n";
        return;
    }

    adrServis S = LS.firstServis;
    while (S != NULL) {
        cout << "\nServis: " << S->infoServis.namaKendaraan
             << " (ID: " << S->infoServis.IDServis << ")\n";

        if (S->firstRelasiServisSparepart == NULL) {
            cout << "  - Tidak menggunakan sparepart\n";
        } else {
            adrRelasiServisSparepart R = S->firstRelasiServisSparepart;
            while (R != NULL) {
                cout << "  - " << R->sparepart->infoSparepart.namaSparepart
                     << " (ID: " << R->sparepart->infoSparepart.IDSparepart
                     << ", Jumlah: " << R->jumlah << ")\n";
                R = R->nextRelasiServisSparepart;
            }
        }
        S = S->nextServis;
    }
}

void showServisFromSparepart(listServis LS, string IDSparepart) {
    cout << "\n=== SERVIS YANG MENGGUNAKAN SPAREPART ID: " << IDSparepart << " ===\n";

    adrServis S = LS.firstServis;
    bool ditemukan = false;

    while (S != NULL) {
        adrRelasiServisSparepart R = S->firstRelasiServisSparepart;
        while (R != NULL) {
            if (R->sparepart->infoSparepart.IDSparepart == IDSparepart) {
                cout << "  - " << S->infoServis.namaKendaraan
                     << " (ID: " << S->infoServis.IDServis
                     << ", Jumlah: " << R->jumlah << ")\n";
                ditemukan = true;
                break;
            }
            R = R->nextRelasiServisSparepart;
        }
        S = S->nextServis;
    }

    if (!ditemukan) {
        cout << "Sparepart ini tidak digunakan dalam servis manapun.\n";
    }
}

int countRelationFromSparepart(listServis LS, string IDSparepart) {
    int count = 0;

    adrServis S = LS.firstServis;
    while (S != NULL) {
        adrRelasiServisSparepart R = S->firstRelasiServisSparepart;
        while (R != NULL) {
            if (R->sparepart->infoSparepart.IDSparepart == IDSparepart) {
                count++;
                break;
            }
            R = R->nextRelasiServisSparepart;
        }
        S = S->nextServis;
    }

    return count;
}

int countSparepartWithoutRelation(listServis LS, listSparepart LSP) {
    int count = 0;

    adrSparepart SP = LSP.firstSparepart;
    while (SP != NULL) {
        if (countRelationFromSparepart(LS, SP->infoSparepart.IDSparepart) == 0) {
            count++;
        }
        SP = SP->nextSparepart;
    }

    return count;
}

void editRelationServisSparepart(adrServis servis, string IDSparepartLama, string IDSparepartBaru, listSparepart LSP, int jumlahBaru) {
    if (servis == NULL) {
        cout << "Servis tidak valid.\n";
        return;
    }

    if (!findRelationServisSparepart(servis, IDSparepartLama)) {
        cout << "Sparepart lama (" << IDSparepartLama << ") tidak ditemukan dalam relasi servis ini.\n";
        return;
    }

    adrSparepart SPBaru = findSparepart(LSP, IDSparepartBaru);
    if (SPBaru == NULL) {
        cout << "Sparepart baru (" << IDSparepartBaru << ") tidak ditemukan.\n";
        return;
    }

    if (SPBaru->infoSparepart.stok < jumlahBaru) {
        cout << "Stok sparepart baru tidak mencukupi. Stok tersedia: " << SPBaru->infoSparepart.stok << "\n";
        return;
    }

    // Cari relasi lama
    adrRelasiServisSparepart RLama = servis->firstRelasiServisSparepart;
    while (RLama != NULL && RLama->sparepart->infoSparepart.IDSparepart != IDSparepartLama) {
        RLama = RLama->nextRelasiServisSparepart;
    }

    if (RLama != NULL) {
        // Kembalikan stok lama
        RLama->sparepart->infoSparepart.stok += RLama->jumlah;

        // Kurangi stok baru
        SPBaru->infoSparepart.stok -= jumlahBaru;

        // Update relasi
        RLama->sparepart = SPBaru;
        RLama->jumlah = jumlahBaru;

        cout << "Relasi berhasil diedit: " << IDSparepartLama << " -> " << IDSparepartBaru << "\n";
    }
}
