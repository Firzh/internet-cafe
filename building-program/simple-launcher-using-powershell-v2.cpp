#include <iostream>
#include <windows.h>
#include <userenv.h>
#include <string>

using namespace std;

// Fungsi untuk membuka aplikasi sebagai user lain
bool launch_as_user(char* username, char* password, char* application) {
    HANDLE hToken;
    if (LogonUserA(username, ".", password, LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken) == 0) {
        cout << "Login gagal: " << GetLastError() << endl;
        return false;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    if (CreateProcessAsUserA(hToken, NULL, application, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0) {
        cout << "Gagal menjalankan aplikasi: " << GetLastError() << endl;
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

int main() {
    int choice;
    char username[256];
    char password[256];

    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    cout << "Pilih aplikasi untuk dibuka:\n";
    cout << "1. Google\n";
    cout << "2. YouTube\n";
    cout << "3. Notepad\n";
    cout << "4. Kalkulator\n";
    cout << "5. Keluar\n";
    cout << "Masukkan pilihan (1-5): ";
    cin >> choice;

    char* application;
    switch (choice) {
        case 1:
            application = "https://www.google.com";
            break;
        case 2:
            application = "https://www.youtube.com";
            break;
        case 3:
            application = "notepad.exe";
            break;
        case 4:
            application = "calc.exe";
            break;
        case 5:
            cout << "Keluar dari program." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid." << endl;
            return 0;
    }

    if (launch_as_user(username, password, application)) {
        cout << "Aplikasi berhasil dijalankan sebagai user " << username << endl;
    } else {
        cout << "Gagal menjalankan aplikasi." << endl;
    }

    return 0;
}