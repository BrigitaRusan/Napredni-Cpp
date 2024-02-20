#include <fmt/format.h>
#include <fmt/ostream.h>
#include <array>
#include <fstream>

#include <ctime>
#include <fmt/core.h>
#include <cstdlib>
#include <cmath>

int main() {
    // Generator slučajnih brojeva
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // a. Generiranje i ispis slučajnog niza
    std::array<int, 10> randomArr;
    for (int i = 0; i < 10; i++) {
        randomArr[i] = 1 + std::rand() % 20;
    }

    for (int i = 0; i < 10; i++) {
        fmt::print("{0:2}: {1:.>10} ** {1:.<10} ** {1:.^10} ** {1:.^#10x}\n", i, randomArr[i]);
    }

    fmt::print("\n");

    // b. Ispis broja pi
    double pi = M_PI;
    for (int i = 0; i < 10; i++) {
	int b = 3 + i;
        if (i % 2 == 1) {
            fmt::print("{0:2}: {1:>+16.{2}f}\n", i, pi, b);
        } else {
            fmt::print("{0:2}: {1:>16.{2}f}\n", i, pi, b);
        }
    }

    fmt::print("\n");

    // c. Ispis varijabli u datoteku
    int var1 = 42, var2 = 123, var3 = 789;
    std::ofstream file("adrese.txt");
    if (file.is_open()) {
        fmt::print(file, "Adresa varijable 1: {}\n", static_cast<void*>(&var1));
        fmt::print(file, "Adresa varijable 2: {}\n", static_cast<void*>(&var2));
        fmt::print(file, "Adresa varijable 3: {}\n", static_cast<void*>(&var3));

        file.close();
    } else {
        fmt::print("Nije moguće otvoriti datoteku adrese.txt\n");
    }

    return 0;
}
