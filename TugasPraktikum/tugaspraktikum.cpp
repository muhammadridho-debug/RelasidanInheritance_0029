#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =======================
// BASE CLASS: User
// =======================
class User {
protected:
    static int globalId; // Member variable globalId (static)
    int id;              // Member variable id
    string nama;         // Member variable nama
    string email;        // Member variable email

public:
    // Constructor
    User(string n, string e) : nama(n), email(e) {
        generateId();
    }

    // Member function untuk generateId
    void generateId() {
        globalId++;
        id = globalId;
    }

    // Getter untuk memudahkan akses dari luar (misal: saat Admin melihat data Member)
    int getId() const { return id; }
    string getNama() const { return nama; }
    string getEmail() const { return email; }
};

// Inisialisasi static variable di luar class
int User::globalId = 0;


// =======================
// DERIVED CLASS: Member
// =======================
class Member : public User {
private:
    bool status; // Status keanggotaan (true = Aktif, false = Non-aktif)
                 // Note: id, nama, dan email otomatis diwarisi dari class User

public:
    // Constructor untuk Member
    Member(string n, string e) : User(n, e), status(true) {}

    // Member function untuk menampilkan profil
    void showProfile() const {
        cout << "\n--- Profil Member ---" << endl;
        cout << "ID     : " << id << endl;
        cout << "Nama   : " << nama << endl;
        cout << "Email  : " << email << endl;
        cout << "Status : " << (status ? "Aktif" : "Non-Aktif") << endl;
    }

    // Fungsi tambahan untuk mengubah dan mengambil status
    void setStatus(bool s) { status = s; }
    bool getStatus() const { return status; }
};


// =======================
// DERIVED CLASS: Admin
// =======================
class Admin : public User {
public:
    // Constructor untuk Admin
    Admin(string n, string e) : User(n, e) {}

    // Member function untuk menampilkan semua member
    void showAllMember(const vector<Member>& members) const {
        cout << "\n=== Daftar Semua Member ===" << endl;
        if (members.empty()) {
            cout << "Belum ada member yang terdaftar." << endl;
            return;
        }
        for (const auto& member : members) {
            cout << "ID: " << member.getId() 
                 << " | Nama: " << member.getNama() 
                 << " | Email: " << member.getEmail()
                 << " | Status: " << (member.getStatus() ? "Aktif" : "Non-Aktif") << endl;
        }
    }

    // Member function untuk mengaktifkan/menonaktifkan member
    void toggleActivationMember(Member& member) {
        // Membalik status saat ini (true jadi false, false jadi true)
        member.setStatus(!member.getStatus());
        cout << "\n[INFO] Status member '" << member.getNama() 
             << "' berhasil diubah menjadi: " 
             << (member.getStatus() ? "Aktif" : "Non-Aktif") << endl;
    }
};


int main() {
    // 1. Membuat akun Admin
    Admin admin1("Budi Santoso", "admin.budi@sistem.com");

    // 2. Membuat beberapa akun Member
    vector<Member> daftarMember;
    daftarMember.push_back(Member("Siti Aminah", "siti@gmail.com"));
    daftarMember.push_back(Member("Andi Wijaya", "andi@yahoo.com"));

    // 3. Member melihat profil masing-masing
    daftarMember[0].showProfile();

    // 4. Admin melihat semua member
    admin1.showAllMember(daftarMember);

    // 5. Admin melakukan toggle status pada Member ke-2 (Andi Wijaya)
    admin1.toggleActivationMember(daftarMember[1]);

    // 6. Admin melihat semua member setelah perubahan
    admin1.showAllMember(daftarMember);

    return 0;
}