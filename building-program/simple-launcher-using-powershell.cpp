#include <iostream>
#include <windows.h>

using namespace std;

// Fungsi untuk membuka URL atau aplikasi
void open_application(const char* application) {
    // Mengubah string C-style ke wide string
    wchar_t wtext[256];
    mbstowcs(wtext, application, strlen(application) + 1);
    LPCWSTR lpwstr = wtext;

    ShellExecute(0, 0, lpwstr, 0, 0, SW_SHOW);
}

int main() {
    int choice;
    cout << "Pilih aplikasi untuk dibuka:\n";
    cout << "1. Google\n";
    cout << "2. YouTube\n";
    cout << "3. Notepad\n";
    cout << "4. Kalkulator\n";
    cout << "5. Keluar\n";
    cout << "Masukkan pilihan (1-5): ";
    cin >> choice;

    switch (choice) {
        case 1:
            open_application("https://www.google.com");
            break;
        case 2:
            open_application("https://www.youtube.com");
            break;
        case 3:
            open_application("notepad");
            break;
        case 4:
            open_application("calc");
            break;
        case 5:
            cout << "Keluar dari program." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
    }

    return 0;
}
