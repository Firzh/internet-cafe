#include "nlohmann\json.hpp"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <sstream>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;
using json = nlohmann::json;

void clearScreen() {
    system("cls");
}

bool stopTimer = false;
int sisaDetik = 0;

struct tempAdmin{
    string username;
    string password;
    string confPasword;
};

struct Member {
    int id;
    string username;
    string password;
    double billing;
    string paket;
    string group;
    int memberCredits;
};

struct komputer{
    int idKomputer;
    bool used;
    komputer *next;
};

struct DateTime {
    string jam;
    string hari;
    string tanggal;
};

string passwordMask() {
    string password;
    char ch;

    ch = _getch();  

    while (ch != 13) { 
        if (ch != 8) { 
            password.push_back(ch);
            cout << '*';
        } else if (!password.empty()) { 
            password.pop_back();
            cout << "\b \b"; 
        }
        ch = _getch();
    }
    cout << endl;
    return password;
}

DateTime getDateTime() {
    DateTime result;

    // Mendapatkan waktu saat ini
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Menampilkan jam
    int jam = ltm->tm_hour;
    int min = ltm->tm_min;
    int sec = ltm->tm_sec;
    if (jam > 9) {
        if (sec >9)
            result.jam = to_string(jam) + ":" + to_string(min) + ":" + to_string(sec);
        if (sec < 10)
            result.jam = to_string(jam) + ":" + to_string(min) + ":0" + to_string(sec);
    }
    if (jam < 10) {
        if (sec >9)
            result.jam = to_string(jam) + ":" + to_string(min) + ":" + to_string(sec);
        if (sec < 10)
            result.jam = to_string(jam) + ":" + to_string(min) + ":0" + to_string(sec);
    }

    // Menampilkan hari
    switch (ltm->tm_wday) {
        case 0:
            result.hari = "Minggu, ";
            break;
        case 1:
            result.hari = "Senin, ";
            break;
        case 2:
            result.hari = "Selasa, ";
            break;
        case 3:
            result.hari = "Rabu, ";
            break;
        case 4:
            result.hari = "Kamis, ";
            break;
        case 5:
            result.hari = "Jumat, ";
            break;
        case 6:
            result.hari = "Sabtu, ";
            break;
    }

    // Menampilkan tanggal
    int tanggal = ltm->tm_mday;
    int bulan = 1 + ltm->tm_mon;
    int tahun = 1900 + ltm->tm_year;
    
    if (bulan > 9) {
        result.tanggal = to_string(tanggal) + "-" + to_string(bulan) + "-" + to_string(tahun);
    } else if (bulan < 10) {
        result.tanggal = to_string(tanggal) + "-0" + to_string(bulan) + "-" + to_string(tahun);
    }
    return result;
}

// Fungsi timer hitung mundur
DWORD WINAPI countdownTimer(LPVOID lpParam) {
    int duration = (int)lpParam;                                        // Mengubah parameter dari tipe LPVOID menjadi int, yang merupakan durasi hitung mundur dalam detik
    time_t start_time = time(nullptr);                                  // Mendapatkan waktu saat ini sebagai waktu mulai hitung mundur

    while (true) {                                                      // Memulai loop tak terbatas untuk menghitung mundur
        if (stopTimer) {                                                // Memeriksa apakah variabel global stopTimer telah diatur ke true
            time_t current_time = time(nullptr);                        // Mendapatkan waktu saat ini dari variabel sebelumnya
            int elapsed_time = current_time - start_time;               // Menghitung waktu yang telah berlalu sejak mulai hitung mundur
            sisaDetik = duration - elapsed_time;                        // Menghitung sisa waktu dan menyimpannya dalam variabel global sisaDetik
            break;                                                      // Keluar dari loop jika stopTimer adalah true
        }

        time_t current_time = time(nullptr);                            // Mendapatkan waktu saat ini dari variabel sebelumnya
        int elapsed_time = current_time - start_time;                   // Menghitung waktu yang telah berlalu sejak mulai hitung mundur
        int remaining_time = duration - elapsed_time;                   // Menghitung sisa waktu
        
        string hour = to_string(remaining_time/3600);
        string minutes = to_string(remaining_time/60 % 60);
        string second = to_string(remaining_time % 60);
        string clocks = hour + ":" + minutes + ":" + second;

        if (remaining_time <= 0) {                                      // Memeriksa apakah waktu hitung mundur telah habis
            cout << "\nWaktu habis!" << endl;                           // Menampilkan pesan bahwa waktu telah habis
            break;                                                      // Keluar dari loop jika waktu habis
        }

        // Tampilkan sisa waktu setiap detik
        cout << "\rSisa waktu: " << clocks << " detik " << flush;       // Menampilkan sisa waktu di baris yang sama (menggunakan carriage return)

        Sleep(1000);                                                    // Jeda 1 detik untuk menghindari loop berjalan terlalu cepat
    }

    return 0;                                                           // Mengembalikan 0 untuk menunjukkan bahwa fungsi telah selesai dengan sukses
}

// Fungsi untuk membuka URL atau aplikasi
void openApplication(const char* application) {

    // Mengubah string C-style ke wide string
    wchar_t wtext[256];
    mbstowcs(wtext, application, strlen(application) + 1);
    LPCWSTR lpwstr = wtext;

    ShellExecuteW(0, 0, lpwstr, 0, 0, SW_SHOW);
}

