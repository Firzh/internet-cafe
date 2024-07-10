#include <iostream>
#include <ctime>
#include <windows.h> // Untuk fungsi Sleep pada Windows

using namespace std;

// Fungsi timer hitung mundur
void countdown_timer(int duration) {
    time_t start_time = time(nullptr);

    while (true) {
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
}

void some_other_function() {
    for (int i = 0; i < 5; ++i) {
        cout << "\nMenjalankan fungsi lain: Langkah " << i + 1 << endl;
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
