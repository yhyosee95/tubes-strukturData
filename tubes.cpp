#include "tubes.h"
using namespace std;

/* ================= CREATE LIST ================= */
void createListMekanik(listMekanik &LM) {
    LM.firstMekanik = NULL;
}

void createListServis(listServis &LS) {
    LS.firstServis = NULL;
}

void createListSparepart(listSparepart &LP) {
    LP.first = NULL;
}

/* ================= CREATE ELEM ================= */
adrMekanik createElmMekanik(elmMekanik dataMekanik) {
    adrMekanik M = new nodeMekanik;
    M->infoMekanik = dataMekanik;
    M->nextMekanik = NULL;
    M->firstRelasi = NULL;
    return M;
}

adrServis createElmServis(elmServis dataServis) {
    adrServis S = new nodeServis;
    S->infoServis = dataServis;
    S->nextServis = NULL;
    S->firstSparepart = NULL;
    return S;
}

nodeSparepart* createElmSparepart(elmSparepart data) {
    nodeSparepart* P = new nodeSparepart;
    P->info = data;
    P->next = NULL;
    return P;
}

adrRelasi createElmRelasi(adrServis servis) {
    adrRelasi R = new nodeRelasi;
    R->servis = servis;
    R->nextRelasi = NULL;
    return R;
}

/* ================= INSERT ================= */
void insertMekanik(listMekanik &LM, adrMekanik M) {
    M->nextMekanik = LM.firstMekanik;
    LM.firstMekanik = M;
}

void insertServis(listServis &LS, adrServis S) {
    S->nextServis = LS.firstServis;
    LS.firstServis = S;
}

void insertSparepart(listSparepart &LP, nodeSparepart* S) {
    S->next = LP.first;
    LP.first = S;
}

void insertRelasi(adrMekanik mekanik, adrServis servis) {
    adrRelasi R = createElmRelasi(servis);
    R->nextRelasi = mekanik->firstRelasi;
    mekanik->firstRelasi = R;
}

/* ================= FIND ================= */
adrMekanik findMekanik(listMekanik LM, string IDMekanik) {
    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        if (M->infoMekanik.IDMekanik == IDMekanik)
            return M;
        M = M->nextMekanik;
    }
    return NULL;
}

adrServis findServis(listServis LS, string IDServis) {
    adrServis S = LS.firstServis;
    while (S != NULL) {
        if (S->infoServis.IDServis == IDServis)
            return S;
        S = S->nextServis;
    }
    return NULL;
}

nodeSparepart* findSparepart(listSparepart LP, string ID) {
    nodeSparepart* P = LP.first;
    while (P != NULL) {
        if (P->info.IDSparepart == ID)
            return P;
        P = P->next;
    }
    return NULL;
}

/* ================= SHOW ================= */
void showAllMekanik(listMekanik LM) {
    adrMekanik M = LM.firstMekanik;
    cout << "=== DATA MEKANIK ===\n";
    while (M != NULL) {
        cout << M->infoMekanik.IDMekanik << " | "
             << M->infoMekanik.namaMekanik << " | "
             << M->infoMekanik.jamKerja << endl;
        M = M->nextMekanik;
    }
}

void showAllServis(listServis LS) {
    adrServis S = LS.firstServis;
    cout << "=== DATA SERVIS ===\n";
    while (S != NULL) {
        cout << S->infoServis.IDServis << " | "
             << S->infoServis.namaKendaraan << " | "
             << S->infoServis.biayaServis << endl;
        S = S->nextServis;
    }
}

void showAllSparepart(listSparepart LP) {
    nodeSparepart* P = LP.first;
    cout << "=== DATA SPAREPART ===\n";
    while (P != NULL) {
        cout << P->info.IDSparepart << " | "
             << P->info.namaSparepart << " | "
             << P->info.harga << endl;
        P = P->next;
    }
}

void showAllRelasi(listMekanik LM) {
    adrMekanik M = LM.firstMekanik;
    cout << "=== RELASI MEKANIK - SERVIS ===\n";
    while (M != NULL) {
        cout << "Mekanik: " << M->infoMekanik.namaMekanik << endl;
        adrRelasi R = M->firstRelasi;
        while (R != NULL) {
            cout << "  Servis: " << R->servis->infoServis.namaKendaraan << endl;
            R = R->nextRelasi;
        }
        M = M->nextMekanik;
    }
}

void showServisDariMekanik(adrMekanik mekanik) {
    adrRelasi R = mekanik->firstRelasi;
    while (R != NULL) {
        cout << R->servis->infoServis.namaKendaraan << endl;
        R = R->nextRelasi;
    }
}

void showMekanikdariServis(listMekanik LM, string IDServis) {
    adrMekanik M = LM.firstMekanik;
    while (M != NULL) {
        adrRelasi R = M->firstRelasi;
        while (R != NULL) {
            if (R->servis->infoServis.IDServis == IDServis)
                cout << M->infoMekanik.namaMekanik << endl;
            R = R->nextRelasi;
        }
        M = M->nextMekanik;
    }
}

/* ================= DELETE ================= */
void deleteRelasi(adrMekanik &M, string IDServis) {
    adrRelasi R = M->firstRelasi;
    adrRelasi prev = NULL;

    while (R != NULL) {
        if (R->servis->infoServis.IDServis == IDServis) {
            if (prev == NULL)
                M->firstRelasi = R->nextRelasi;
            else
                prev->nextRelasi = R->nextRelasi;
            delete R;
            return;
        }
        prev = R;
        R = R->nextRelasi;
    }
}

void deleteMekanik(listMekanik &LM, string IDMekanik) {
    adrMekanik M = LM.firstMekanik;
    adrMekanik prev = NULL;

    while (M != NULL) {
        if (M->infoMekanik.IDMekanik == IDMekanik) {
            if (prev == NULL)
                LM.firstMekanik = M->nextMekanik;
            else
                prev->nextMekanik = M->nextMekanik;
            delete M;
            return;
        }
        prev = M;
        M = M->nextMekanik;
    }
}

void deleteServis(listServis &LS, string IDServis) {
    adrServis S = LS.firstServis;
    adrServis prev = NULL;

    while (S != NULL) {
        if (S->infoServis.IDServis == IDServis) {
            if (prev == NULL)
                LS.firstServis = S->nextServis;
            else
                prev->nextServis = S->nextServis;
            delete S;
            return;
        }
        prev = S;
        S = S->nextServis;
    }
}

void deleteSparepart(listSparepart &LP, string ID) {
    nodeSparepart* P = LP.first;
    nodeSparepart* prev = NULL;

    while (P != NULL) {
        if (P->info.IDSparepart == ID) {
            if (prev == NULL)
                LP.first = P->next;
            else
                prev->next = P->next;
            delete P;
            return;
        }
        prev = P;
        P = P->next;
    }
}