// Fungsi laucher sederhana
void launcher() {
    clearScreen();
    int choice = 0;
    do {
        cout << "Pilih aplikasi untuk dibuka:\n";
        cout << "1. Google\n";
        cout << "2. YouTube\n";
        cout << "3. Notepad\n";
        cout << "4. Kalkulator\n";
        cout << "5. Keluar\n\n";
        cout << "Masukkan pilihan : \n\n\n";
        cin >> choice;

        switch (choice) {
            case 1:
                openApplication("https://www.google.com");
                break;
            case 2:
                openApplication("https://www.youtube.com");
                break;
            case 3:
                openApplication("notepad");
                break;
            case 4:
                openApplication("calc");
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                Sleep(2);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                Sleep(2);
                break;
        }
    } while (choice != 5);
}

// Fungsi konversi jam ke detik
float convertHourToSec(float hour) {
    float sec;
    sec = hour * 60 * 60;
    return sec;
}

// Fungsi untuk membaca file JSON
json bacaFileJson(const string& namaFile) {
    ifstream file(namaFile);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    }
    return data;
}

// Fungsi untuk menyimpan data ke file JSON
void simpanKeJson(const json& data, const string& namaFile) {
    ofstream file(namaFile);
    if (file.is_open()) {
        file << data.dump(4); 
        file.close();
    }
}

bool cekLoginAdmin(const string& uname, const string& pass) {
    json dataAdmin = bacaFileJson("Admin.json");

    for (const auto& opr : dataAdmin) {
        if (opr["username"] == uname && opr["password"] == pass) {
            return true; 
        }
    }
    return false; 
}

bool cekLoginOperator(const string& opname, const string& oppass) {
    json dataOperator = bacaFileJson("Operator.json");

    for (const auto& opr : dataOperator) {
        if (opr["username"] == opname && opr["password"] == oppass) {
            return true; 
        }
    }
    return false; 
}

// Fungsi untuk menambahkan data pemasukan ke file JSON
void tambahDataPemasukan(const string& namaFile, double pemasukan) {
    json data;

    DateTime waktu = getDateTime();
    string date = waktu.hari + waktu.tanggal;

    if (ifstream(namaFile)) {
        data = bacaFileJson(namaFile);
    }

    if (data.empty()) {
        data["Pemasukan"] = json::array();
        data["Total Pemasukan"]["total"] = 0.0;
    }

    json newData = {
        {"tanggal", date}, 
        {"pemasukan", pemasukan} 
    };

    data["Pemasukan"].push_back(newData);

    double totalPemasukan = 0.0;
    for (const auto& entry : data["Pemasukan"]) {
        totalPemasukan += entry["pemasukan"].get<double>(); 
    }
    data["Total Pemasukan"]["total"] = totalPemasukan;

    simpanKeJson(data, namaFile);
}

// Fungsi untuk mendapatkan Total Pemasukan dari file JSON
double getTotalPemasukan() {
    json data = bacaFileJson("Pemasukan.json");
    double totalPemasukan = 0.0;

    // Mengecek apakah objek Total Pemasukan ada di JSON
    if (data.find("Total Pemasukan") != data.end()) {
        totalPemasukan = data["Total Pemasukan"]["total"];
    } else {
        cout << "Objek Total Pemasukan tidak ditemukan dalam file JSON." << endl;
    }

    return totalPemasukan;
}

//format log
// tambahEntri("log/waning/error", usernameAdmin, kegiatan, usernameMember, paket, usernameBaruAdmin, grup);
void tambahEntri(string jenis, string admin, string kegiatan, string member, string paket, string newUname, string grup) {
    json data = bacaFileJson("Log.json");

    DateTime waktu = getDateTime();
    string date = waktu.hari + waktu.tanggal;

    if (data.empty()) {
        data["$date"] = date;
        data["&log"] = json::array();
        data["^warning!"]= json::array();
        data["~error!!"] = json::array();
    }

    if (data["$date"] != date) {
        data["$date"] = date;
        data["&log"] = json::array();
        data["^warning!"] = json::array();
        data["~error!!"] = json::array();
    }
    
    json newEntry = {
        {"$jam", waktu.jam},
        {"%kegiatan", kegiatan}
    };

    if (!admin.empty())
        newEntry["&admin"] = admin;
    if (!member.empty())
        newEntry["*member"] = member;
    if (!paket.empty())
        newEntry["+paket"] = paket;
    if (!newUname.empty())
        newEntry["-newUname"] = newUname;
    if (!grup.empty())
        newEntry["-grup"] = grup;

    if (jenis == "log") 
        data["&log"].push_back(newEntry);
    if (jenis == "warning")
        data["^warning!"].push_back(newEntry);
    if (jenis == "error")
        data["~error!!"].push_back(newEntry);

    simpanKeJson(data, "Log.json");
}

void simpanPrintout(const string& username, const string& password) {
    json data = bacaFileJson("PrintOut.json");

    if (data.empty()) {
        data["printOut"] = json::array();
    }

    json newData = {
        {"Username", username},
        {"Password", password}
    };

    data["printOut"].push_back(newData);

    simpanKeJson(data, "PrintOut.json");
}

