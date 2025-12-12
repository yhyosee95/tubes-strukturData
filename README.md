# 🚗 Manajemen Bengkel - Multi Linked List (Struktur Data C++)

Project ini merupakan implementasi **Tugas Besar Struktur Data** menggunakan konsep **Multi Linked List** dengan 3 jenis list utama:

1. **List Mekanik** (Parent)
2. **List Servis** (Child)
3. **List Sparepart** (Child Tambahan)
4. **List Relasi** (Penghubung Mekanik → Servis)

Project dibuat menggunakan bahasa C++ dan telah diatur dalam file terpisah:

* `main.cpp`
* `tubes.cpp`
* `tubes.h`

---

## 📌 **Deskripsi Program**

Program ini mensimulasikan manajemen bengkel sederhana.
Fitur-fitur program meliputi:

### **Mekanik (Parent List)**

* Tambah mekanik
* Hapus mekanik
* Tampilkan semua mekanik
* Melihat servis apa saja yang ditangani mekanik

### **Servis (Child List)**

* Tambah servis
* Hapus servis
* Tampilkan semua servis
* Menampilkan mekanik yang menangani servis tertentu

### **Sparepart (Child Tambahan)**

* Tambah sparepart
* Hapus sparepart
* Tampilkan semua sparepart

### **Relasi Mekanik ↔ Servis**

* Hubungkan mekanik dengan servis
* Hapus relasi tertentu
* Tampilkan semua relasi

Program menggunakan **multilinked list**, di mana:

* Mekanik bisa punya banyak servis (One-to-Many)
* Servis dapat dimiliki oleh lebih dari satu mekanik
* Sparepart berdiri sebagai list terpisah (tidak masuk relasi)

---

## 🛠 **Cara Compile & Run**

Pastikan menggunakan terminal di folder project.

### **Compile:**

```
g++ main.cpp tubes.cpp -o program
```

### **Jalankan:**

```
./program
```

---

## 🗂️ **Struktur File**

```
📦 TuBes
├── main.cpp
├── tubes.cpp
├── tubes.h
├── README.md
```

---

## 🧱 **Struktur Data (Diagram Relasi)**

### **1. Parent List → Mekanik**

Setiap mekanik:

```
[Mekanik]
  ├─ ID
  ├─ Nama
  ├─ Jam Kerja
  └─ firstRelasi → menuju list relasi
```

### **2. Child List → Servis**

```
[Servis]
  ├─ ID Servis
  ├─ Nama Kendaraan
  └─ Biaya Servis
```

### **3. Relasi Mekanik → Servis**

```
[Mekanik] → [Relasi] → [Servis]
```

Multilinked list artinya satu Mekanik memiliki banyak node Relasi.

### **4. Child Tambahan → Sparepart**

List terpisah, tidak terhubung dengan mekanik atau servis.

---

## 📋 **Fitur Program (Menu)**

Program memiliki menu utama dengan 14 pilihan, yaitu:

1. Tambah Mekanik
2. Tambah Servis
3. Tambah Sparepart
4. Hubungkan Mekanik dan Servis
5. Tampilkan Semua Mekanik
6. Tampilkan Semua Servis
7. Tampilkan Semua Sparepart
8. Tampilkan Semua Relasi
9. Tampilkan Servis dari Mekanik tertentu
10. Tampilkan Mekanik dari Servis tertentu
11. Hapus Mekanik
12. Hapus Servis
13. Hapus Sparepart
14. Hapus Relasi
15. Keluar Program

---

## 🧪 **Contoh Input Output Singkat**

### Tambah Mekanik:

```
ID Mekanik: M01
Nama Mekanik: Andi
Jam Kerja: 8
```

### Tambah Servis:

```
ID Servis: S01
Nama Kendaraan: Supra GTR
Biaya Servis: 150000
```

### Relasi:

```
ID Mekanik: M01
ID Servis: S01
Relasi berhasil dibuat.
```

---

## 🎯 **Tujuan Akademik**

Project ini bertujuan untuk memahami:

* Konsep multilinked list
* Pointer antar struktur data
* Implementasi linked list manual (tanpa STL)
* Manajemen memori dynamic (new/delete)
* Pemisahan header & source file

---

## 👨‍💻 **Kontributor**

* Yosevin Hendraji (Telkom University — Teknologi Informasi)
* Naila (Telkom University - Teknlogi Informasi)
* Fauzan (Telkom University - Teknologi Informasi)
* Project dikerjakan sebagai Tugas Besar Struktur Data 2025.

---

## 📄 **Lisensi**

Project ini bebas dipelajari & dimodifikasi untuk tujuan akademik.

---

Jika README ini ingin lu tambahin gambar, contoh output, atau flowchart, tinggal bilang aja ngab 🙌🔥
