#ifndef TUBES_H
#define TUBES_H

#include <iostream>
using namespace std;

// ADT Parent: Mekanik
struct elmMekanik {
    string IDMekanik;
    string namaMekanik;
    int jamKerja;
};

// ADT Child: Servis
struct elmServis {
    string IDServis;
    string namaKendaraan;
    int biayaServis;
};

// Deklarasi forward
struct nodeMekanik;
struct nodeServis;
struct nodeRelasi;

typedef nodeMekanik* adrMekanik;
typedef nodeServis* adrServis;
typedef nodeRelasi* adrRelasi;

// Node Parent: Mekanik
struct nodeMekanik {
    elmMekanik infoMekanik;
    adrMekanik nextMekanik;
    adrRelasi firstRelasi; // pointer ke relasi dengan servis
};

// Node Child: Servis
struct nodeServis {
    elmServis infoServis;
    adrServis nextServis;
};

// Node Relasi antara Mekanik (Parent) dan Servis (Child)
struct nodeRelasi {
    adrServis servis; // pointer ke servis
    adrRelasi nextRelasi;
};

// Struktur List
struct listMekanik {
    adrMekanik firstMekanik;
};

struct listServis {
    adrServis firstServis;
};

// ================= FUNGSI UTAMA SESUAI SPESIFIKASI =================

// a. Insert element parent (Mekanik)
void insertMekanik(listMekanik &LM, elmMekanik data);

// b. Insert element child (Servis)
void insertServis(listServis &LS, elmServis data);

// c. Insert element relation (Mekanik-Servis)
void insertRelationMekanikServis(listMekanik &LM, listServis &LS, string IDMekanik, string IDServis);

// d. Delete element parent (Mekanik)
void deleteMekanik(listMekanik &LM, string IDMekanik);

// e. Delete element child (Servis)
void deleteServis(listServis &LS, string IDServis);

// f. Delete element relation (Mekanik-Servis)
void deleteRelationMekanikServis(adrMekanik mekanik, string IDServis);

// g. Find element Parent (Mekanik)
adrMekanik findMekanik(listMekanik LM, string IDMekanik);

// h. Find element child (Servis)
adrServis findServis(listServis LS, string IDServis);

// i. Find element relation (Mekanik-Servis)
bool findRelationMekanikServis(adrMekanik mekanik, string IDServis);

// j. Show all data di List Parent (Mekanik)
void showAllMekanik(listMekanik LM);

// k. Show all data di List Child (Servis)
void showAllServis(listServis LS);

// l. Show data child dari parent tertentu (Servis dari Mekanik)
void showServisFromMekanik(adrMekanik mekanik);

// m. Show setiap data parent beserta data child yang berelasi dengannya
void showAllMekanikWithServis(listMekanik LM);

// n. Show data child beserta data parent yang masing-masing child miliki
void showAllServisWithMekanik(listMekanik LM, listServis LS);

// o. Show data parent yang berelasi dengan child tertentu
void showMekanikFromServis(listMekanik LM, string IDServis);

// p. Count relation dari setiap element parent
int countRelationMekanikServis(adrMekanik mekanik);

// q. Count relation yang dimiliki oleh child tertentu
int countRelationFromServis(listMekanik LM, string IDServis);

// r. Count element child yang tidak memiliki relasi
int countServisWithoutRelation(listMekanik LM, listServis LS);

// s. Edit relasi / mengganti child dari parent tertentu
void editRelationMekanikServis(adrMekanik mekanik, string IDServisLama, string IDServisBaru, listServis LS);

// Fungsi tambahan untuk inisialisasi
void createListMekanik(listMekanik &LM);
void createListServis(listServis &LS);

#endif