string headerDisplayBorder = "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
string headerBorder        = "===============================================================================================\n";
string headerAdmin         = "                                         Menu Admin                                            \n";
string headerLogin         = "                                           Login                                               \n";
string headerOperator      = "                                        Menu Operator                                          \n";
string headerPemasukan     = "                                          Pemasukan                                            \n";
string headerUserPaketan   = "                                        User Paketan                                           \n";
string headerTambahBilling = "                                       Tambah Billing                                          \n";
string headerPengaturanAdm = "                                      Pengaturan Admin                                         \n";
string headerNewMember     = "                                         Member Baru                                           \n";
string headerMembership    = "                                         Membership                                            \n";
string headerMember        = "                                         Menu Member                                           \n";
string headerListMember    = "                                         List Member                                           \n";

void editDataAdmin(json& data, const string& username, const string& kunci, const string& nilaiBaru) {
    for (auto& admin : data) {
        if (admin["username"] == username) {
            if (admin.contains(kunci)) {
                admin[kunci] = nilaiBaru;
                return;
            }
        }
    }
    cout << "Admin dengan username tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus data admin dari JSON
void hapusDataAdmin(json& data, const string& username) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        if ((*it)["username"] == username) {
            data.erase(it);
            return;
        }
    }
    cout << "Admin dengan username tersebut tidak ditemukan.\n";
}

void tambahAdminBaru(const string& username, const string& password, const string& filename) {
    // Membuat objek JSON untuk admin baru
    json adminBaru = {
        {"username", username},
        {"password", password}
    };

    json data = bacaFileJson(filename);
    data.push_back(adminBaru);

    simpanKeJson(data, filename);
}

bool hapusAdmin(const string& username) {
    json dataAdmin = bacaFileJson("Admin.json");
    bool ditemukan = false;
    
    auto it = remove_if(dataAdmin.begin(), dataAdmin.end(), [&username, &ditemukan](const json& admin) {
        if (admin["username"] == username) {
            ditemukan = true;
            return true;
        }
        return false;
    });

    if (ditemukan) {
        dataAdmin.erase(it, dataAdmin.end());
        simpanKeJson(dataAdmin, "Admin.json");
        return true;
    }
    return false;
}

//================================================================================================================
// awal doublelinkedlist
struct Node {
    Member data;
    Node* next;
    Node* prev;
};

class DoubleLinkedlist {
private:
    Node* head;
    Node* tail;
    int size;
    int lastID = 0;

public:
    DoubleLinkedlist() : head(nullptr), tail(nullptr), size(0) {}

    void tambahMember(Member newData) {
        if (size >= 1000) {
            cout << "Member sudah maksimal, perlu maintenance\n";
            return;
        }

        string basePassword = generateUniquePass(newData);

        newData.password = basePassword;
        newData.id = ++lastID;
        lastID = newData.id;
        Node* newNode = new Node;
        newNode->data = newData;

        string name = newData.username;
        string pass = newData.password;
        simpanPrintout(name, pass);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
        size++;
        cout << "Member berhasil ditambah!\n";
        clock_t start_time = clock();
        while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}  
    }

    // Fungsi untuk verifikasi member berdasarkan username dan password
    bool cekLoginUser(string username, string password) {

        // Cek apakah terdapat member dengan melihat head bukan merupakan nullptr
        if (head == nullptr) {
            cout << "Member tidak ada...\n";
            clock_t start_time = clock();
            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}  
            return false;
        }

        // Set current node menjadi head
        Node* current = head;

        //  Melakukan pencarian dan pengecekan username + password yang dimasukkan user
        do {
            if (current->data.username == username && current->data.password == password) {
                cout << "Memverifikasi...\n";
                clock_t start_time = clock();
                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                clearScreen();
                cout << "Selamat datang!\n";
                Sleep(2);
                return true;
            }
            // Melanjutkan ke node selanjutnya jika salah
            current = current->next;

        // Berhenti apabila kembali bertemu node yang di set menjadi head agar tidak terjadi infinite looping
        } while (current != head);

        return false;
    }

    string generateUniquePass(const Member& member) {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int tanggal = ltm->tm_mday;
        int tahun = 1900 + ltm->tm_year;

        string tempPass = to_string(tanggal);
        int angkaHurufAwal = konversiHurufKeAngka(member.username[0]);
        int angkaHurufTiga = konversiHurufKeAngka(member.username[2]);
        int angkaKetiga = angkaHurufAwal + angkaHurufTiga;
        tempPass += to_string(angkaKetiga);
        tempPass += to_string(tahun);    
        return tempPass;
    }

    int konversiHurufKeAngka(char huruf) {
        if (isalpha(huruf)) {
            return toupper(huruf) - 'A' + 1;
        } else {
            return -1;
        }
    }

    const string PI = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549308196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700663155881748815209209628292540919171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912983367336244065664308602139494639522473719070217986094370277053921717629317678765195982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989";

    void fillDigits(string pi_digits[], size_t& size) {
        size = PI.length() / 3;
        for (size_t i = 0; i < size; ++i) {
            pi_digits[i] = PI.substr(i * 3, 3);
        }
    }

    string generateUsername(string pi_digits[], size_t size) {
        string username;
        srand(time(0)); 

        for (int i = 0; i < 2; ++i) { 
            int randomIndex = rand() % size;
            username += pi_digits[randomIndex];
        }

        return username;
    }

    bool isUsernameUnique(const string& username) {
        if (head == nullptr) return true;  

        Node* current = head;
        do {
            if (current->data.username == username) {
                return false; 
            }
            current = current->next;
        } while (current != head);
        return true; 
    }

    Member& cariMember(const string& username, DoubleLinkedlist& list) {
        Node* current = list.head;

        while (current != nullptr) {
            if (current->data.username == username) {
                return current->data;
            }
            current = current->next;
        }

        throw runtime_error("Member tidak ditemukan.");
        clock_t start_time = clock();
        while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {} 
    }

