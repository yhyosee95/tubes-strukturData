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

/* ================= FUNGSI UTAMA ================= */

// a. Insert element parent (Mekanik)
void insertMekanik(listMekanik &LM, elmMekanik data) {
    adrMekanik M = new nodeMekanik;
    M->infoMekanik = data;
    M->nextMekanik = NULL;
    M->firstRelasi = NULL;

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
    adrRelasi R = new nodeRelasi;
    R->servis = S;
    R->nextRelasi = NULL;

    // Tambahkan relasi ke list relasi mekanik
    if (M->firstRelasi == NULL) {
        M->firstRelasi = R;
    } else {
        adrRelasi curr = M->firstRelasi;
        while (curr->nextRelasi != NULL) {
            curr = curr->nextRelasi;
        }
        curr->nextRelasi = R;
    }

    cout << "Relasi antara mekanik " << IDMekanik << " dan servis " << IDServis << " berhasil dibuat.\n";
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
    adrRelasi R = M->firstRelasi;
    while (R != NULL) {
        adrRelasi temp = R;
        R = R->nextRelasi;
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

    // Hapus servis dari list
    if (prev == NULL) {
        LS.firstServis = S->nextServis;
    } else {
        prev->nextServis = S->nextServis;
    }

    delete S;
    cout << "Servis dengan ID " << IDServis << " berhasil dihapus.\n";
    cout << "Catatan: Relasi yang menggunakan servis ini masih perlu dihapus manual dari masing-masing mekanik.\n";
}

// f. Delete element relation (Mekanik-Servis)
void deleteRelationMekanikServis(adrMekanik mekanik, string IDServis) {
    if (mekanik == NULL) {
        cout << "Mekanik tidak valid.\n";
        return;
    }

    if (mekanik->firstRelasi == NULL) {
        cout << "Mekanik tidak memiliki relasi servis.\n";
        return;
    }

    adrRelasi R = mekanik->firstRelasi;
    adrRelasi prev = NULL;

    // Cari relasi yang akan dihapus
    while (R != NULL && R->servis->infoServis.IDServis != IDServis) {
        prev = R;
        R = R->nextRelasi;
    }

    if (R == NULL) {
        cout << "Relasi dengan servis " << IDServis << " tidak ditemukan pada mekanik ini.\n";
        return;
    }

    // Hapus relasi
    if (prev == NULL) {
        mekanik->firstRelasi = R->nextRelasi;
    } else {
        prev->nextRelasi = R->nextRelasi;
    }

    delete R;
    cout << "Relasi dengan servis " << IDServis << " berhasil dihapus dari mekanik.\n";
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

// i. Find element relation (Mekanik-Servis)
bool findRelationMekanikServis(adrMekanik mekanik, string IDServis) {
    if (mekanik == NULL) return false;

    adrRelasi R = mekanik->firstRelasi;
    while (R != NULL) {
        if (R->servis->infoServis.IDServis == IDServis) {
            return true;
        }
        R = R->nextRelasi;
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

// l. Show data child dari parent tertentu (Servis dari Mekanik)
void showServisFromMekanik(adrMekanik mekanik) {
    if (mekanik == NULL) {
        cout << "Mekanik tidak valid.\n";
        return;
    }

    cout << "\n=== SERVIS YANG DITANGANI OLEH: " << mekanik->infoMekanik.namaMekanik << " ===\n";
    if (mekanik->firstRelasi == NULL) {
        cout << "Mekanik ini tidak menangani servis apapun.\n";
        return;
    }

    adrRelasi R = mekanik->firstRelasi;
    int no = 1;
    while (R != NULL) {
        cout << no << ". ID: " << R->servis->infoServis.IDServis
             << " | Kendaraan: " << R->servis->infoServis.namaKendaraan
             << " | Biaya: Rp " << R->servis->infoServis.biayaServis << "\n";
        R = R->nextRelasi;
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

        if (M->firstRelasi == NULL) {
            cout << "  - Tidak menangani servis\n";
        } else {
            adrRelasi R = M->firstRelasi;
            while (R != NULL) {
                cout << "  - " << R->servis->infoServis.namaKendaraan
                     << " (ID: " << R->servis->infoServis.IDServis << ")\n";
                R = R->nextRelasi;
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
            adrRelasi R = M->firstRelasi;
            while (R != NULL) {
                if (R->servis->infoServis.IDServis == S->infoServis.IDServis) {
                    cout << "  - Ditangani oleh: " << M->infoMekanik.namaMekanik
                         << " (ID: " << M->infoMekanik.IDMekanik << ")\n";
                    ditangani = true;
                    break;
                }
                R = R->nextRelasi;
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
        adrRelasi R = M->firstRelasi;
        while (R != NULL) {
            if (R->servis->infoServis.IDServis == IDServis) {
                cout << "  - " << M->infoMekanik.namaMekanik
                     << " (ID: " << M->infoMekanik.IDMekanik
                     << ", Jam Kerja: " << M->infoMekanik.jamKerja << " jam)\n";
                ditemukan = true;
                break;
            }
            R = R->nextRelasi;
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
    adrRelasi R = mekanik->firstRelasi;
    while (R != NULL) {
        count++;
        R = R->nextRelasi;
    }
    return count;
}

// q. Count relation yang dimiliki oleh child tertentu
int countRelationFromServis(listMekanik LM, string IDServis) {
    int count = 0;

    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        adrRelasi R = M->firstRelasi;
        while (R != NULL) {
            if (R->servis->infoServis.IDServis == IDServis) {
                count++;
                break; // break karena sudah ditemukan di mekanik ini
            }
            R = R->nextRelasi;
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
    adrRelasi R = new nodeRelasi;
    R->servis = SBaru;
    R->nextRelasi = NULL;

    if (mekanik->firstRelasi == NULL) {
        mekanik->firstRelasi = R;
    } else {
        adrRelasi curr = mekanik->firstRelasi;
        while (curr->nextRelasi != NULL) {
            curr = curr->nextRelasi;
        }
        curr->nextRelasi = R;
    }

    cout << "Relasi berhasil diedit: " << IDServisLama << " -> " << IDServisBaru << "\n";
}
