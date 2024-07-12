#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

// Fungsi penanganan sinyal
void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        cout << "\nWaktu habis!" << endl;
    }
}

void countdown_timer(int duration) {
    // Mengatur penanganan sinyal untuk SIGALRM
    signal(SIGALRM, handle_alarm);
    
    // Mengatur alarm untuk durasi yang ditentukan
    alarm(duration);
}

void some_other_function() {
    for (int i = 0; i < 5; ++i) {
        cout << "Menjalankan fungsi lain: Langkah " << i + 1 << endl;
        sleep(2); // Simulasi pekerjaan yang memakan waktu 2 detik
    }
}

int main() {
    int duration;
    cout << "Masukkan durasi waktu hitung mundur (dalam detik): ";
    cin >> duration;

    // Memulai timer hitung mundur
    countdown_timer(duration);

    // Menjalankan fungsi lain sementara timer berjalan di latar belakang
    some_other_function();

    // Menunggu sampai timer selesai
    pause(); // Menunggu sinyal untuk mengakhiri program

    return 0;
}
