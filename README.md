# 3D Human Model using OpenGL (FreeGLUT + C++)

Proyek ini merupakan simulasi pemodelan manusia 3D menggunakan **C++ dan OpenGL (FreeGLUT)**, yang memuat model `.nfg` dan tekstur `.tga`, ditampilkan secara realistis dengan rotasi otomatis.

## 🎯 Tujuan Proyek

Mendemonstrasikan kemampuan dasar dalam:
- Menampilkan objek 3D berbasis data file eksternal (`.nfg` dan `.tga`)
- Mengimplementasikan tekstur kulit manusia
- Menambahkan rotasi otomatis untuk efek visualisasi dinamis
- Menggunakan pipeline grafis modern berbasis **OpenGL**

## 🛠️ Teknologi yang Digunakan

- C++
- OpenGL (FreeGLUT)
- TGA Texture Loader
- Code::Blocks (MinGW)
- Git & GitHub

## 📦 Struktur File

├── assets/
│ ├── Woman1.tga # Tekstur kulit model
│ └── Woman1.nfg # File model 3D
├── TGA.h # Header untuk loader file .tga
├── main.cpp # Main rendering dan logika rotasi
└── README.md

bash
Salin
Edit

## 🚀 Cara Menjalankan

1. Clone repository:
   ```bash
   git clone https://github.com/SuryoFebri/3D-Human-Model-OpenGL.git
