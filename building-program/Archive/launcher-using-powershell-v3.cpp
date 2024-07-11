#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

// Fungsi untuk membuka URL atau aplikasi
void open_application(const wchar_t* application) {
    ShellExecuteW(0, 0, application, 0, 0, SW_SHOW);
}

// Fungsi untuk membaca preferensi dari file
vector<string> read_preferences(const string& filename) {
    vector<string> preferences;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        preferences.push_back(line);
    }

    file.close();
    return preferences;
}

// Fungsi untuk menampilkan menu aplikasi
void display_menu(const vector<string>& preferences) {
    cout << "Pilih aplikasi untuk dibuka:\n";
    for (size_t i = 0; i < preferences.size(); ++i) {
        cout << i + 1 << ". " << preferences[i] << endl;
    }
    cout << preferences.size() + 1 << ". Keluar\n";
    cout << "Masukkan pilihan (1-" << preferences.size() + 1 << "): ";
}

int main() {
    vector<string> preferences = read_preferences("preferences.txt");
    int choice;

    display_menu(preferences);
    cin >> choice;

    if (choice > 0 && choice <= preferences.size()) {
        // Mengubah string C++ ke wide string
        wstring wstr(preferences[choice - 1].begin(), preferences[choice - 1].end());
        open_application(wstr.c_str());
    } else if (choice == preferences.size() + 1) {
        cout << "Keluar dari program." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}

// Penjelasan:
// - Fungsi `read_preferences` membaca preferensi dari file teks dan menyimpannya dalam vector string.
// - Fungsi `display_menu` menampilkan menu berdasarkan preferensi yang dibaca.
// - Kode utama membaca preferensi dari file "preferences.txt" dan menampilkan menu. Jika pengguna memilih opsi yang valid, aplikasi atau URL akan dibuka.
