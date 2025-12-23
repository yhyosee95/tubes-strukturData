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

// ADT Child 2: Sparepart
struct elmSparepart {
    string IDSparepart;
    string namaSparepart;
    int harga;
    int stok;
};

// Deklarasi forward
struct nodeMekanik;
struct nodeServis;
struct nodeSparepart;
struct nodeRelasiMekanikServis;
struct nodeRelasiServisSparepart;

typedef nodeMekanik* adrMekanik;
typedef nodeServis* adrServis;
typedef nodeSparepart* adrSparepart;
typedef nodeRelasiMekanikServis* adrRelasiMekanikServis;
typedef nodeRelasiServisSparepart* adrRelasiServisSparepart;

// Node Parent: Mekanik
struct nodeMekanik {
    elmMekanik infoMekanik;
    adrMekanik nextMekanik;
    adrRelasiMekanikServis firstRelasiMekanikServis; // pointer ke relasi dengan servis
};

// Node Child 1: Servis
struct nodeServis {
    elmServis infoServis;
    adrServis nextServis;
    adrRelasiServisSparepart firstRelasiServisSparepart; // pointer ke relasi dengan sparepart
};

// Node Child 2: Sparepart
struct nodeSparepart {
    elmSparepart infoSparepart;
    adrSparepart nextSparepart;
};

// Node Relasi 1: antara Mekanik (Parent) dan Servis (Child 1)
struct nodeRelasiMekanikServis {
    adrServis servis; // pointer ke servis
    adrRelasiMekanikServis nextRelasiMekanikServis;
};

// Node Relasi 2: antara Servis (Child 1) dan Sparepart (Child 2)
struct nodeRelasiServisSparepart {
    adrSparepart sparepart; // pointer ke sparepart
    int jumlah; // jumlah sparepart yang digunakan
    adrRelasiServisSparepart nextRelasiServisSparepart;
};

// Struktur List
struct listMekanik {
    adrMekanik firstMekanik;
};

struct listServis {
    adrServis firstServis;
};

struct listSparepart {
    adrSparepart firstSparepart;
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

// ================= FUNGSI TAMBAHAN UNTUK SPAREPART =================

// b2. Insert element child 2 (Sparepart)
void insertSparepart(listSparepart &LSP, elmSparepart data);

// c2. Insert element relation (Servis-Sparepart)
void insertRelationServisSparepart(listServis &LS, listSparepart &LSP, string IDServis, string IDSparepart, int jumlah);

// e2. Delete element child 2 (Sparepart)
void deleteSparepart(listSparepart &LSP, string IDSparepart);

// f2. Delete element relation (Servis-Sparepart)
void deleteRelationServisSparepart(adrServis servis, string IDSparepart);

// h2. Find element child 2 (Sparepart)
adrSparepart findSparepart(listSparepart LSP, string IDSparepart);

// i2. Find element relation (Servis-Sparepart)
bool findRelationServisSparepart(adrServis servis, string IDSparepart);

// k2. Show all data di List Child 2 (Sparepart)
void showAllSparepart(listSparepart LSP);

// l2. Show data child 2 dari child 1 tertentu (Sparepart dari Servis)
void showSparepartFromServis(adrServis servis);

// m2. Show setiap data child 1 beserta data child 2 yang berelasi
void showAllServisWithSparepart(listServis LS);

// n2. Show data child 2 beserta data child 1 yang masing-masing child 2 miliki
void showAllSparepartWithServis(listServis LS, listSparepart LSP);

// o2. Show data child 1 yang berelasi dengan child 2 tertentu
void showServisFromSparepart(listServis LS, string IDSparepart);

// p2. Count relation dari setiap element child 1
int countRelationServisSparepart(adrServis servis);

// q2. Count relation yang dimiliki oleh child 2 tertentu
int countRelationFromSparepart(listServis LS, string IDSparepart);

// r2. Count element child 2 yang tidak memiliki relasi
int countSparepartWithoutRelation(listServis LS, listSparepart LSP);

// s2. Edit relasi / mengganti child 2 dari child 1 tertentu
void editRelationServisSparepart(adrServis servis, string IDSparepartLama, string IDSparepartBaru, listSparepart LSP, int jumlahBaru);

// Fungsi tambahan untuk inisialisasi
void createListMekanik(listMekanik &LM);
void createListServis(listServis &LS);
void createListSparepart(listSparepart &LSP);

#endif
