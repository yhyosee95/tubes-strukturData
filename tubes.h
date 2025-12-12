#ifndef TUBES_H
#define TUBES_H

#include <iostream>
using namespace std;

// ADT Parent, disini kami menggunakan Mekanik sebagai parent
struct elmMekanik {
    string IDMekanik;
    string namaMekanik;
    int jamKerja;
};

//Untuk childnya, kami menggunakan Servis sebagai child
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

//Node parent yaitu Mekanik
struct nodeMekanik {
    elmMekanik infoMekanik;
    adrMekanik nextMekanik;
    adrRelasi firstRelasi; // pointer ke relasi
};

//Node child yaitu Servis
struct nodeServis {
    elmServis infoServis;
    adrServis nextServis; //ini adalah pointer ke servis selanjutnya
};

//List child tambahan yaitu sparepart
struct elmSparepart {
    string IDSparepart;
    string namaSparepart;
    int harga;
};

//node child yang satunya yaitu sparepart
struct nodeSparepart {
    elmSparepart info;
    nodeSparepart* next;
};

//Node relasi yang menghubungkan Mekanik dan Servis
struct nodeRelasi {
    adrServis servis; // pointer ke servis
    adrRelasi nextRelasi; // pointer ke relasi selanjutnya
};

//List struktur
struct listMekanik {
    adrMekanik firstMekanik;
};

struct listServis {
    adrServis firstServis;
};

struct listSparepart {
    nodeSparepart* first;
};

//Fungsi-fungsi
//Disini kai menggunakan singkatan agar tidak memakan waktu dan tempat 
//LM = List Mekanik 
//LS = List Servis

//ini fungsi untuk membuat list mekanik dan servis
void createListMekanik(listMekanik &LM);
void createListServis(listServis &LS);

//fungsi untuk membuat elemen mekanik, servis, dan relasi
adrMekanik createElmMekanik(elmMekanik dataMekanik);
adrServis createElmServis(elmServis dataServis);
adrRelasi createElmRelasi(adrServis servis);

//fungsi untuk menemukan data data
adrMekanik findMekanik(listMekanik LM, string IDMekanik);
adrServis findServis(listServis LS, string IDServis);

//fungsi untuk menampilkan data
void showAllMekanik(listMekanik LM);
void showAllServis(listServis LS);
void showAllRelasi(listMekanik LM);

void showServisDariMekanik(adrMekanik mekanik);
void showMekanikdariServis(listMekanik LM, string IDServis);

//fungsi delete
void deleteMekanik(listMekanik &LM, string IDMekanik);
void deleteServis(listServis &LS, string IDServis);
void deleteRelasi(adrMekanik &M, string IDServis);

//kami menambahkan fungsi baru untuk sparepart
void createListSparepart(listSparepart &LP);
nodeSparepart* createElmSparepart(elmSparepart data);
void insertSparepart(listSparepart &LP, nodeSparepart* S);
void showAllSparepart(listSparepart LP);
nodeSparepart* findSparepart(listSparepart LP, string ID);
void deleteSparepart(listSparepart &LP, string ID);

//fungsi insert
void insertMekanik(listMekanik &LM, adrMekanik M);
void insertServis(listServis &LS, adrServis S);
void insertRelasi(adrMekanik mekanik, adrServis servis);


#endif