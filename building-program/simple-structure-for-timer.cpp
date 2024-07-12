#include <iostream>
#include <string>
#include <ctime>
#include <ctime>
#include <windows.h>

using namespace std;

struct User {
    string username;
    time_t loginTime;
    time_t logoutTime;
    bool isLoggedIn;
};

void login(User &user) {
    if (!user.isLoggedIn) {
        user.isLoggedIn = true;
        user.loginTime = time(0); // waktu saat ini
        cout << "User " << user.username << " berhasil login." << endl;
    } else {
        cout << "User sudah login." << endl;
    }
}

void logout(User &user) {
    if (user.isLoggedIn) {
        user.logoutTime = time(0);
        user.isLoggedIn = false;
        cout << "User " << user.username << " berhasil logout." << endl;
    } else {
        cout << "User belum login." << endl;
    }
}

double calculateCost(User &user, double ratePerSecond) {
    if (!user.isLoggedIn) {
        double duration = difftime(user.logoutTime, user.loginTime);
        return duration * ratePerSecond;
    } else {
        cout << "User masih login. Logout dulu untuk menghitung biaya." << endl;
        return 0.0;
    }
}

int main() {
    User user;
    user.username = "user1";
    user.isLoggedIn = false;

    double ratePerSecond = 0.05; // contoh tarif per detik

    int choice;
    do {
        cout << "1. Login\n2. Logout\n3. Hitung Biaya\n4. Keluar\nPilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                login(user);
                break;
            case 2:
                logout(user);
                break;
            case 3:
                cout << "Biaya penggunaan: Rp" << calculateCost(user, ratePerSecond) << endl;
                break;
            case 4:
                cout << "Keluar program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 4);

    return 0;
}
