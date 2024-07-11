#include <iostream>
#include <ctime>
#include <windows.h> // Untuk fungsi Sleep dan MessageBox pada Windows

using namespace std;

// Fungsi timer hitung mundur
void countdown_timer(int duration) {
    time_t start_time = time(nullptr);

    while (true) {
        time_t current_time = time(nullptr);
        int elapsed_time = current_time - start_time;
        int remaining_time = duration - elapsed_time;

        if (remaining_time <= 0) {
            MessageBoxA(NULL, "Waktu habis!", "Timer", MB_OK);
            break;
        }

        // Tampilkan sisa waktu setiap detik
        string message = "Sisa waktu: " + to_string(remaining_time) + " detik";
        MessageBoxA(NULL, message.c_str(), "Timer", MB_OK);

        Sleep(1000); // Jeda 1 detik
    }
}

void some_other_function() {
    for (int i = 0; i < 5; ++i) {
        string message = "Menjalankan fungsi lain: Langkah " + to_string(i + 1);
        MessageBoxA(NULL, message.c_str(), "Proses Lain", MB_OK);
        Sleep(2000); // Simulasi pekerjaan yang memakan waktu 2 detik
    }
}

int main() {
    int duration;
    cout << "Masukkan durasi waktu hitung mundur (dalam detik): ";
    cin >> duration;

    // Jalankan timer di thread terpisah
    HANDLE timer_thread = CreateThread(
        NULL,                // Default security attributes
        0,                   // Default stack size
        (LPTHREAD_START_ROUTINE)countdown_timer, // Thread function
        (LPVOID)duration,    // Argument untuk thread function
        0,                   // Default creation flags
        NULL);               // Tidak menyimpan thread identifier

    // Jalankan fungsi lain sementara timer berjalan di latar belakang
    some_other_function();

    // Tunggu sampai timer selesai
    WaitForSingleObject(timer_thread, INFINITE);

    // Tutup handle thread setelah selesai
    CloseHandle(timer_thread);

    return 0;
}
