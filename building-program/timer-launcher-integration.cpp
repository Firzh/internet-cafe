#include <iostream>
#include <ctime>
#include <windows.h> // Untuk fungsi Sleep dan ShellExecuteW pada Windows

using namespace std;

// Variabel global untuk menghentikan timer dan menyimpan sisa waktu
bool stopTimer = false;
int sisaDetik = 0;

// Fungsi timer hitung mundur
DWORD WINAPI countdown_timer(LPVOID lpParam) {
    int duration = (int)lpParam;
    time_t start_time = time(nullptr);

    while (true) {
        if (stopTimer) {
            time_t current_time = time(nullptr);
            int elapsed_time = current_time - start_time;
            sisaDetik = duration - elapsed_time;
            break;
        }

        time_t current_time = time(nullptr);
        int elapsed_time = current_time - start_time;
        int remaining_time = duration - elapsed_time;

        if (remaining_time <= 0) {
            cout << "\nWaktu habis!" << endl;
            break;
        }

        // Tampilkan sisa waktu setiap detik
        cout << "\rSisa waktu: " << remaining_time << " detik " << flush;

        Sleep(1000); // Jeda 1 detik
    }

    return 0;
}

// Fungsi untuk membuka URL atau aplikasi
void open_application(const char* application) {
    // Mengubah string C-style ke wide string
    wchar_t wtext[256];
    mbstowcs(wtext, application, strlen(application) + 1);
    LPCWSTR lpwstr = wtext;

    ShellExecuteW(0, 0, lpwstr, 0, 0, SW_SHOW);
}

// Fungsi launcher sederhana
void launcher() {
    int choice = 0;
    do {
        cout << "Pilih aplikasi untuk dibuka:\n";
        cout << "1. Google\n";
        cout << "2. YouTube\n";
        cout << "3. Notepad\n";
        cout << "4. Kalkulator\n";
        cout << "5. Keluar\n\n";
        cout << "Masukkan pilihan: ";
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
                stopTimer = true; // Menghentikan timer
                Sleep(2);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                Sleep(2);
                break;
        }
    } while (choice != 5);
}

int main() {
    int duration;
    cout << "Masukkan durasi waktu hitung mundur (dalam detik): ";
    cin >> duration;

    // Jalankan timer di thread terpisah
    HANDLE timer_thread = CreateThread(
        NULL,                // Default security attributes
        0,                   // Default stack size
        countdown_timer,     // Thread function
        (LPVOID)duration,    // Argument untuk thread function
        0,                   // Default creation flags
        NULL);               // Tidak menyimpan thread identifier

    // Jalankan fungsi launcher di thread utama
    launcher();

    // Tunggu sampai timer selesai
    WaitForSingleObject(timer_thread, INFINITE);

    // Tutup handle thread setelah selesai
    CloseHandle(timer_thread);

    // Tampilkan sisa detik
    cout << "Sisa waktu: " << sisaDetik << " detik" << endl;

    return 0;
}