//================================================================================================================
// awal fungsi untuk (Non-member)

    void paketNonMember(Member& newMember) {
        cout << headerBorder << headerUserPaketan << headerBorder << endl;
        newMember.group = "Group Non-member";

        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Paket i3\n";
        cout << "2. Paket i5\n";
        cout << "3. Paket i7\n";
        cout << "4. Custom\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGNM;
        cin >> pilihanGNM;

        switch (pilihanGNM) {
            case 1:
                clearScreen();
                cout << headerBorder << headerUserPaketan << headerBorder << endl;

                cout << "Pilihan Paket:\n";
                cout << "1. Paket pagi\n";
                cout << "2. Paket malam\n";
                cout << "3. Custom\n";
                cout << "Masukkan pilihan paket: ";
                
                int pilihanPGNM1;
                cin >> pilihanPGNM1;

                switch (pilihanPGNM1) {
                    case 1:
                        newMember.paket = "Paket Pagi";
                        newMember.billing = 10000;  
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 2:
                        newMember.paket = "Paket Malam";
                        newMember.billing = 15000;  
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 3:
                        cout << "Masukkan billing : ";
                        cin >> newMember.billing;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
                break;
            case 2:
                clearScreen();
                cout << headerBorder << headerUserPaketan << headerBorder << endl;

                cout << "Pilihan Paket:\n";
                cout << "1. Paket Pagi\n";
                cout << "2. Paket Malam 21\n";
                cout << "3. Paket Malam 12\n";
                cout << "Masukkan pilihan paket: ";
                
                int pilihanPGNM2;
                cin >> pilihanPGNM2;

                switch (pilihanPGNM2) {
                    case 1:
                        newMember.paket = "Paket Pagi";
                        newMember.billing = 20000;  
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 2:
                        newMember.paket = "Paket Malam 21";
                        newMember.billing = 30000; 
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 3:
                        newMember.paket = "Paket Malam 12";
                        newMember.billing = 20000;
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
                break;
            case 3:
                clearScreen();
                cout << headerBorder << headerUserPaketan << headerBorder << endl;

                cout << "Pilihan Paket:\n";
                cout << "1. Paket Pagi\n";
                cout << "2. Paket Malam 21\n";
                cout << "3. Paket Malam 12\n";
                cout << "Masukkan pilihan paket: ";
                
                int pilihanPGNM3;
                cin >> pilihanPGNM3;

                switch (pilihanPGNM3) {
                    case 1:
                        newMember.paket = "Paket Pagi";
                        newMember.billing = 25000;  
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 2:
                        newMember.paket = "Paket Malam 21";
                        newMember.billing = 40000; 
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    case 3:
                        newMember.paket = "Paket Malam 12";
                        newMember.billing = 30000;
                        tambahDataPemasukan("Pemasukan.json", newMember.billing);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
                break;
            case 4:
                clearScreen();
                cout << headerBorder << headerUserPaketan << headerBorder << endl;

                cout << "Masukkan billing : ";
                cin >> newMember.billing;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket Non-member" << newMember.paket << " dipilih dengan biaya " << newMember.billing << ".\n";
    }

//==================================================== Batas Non-member ============================================
// awal fungsi untuk newMember

    void pilihPaketNewMember(Member& newMember) {
        clearScreen();
        cout << headerBorder << headerNewMember << headerBorder << endl;

        cout << "Pilihan Group:\n";
        cout << "1. Group i3\n";
        cout << "2. Group i5\n";
        cout << "3. Group i7\n";
        cout << "4. Group VIP\n";
        cout << "Masukkan pilihan group: ";
        
        int pilihanGroup;
        cin >> pilihanGroup;

        switch (pilihanGroup) {
            case 0:
                break;
            case 1:
                newMember.group = "Group i3";
                cout << headerBorder << headerNewMember << headerBorder << endl;
                paketNewI3(newMember);
                break;
            case 2:
                newMember.group = "Group i5";
                cout << headerBorder << headerNewMember << headerBorder << endl;
                paketNewI5(newMember);
                break;
            case 3:
                newMember.group = "Group i7";
                cout << headerBorder << headerNewMember << headerBorder << endl;
                paketNewI7(newMember);
                break;
            case 4:
                newMember.group = "Group VIP";
                cout << headerBorder << headerNewMember << headerBorder << endl;
                paketNewVIP(newMember);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    }

    void paketNewI3(Member& newMember) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 5 jam\n";
        cout << "2. Member 10 jam\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi3;
        cin >> pilihanGi3;

        switch (pilihanGi3) {
            case 1:
                newMember.paket = "Member 5 jam";
                newMember.billing = 20000;
                newMember.memberCredits = 5 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            case 2:
                newMember.paket = "Member 10 jam";
                newMember.billing = 40000;
                newMember.memberCredits = 10 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << newMember.paket << " dipilih dengan biaya " << newMember.billing << ".\n";
    }

    void paketNewI5(Member& newMember) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 4 jam\n";
        cout << "2. Member 10 jam\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi5;
        cin >> pilihanGi5;

        switch (pilihanGi5) {
            case 1:
                newMember.paket = "Member 4 jam";
                newMember.billing = 20000;
                newMember.memberCredits = 5 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            case 2:
                newMember.paket = "Member 10 jam";
                newMember.billing = 50000;
                newMember.memberCredits = 10 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << newMember.paket << " dipilih dengan biaya " << newMember.billing << ".\n";
    }

    void paketNewI7(Member& newMember) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 3 jam\n";
        cout << "2. Member 7 jam\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi7;
        cin >> pilihanGi7;

        switch (pilihanGi7) {
            case 1:
                newMember.paket = "Member 3 jam";
                newMember.billing = 25000;  
                newMember.memberCredits = 3 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            case 2:
                newMember.paket = "Member 7 jam";
                newMember.billing = 50000; 
                newMember.memberCredits = 7 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << newMember.paket << " dipilih dengan biaya " << newMember.billing << ".\n";
    }

    void paketNewVIP(Member& newMember) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 4 jam\n";
        cout << "2. Member 7 jam\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGVIP;
        cin >> pilihanGVIP;

            switch (pilihanGVIP) {
            case 1:
                newMember.paket = "Member 4 jam";
                newMember.billing = 50000; 
                newMember.memberCredits = 4 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing); 
                break;
            case 2:
                newMember.paket = "Member 7 jam";
                newMember.billing = 75000; 
                newMember.memberCredits = 7 * 3600;
                tambahDataPemasukan("Pemasukan.json", newMember.billing);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << newMember.paket << " dipilih dengan biaya " << newMember.billing << ".\n";
    }

//==================================================== Batas newMember ============================================
// awal fungsi untuk Member

    void pilihPaketMember(Member& member) {
        clearScreen();
        cout << headerBorder << headerTambahBilling << headerBorder << endl;

        cout << "Pilihan Group:\n";
        cout << "1. Group i3\n";
        cout << "2. Group i5\n";
        cout << "3. Group i7\n";
        cout << "4. Group VIP\n";
        cout << "Masukkan pilihan group: ";
        
        int pilihanGroup;
        cin >> pilihanGroup;

        switch (pilihanGroup) {
            case 0:
                break;
            case 1:
                member.group = "Group i3";
                cout << headerBorder << headerTambahBilling << headerBorder << endl;
                paketI3(member);
                break;
            case 2:
                member.group = "Group i5";
                cout << headerBorder << headerTambahBilling << headerBorder << endl;
                paketI5(member);
                break;
            case 3:
                member.group = "Group i7";
                cout << headerBorder << headerTambahBilling << headerBorder << endl;
                paketI7(member);
                break;
            case 4:
               member.group = "Group VIP";
               cout << headerBorder << headerTambahBilling << headerBorder << endl;
                paketVIP(member);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    }

    void paketI3(Member& member) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 5 jam\n";
        cout << "2. Member 10 jam\n";
        cout << "3. Custom\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi3;
        cin >> pilihanGi3;

        switch (pilihanGi3) {
            case 1:
                member.paket = "Member 5 jam";
                member.billing = 20000;
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 2:
                member.paket = "Member 10 jam";
                member.billing = 40000;
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 3:
                cout << "Masukkan billing :";
                cin >> member.billing;
                member.memberCredits = member.billing / 4000 * 3600;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << member.paket << " dipilih dengan biaya " << member.billing << ".\n";
    }

    void paketI5(Member& member) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 4 jam\n";
        cout << "2. Member 10 jam\n";
        cout << "3. Custom\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi5;
        cin >> pilihanGi5;

        switch (pilihanGi5) {
            case 1:
                member.paket = "Member 4 jam";
                member.billing = 20000;
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 2:
                member.paket = "Member 10 jam";
                member.billing = 50000;
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 3:
                cout << "Masukkan billing :";
                cin >> member.billing;
                member.memberCredits = member.billing / 5000 * 3600;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << member.paket << " dipilih dengan biaya " << member.billing << ".\n";
    }

    void paketI7(Member& member) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 3 jam\n";
        cout << "2. Member 7 jam\n";
        cout << "3. Custom\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGi7;
        cin >> pilihanGi7;

        switch (pilihanGi7) {
            case 1:
                member.paket = "Member 3 jam";
                member.billing = 25000;  
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 2:
                member.paket = "Member 7 jam";
                member.billing = 50000; 
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 3:
                cout << "Masukkan billing :";
                cin >> member.billing;
                member.memberCredits = member.billing / 7000 * 3600;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << member.paket << " dipilih dengan biaya " << member.billing << ".\n";
    }

    void paketVIP(Member& member) {
        clearScreen();
        cout << "Pilihan Paket:\n";
        cout << "1. Member 4 jam\n";
        cout << "2. Member 7 jam\n";
        cout << "3. Custom\n";
        cout << "Masukkan pilihan paket: ";
        
        int pilihanGVIP;
        cin >> pilihanGVIP;

            switch (pilihanGVIP) {
            case 1:
                member.paket = "Member 4 jam";
                member.billing = 50000;  
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 2:
                member.paket = "Member 7 jam";
                member.billing = 75000; 
                tambahDataPemasukan("Pemasukan.json", member.billing);
                break;
            case 3:
                cout << "Masukkan billing :";
                cin >> member.billing;
                member.memberCredits = member.billing / 12500 * 3600;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "\nPaket " << member.paket << " dipilih dengan biaya " << member.billing << ".\n";
    }

    void displayMember(const string& groupName) {
        clearScreen();
        cout << headerBorder << headerListMember << headerBorder << endl;

        if (head == nullptr) {
            cout << "Daftar anggota kosong." << endl;
            return;
        }
        Node* current = head;

        do {
            if (current->data.group == groupName) {
                cout << headerDisplayBorder;
                cout << "  id           : " << current->data.id << endl;
                cout << "  Username     : " << current->data.username << endl;
                cout << "  group        : " << current->data.group << endl;
                cout << headerDisplayBorder << endl;
            }
            current = current->next;
        } while (current != head);
        char ch;
        cout << "1. Selesai" << endl;
        ch = getch();
        clearScreen();
    }

    Node* cariMemberBerdasarkanNama(string nama) {
        if (head == nullptr) return nullptr;

        Node* current = head;
        do {
            if (current->data.username == nama) {
                return current;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    }

};

//================================================================================================================
// int main (operator)

// int main() {
//     int duration;
//     cout << "Masukkan durasi waktu hitung mundur (dalam detik): ";
//     cin >> duration;

//     // Jalankan timer di thread terpisah
//     HANDLE timer_thread = CreateThread(
//         NULL,                // Default security attributes
//         0,                   // Default stack size
//         (LPTHREAD_START_ROUTINE)countdown_timer, // Thread function
//         (LPVOID)duration,    // Argument untuk thread function
//         0,                   // Default creation flags
//         NULL);               // Tidak menyimpan thread identifier

//     // Jalankan fungsi lain sementara timer berjalan di latar belakang
//     some_other_function();

//     // Tunggu sampai timer selesai
//     WaitForSingleObject(timer_thread, INFINITE);

//     // Tutup handle thread setelah selesai
//     CloseHandle(timer_thread);

//     return 0;
// }

int main() {
    clearScreen();
    DoubleLinkedlist list;                                  //pembuatan obj "list" dari class Doublelinkedlist
    tempAdmin newAdmin;                                     //pembuatan obj "newAdmin" dari struct tempAdmin
    string uname, pass, opname, oppass, tempLogin;          //inisialisasi global variabel string untuk login admin dan operator
    int loop = 0, pilihanLogin;                             //inisialisasi variabel untuk looping program dan if else

    while (loop != 1) {
        cout << headerBorder << headerLogin << headerBorder;
        cout << "Login sebagai :\n\n";
        cout << "1. Operator\n";
        cout << "2. Admin\n";
        cout << "3. User\n\n";
        cout << "> ";
        cin >> pilihanLogin;

        if (pilihanLogin == 1) {
            clearScreen();
            cout << headerBorder << headerLogin << headerBorder;
            cout << "Operator : ";
            cin >> opname;
            cout << "Password : ";
            oppass = passwordMask();

            if (cekLoginOperator(opname,oppass)) {
                clearScreen();
                cout << "Login berhasil!\n";
                clock_t start_time = clock();
                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}

                int choice,op;
                op = 0;
                while(op != 1) {
                    clearScreen();
                    cout << headerBorder << headerOperator << headerBorder;
                    int ma;
                    cout << "Pilih menu :\n";
                    cout << "1. Tambah Admin\n";
                    cout << "2. Hapus Admin\n";
                    cout << "3. Edit Admin\n";
                    cout << "4. \n";
                    cout << "5. \n";
                    cout << "0. Exit\n\n";
                    cout << "> ";
                    cin >> ma;

                    if (ma == 0) {
                        clearScreen();
                        op = 1;
                        break;
                    } 
                    else if (ma == 1 ) {
                        clearScreen();
                        json dataAdmin = bacaFileJson("Admin.json");
                        cout << "Masukkan Username Admin Baru :\n";
                        cin >> newAdmin.username;
                        
                        cout << "Masukkan Password Admin Baru :\n";
                        newAdmin.password = passwordMask();
                        cout << "Konfirmasi Password Admin Baru :\n";
                        newAdmin.confPasword = passwordMask();

                        if (newAdmin.password == newAdmin.confPasword) {
                            tambahAdminBaru(newAdmin.username, newAdmin.password, "Admin.json");
                            cout << "Admin berhasil ditambahkan!\n";
                            clock_t start_time = clock();
                            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}                          
                        }                  
                    }
                    else if (ma == 2) {
                        clearScreen();
                        string rmAdmin;
                        cout << "Masukkan Username Admin :";
                        cin >> rmAdmin;
                        
                        if (hapusAdmin(rmAdmin)) {
                            cout << "Admin berhasil dihapus.\n";
                            clock_t start_time = clock();
                            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                        } else {
                            cout << "Admin dengan username tersebut tidak ditemukan.\n";
                            clock_t start_time = clock();
                            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                        }
                    }
                    else if (ma == 3) {
                        clearScreen();
                        string tempEditAdmin, keyEditAdmin, newValue, opsiEdit, tempPassword;
                        int repeatPass = 0, repeatOrder = 0;
                        json dataAdmin = bacaFileJson("Admin.json");
                        
                        cout << "Masukkan username admin yang ingin diubah: ";
                        cin >> tempEditAdmin;
                        clearScreen();
                        
                        while(repeatOrder != 1) {
                            clearScreen();
                            cout << "Pilih yang ingin diubah:\n";
                            cout << "1. Username\n";
                            cout << "2. Password\n";
                            cout << "> ";
                            cin >> opsiEdit;

                            if (opsiEdit == "1") {
                                keyEditAdmin = "username";
                                cout << "Masukkan username baru: ";

                                cin >> newValue;
                                editDataAdmin(dataAdmin, tempEditAdmin, keyEditAdmin, newValue);
                                repeatOrder = 1;

                            } else if (opsiEdit == "2") {

                                while(repeatPass != 1) {
                                    keyEditAdmin = "password";
                                    cout << "Masukkan password baru: ";
                                    newValue = passwordMask();
                                    cout << "Konfirmasi Password Admin Baru :";
                                    tempPassword = passwordMask();

                                    if(newValue == tempPassword) {
                                        editDataAdmin(dataAdmin, tempEditAdmin, keyEditAdmin, newValue);
                                        repeatOrder = 1;
                                        repeatPass = 1;
                                    }
                                    else {
                                        cout << "Password tidak sama, tolong ulangi lagi!";
                                    }
                                }
                            } else {
                                cout << "Pilihan tidak valid.\n";
                                clock_t start_time = clock();
                                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                            }                                
                        }

                        // Simpan perubahan kembali ke file JSON
                        simpanKeJson(dataAdmin, "Admin.json");
                        cout << "Data admin telah diupdate.\n";
                        clock_t start_time = clock();
                        while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {} 
                    }
                    else if (ma == 4) {
                        clearScreen();
                    }
                }
            }
        }
//================================================================================================================
// int main (admin)
        else if (pilihanLogin == 2) {
            clearScreen();
            cout << headerBorder << headerLogin << headerBorder;
            cout << "Username : ";
            cin >> uname;
            cout << "Password : ";
            pass = passwordMask();

            if (cekLoginAdmin(uname, pass)) {
                clearScreen();
                cout << "Login berhasil!\n";
                clock_t start_time = clock();
                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                tambahEntri("log", uname, "Admin telah login", "", "", "", "");

                int choice,A,c;
                A = 0;
                while(A !=1 ) {
                    clearScreen();
                    clock_t start_time = clock();
                    while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                    cout << headerBorder << headerAdmin << headerBorder;
                    cout << "1. Member Baru\n";
                    cout << "2. List Member\n";
                    cout << "3. User Paketan\n";
                    cout << "4. Tambah Billing\n";
                    cout << "5. List Pemasukkan\n";
                    cout << "6. Pengaturan Admin\n";
                    cout << "0. Exit\n\n";
                    cout << "> ";
                    cin >> choice;
                    switch (choice) {
                    case 0: {
                        clearScreen();
                        A = 1;
                        break;
                    }
                    case 1: {
                        clearScreen();
                        Member newMember; 
                        bool uniqueUsername = false;
                        cout << headerBorder << headerNewMember << headerBorder << endl;

                        while (!uniqueUsername) {
                            cout << "Masukkan Username Member Baru: ";
                            cin >> newMember.username;

                            if (list.isUsernameUnique(newMember.username)) {
                                uniqueUsername = true;
                            } else {
                                cout << "Username sudah digunakan. Silakan pilih username lain.\n";
                                clock_t start_time = clock();
                                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {} 
                                clearScreen();
                            }
                        }

                        list.pilihPaketNewMember(newMember); 
                        clock_t start_time = clock();
                        while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {} 
                        tambahEntri("log", uname, "Admin menambahkan member", newMember.username, "", "", newMember.group);

                        list.tambahMember(newMember); 
                        break;
                    }
                    case 2: {
                        clearScreen();
                        cout << headerBorder << headerListMember << headerBorder << endl;
                        cout << "Pilih grup yang akan ditayangkan :\n";
                        cout << "1. Group Non-member\n";
                        cout << "2. Group i3\n";
                        cout << "3. Group i5\n";
                        cout << "4. Group i7\n";
                        cout << "5. Group VIP\n\n";
                        cout << "> ";
                        int pilihanDisplayGroup;
                        cin >> pilihanDisplayGroup;

                        if (pilihanDisplayGroup == 1) {
                            list.displayMember("Group Non-member");
                        }
                        else if (pilihanDisplayGroup == 2) {
                            list.displayMember("Group i3");        
                        }
                        else if (pilihanDisplayGroup == 3) {
                            list.displayMember("Group i5");        
                        }   
                        else if (pilihanDisplayGroup == 4) {
                            list.displayMember("Group i7");        
                        }
                        else if (pilihanDisplayGroup == 5) {
                            list.displayMember("Group VIP");        
                        }
                        else {
                        cout << "Pilihan tidak valid. Silakan masukkan nomor antara 1 dan 5." << endl;
                        }
                        break;
                    }
                    case 3: {
                        clearScreen();
                        cout << headerBorder << headerUserPaketan << headerBorder << endl;

                        Member newMember;
                        const size_t maxSize = 6; // Sesuaikan dengan jumlah maksimum digit yang diharapkan
                        string pi_digits[maxSize];
                        size_t size;

                        list.fillDigits(pi_digits, size);
                        string username = list.generateUsername(pi_digits, size);

                        string hasilGenerateUname = username;
                        newMember.username = hasilGenerateUname;
                        list.paketNonMember(newMember);   
                        list.tambahMember(newMember);  
                        tambahEntri("log", uname, "Admin menambahkan userPaket", "", newMember.paket, "", newMember.group);
                        break;
                    }
                    case 4: {
                        clearScreen();
                        cout << headerBorder << headerTambahBilling << headerBorder << endl;
                        string username;

                        cout << "Masukkan username member: ";
                        cin >> username;
                        Member& member = list.cariMember(username, list);

                        if (&member == nullptr) {
                            cout << "Member tidak ditemukan.\n";
                        } else {
                            cout << "Member ditemukan: " << member.username << endl;
                            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}  
                            cout << "Billing: " << member.billing << endl;

                            list.pilihPaketMember(member);

                            cout << "Biling berhasil ditambahkan!" << endl;
                            clock_t start_time = clock();
                            while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}  
                            cout << "Billing baru: " << member.billing << endl;
                        }
                        tambahEntri("log", uname, "Admin menambahkan billing member", username, member.paket, "", member.group);
                        break;
                    }
                    case 5: {
                        clearScreen();
                        cout << headerBorder << headerPemasukan << headerBorder << endl;
                        double totalPemasukan = getTotalPemasukan();
                        cout << "Total Pemasukan: " << totalPemasukan << endl << endl;
                        char ch;
                        cout << "1. Selesai" << endl;
                        ch = getch();
                        clearScreen();
                        break;
                    }
                    case 6: {
                        int choice,op;
                        op = 0;
                        while(op != 1) {
                            clearScreen();
                            cout << headerBorder << headerPengaturanAdm << headerBorder;
                            int ma;
                            cout << "Pilih menu :\n";
                            cout << "1. Edit\n";
                            cout << "2. \n";
                            cout << "3. \n";
                            cout << "4. \n";
                            cout << "5. \n";
                            cout << "0. Exit\n\n";
                            cout << "> ";
                            cin >> ma;

                            if (ma == 0) {
                                clearScreen();
                                op = 1;
                                break;
                            } 
                            else if(ma == 1) {
                                clearScreen();
                                string tempEditAdmin, keyEditAdmin, newValue, opsiEdit, tempPassword;
                                int repeatPass = 0, repeatOrder = 0;
                                json dataAdmin = bacaFileJson("Admin.json");
                                
                                tempEditAdmin = uname;

                                while(repeatOrder != 1) {
                                    clearScreen();
                                    cout << "Pilih yang ingin diubah:\n";
                                    cout << "1. Username\n";
                                    cout << "2. Password\n";
                                    cout << "> ";
                                    cin >> opsiEdit;

                                    if (opsiEdit == "1") {
                                        keyEditAdmin = "username";

                                        cout << "Masukkan username baru: ";
                                        cin >> newValue;
                                        editDataAdmin(dataAdmin, tempEditAdmin, keyEditAdmin, newValue);
                                        tambahEntri("log", uname, "Admin mengubah username", "", "", newValue, "");
                                        repeatOrder = 1;
                                    } else if (opsiEdit == "2") {
                                        while(repeatPass != 1) {
                                            keyEditAdmin = "password";

                                            cout << "Masukkan password baru: ";
                                            newValue = passwordMask();
                                            cout << "Konfirmasi Password Admin Baru :";
                                            tempPassword = passwordMask();

                                            if(newValue == tempPassword) {
                                                editDataAdmin(dataAdmin, tempEditAdmin, keyEditAdmin, newValue);
                                                repeatOrder = 1;
                                                repeatPass = 1;
                                            }
                                            else {
                                                cout << "Password tidak sama, tolong ulangi lagi!";
                                            }
                                        }
                                    } else {
                                        cout << "Pilihan tidak valid.\n";
                                        clock_t start_time = clock();
                                        while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                                    }
                                }
                                
                                simpanKeJson(dataAdmin, "Admin.json");
                                cout << "Data admin telah diupdate.\n";
                                clock_t start_time = clock();
                                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {} 
                            }
                        }
                    }
                    default:
                        break;
                    }
                }
            } else {
                clearScreen();
                cout << "Username atau password salah. Silahkan coba lagi.";  
                clock_t start_time = clock();
                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                clearScreen();  
            }
        }
//================================================================================================================
// int main (user)
        else if (pilihanLogin == 3) {
            clearScreen();
            cout << headerBorder << headerMember << headerBorder;
            cout << "Username : ";
            cin >> uname;
            cout << "Password : ";
            pass = passwordMask();

            if (list.cekLoginUser(uname, pass)) {
                tambahEntri("log", "", "User telah login", "uname", "", "", "");

                int A = 0;
                while (A != 1){
                    Member& member = list.cariMember(uname, list);
                    int userCredits;

                    userCredits = member.memberCredits;
                    int duration = userCredits;
        
                    // Jalankan timer di thread terpisah
                    HANDLE timer_thread = CreateThread(
                        NULL,                // Default security attributes
                        0,                   // Default stack size
                        countdownTimer,      // Thread function
                        (LPVOID)duration,    // Argument untuk thread function
                        0,                   // Default creation flags
                        NULL);               // Tidak menyimpan thread identifier

                    // Jalankan fungsi lain sementara timer berjalan di latar belakang
                    launcher();
                    Sleep(500);

                    // Tunggu sampai timer selesai
                    WaitForSingleObject(timer_thread, INFINITE);

                    // Memasukkan kembali sisa waktu ke dalam userCredits
                    member.memberCredits = sisaDetik;

                    // Tutup handle thread setelah selesai
                    CloseHandle(timer_thread);
                    A = 1;
                }
            } else {
                clearScreen();
                cout << "Username atau password salah. Silahkan coba lagi.";  
                clock_t start_time = clock();
                while ((clock() - start_time) / CLOCKS_PER_SEC < 1) {}
                clearScreen();  
            }
            loop = 1;
        }
    }
    return 0;
}