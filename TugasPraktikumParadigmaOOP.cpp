#include <iostream>
#include <vector>
#include <string>

// Abstract Base Class
class RekeningBank {
protected:
    std::string nomorRekening;
    std::string namaNasabah;
    double saldo;

public:
    RekeningBank(std::string noRek, std::string nama, double saldoAwal)
        : nomorRekening(noRek), namaNasabah(nama), saldo(saldoAwal) {}

    virtual ~RekeningBank() {} // Virtual destructor untuk mencegah memory leak

    // Pure Virtual Function
    virtual void potongAdmin() = 0;

    // Getter untuk menampilkan informasi
    void tampilkanInformasi() const {
        std::cout << "Nasabah: " << namaNasabah 
                  << " | No. Rek: " << nomorRekening 
                  << " | Saldo Akhir: Rp " << saldo << "\n";
    }
};

// Derived Class 1: Rekening Syariah (Bebas Biaya Admin)
class RekeningSyariah : public RekeningBank {
public:
    RekeningSyariah(std::string noRek, std::string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    void potongAdmin() override {
        // Prinsip Syariah: Saldo tetap utuh, tidak ada potongan
        std::cout << "[Syariah] " << namaNasabah << ": Bebas biaya admin. \n";
    }
};

// Derived Class 2: Rekening Konvensional (Potongan Flat Rp 15.000)
class RekeningKonvensional : public RekeningBank {
public:
    RekeningKonvensional(std::string noRek, std::string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    void potongAdmin() override {
        saldo -= 15000;
        std::cout << "[Konvensional] " << namaNasabah << ": Dipotong Rp 15.000. \n";
    }
};

// Derived Class 3: Rekening Premium (Potongan Dinamis)
class RekeningPremium : public RekeningBank {
public:
    RekeningPremium(std::string noRek, std::string nama, double saldoAwal)
        : RekeningBank(noRek, nama, saldoAwal) {}

    void potongAdmin() override {
        if (saldo > 10000000) {
            // Saldo di atas 10 Juta -> Bebas Biaya Admin
            std::cout << "[Premium] " << namaNasabah << ": Saldo > 10jt, Bebas biaya admin!\n";
        } else {
            // Saldo <= 10 Juta -> Potong Rp 50.000
            saldo -= 50000;
            std::cout << "[Premium] " << namaNasabah << ": Saldo <= 10jt, Dipotong Rp 50.000.\n";
        }
    }
};

// Driver Program (Simulasi Server Bank di Akhir Bulan)
int main() {
    // Menampung berbagai jenis rekening menggunakan pointer dari Base Class (RekeningBank)
    std::vector<RekeningBank*> daftarRekening;

    // Registrasi nasabah baru ke dalam sistem
    daftarRekening.push_back(new RekeningSyariah("SYR-001", "Ahmad Fauzi", 5000000));
    daftarRekening.push_back(new RekeningKonvensional("KONV-002", "Budi Santoso", 2000000));
    
    // Anggota baru: Rekening Premium dengan kondisi saldo berbeda
    daftarRekening.push_back(new RekeningPremium("PREM-003", "Citra Lestari", 15000000)); // Saldo > 10jt
    daftarRekening.push_back(new RekeningPremium("PREM-004", "Dedi Wijaya", 8000000));     // Saldo <= 10jt

    std::cout << "=== PROSES OTOMATISASI POTONGAN ADMIN AKHIR BULAN ===\n\n";
    
    // Server memproses semua rekening secara fleksibel menggunakan perulangan tunggal
    for (RekeningBank* rekening : daftarRekening) {
        rekening->potongAdmin();
    }

    std::cout << "\n=== STATUS SALDO AKHIR NASABAH ===\n\n";
    for (const RekeningBank* rekening : daftarRekening) {
        rekening->tampilkanInformasi();
    }

    // Cleanup memori untuk menghindari memory leak
    for (RekeningBank* rekening : daftarRekening) {
        delete rekening;
    }
    daftarRekening.clear();

    return 0;
}