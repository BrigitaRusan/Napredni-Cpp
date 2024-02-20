#include "range/v3/all.hpp"  // to je dovoljno za range-v3.
                             // Pojedini elementi se mogu "includati" i pojedinačno.
#include "fmt/format.h"
#include <iostream>
#include <string>
#include <optional>

using namespace ranges; // Nikako ne uključivati std!

struct Planet {
    std::string name;
    double gravity;
};


int main(){
    {
     //1. Generirajte niz 1,2,2,3,3,3.......9,9,9,9,9,9,9,9,9.

    auto repeated_numbers = views::iota(1, 10)
        | views::transform([](int num) {
            return yield_from(views::repeat_n(num, num));
        })
        | views::join;

        fmt::print("1. Generiran niz: ");
        ranges::for_each(repeated_numbers, [](int num) {
        fmt::print("{} ", num);
        });
         fmt::print("\n");
    }

    {
    // 2. Nađi planet s gravitacijom 11.15 m²/s. Rezultat vratiti (i ispisati)
    //    kao std::optional<std::string>.
    Planet const v[] = {{"Venus",8.87}, {"Mars",3.711}, {"Jupiter", 24.92},{"Neptun", 11.15},
                        {"Saturn", 10.44}, {"Uran",8.69}};

       auto result = v | views::filter([](const Planet& p) { return p.gravity == 11.15; }) |
                         views::transform([](const Planet& p) { return p.name; });

        if (!result.empty()) {
            fmt::print("2. Planet s gravitacijom 11.15: {}\n", *result.begin());
        } else {
            fmt::print("2. Planet s gravitacijom 11.15 nije pronađen.\n");
        }

    }

    {
    // 3. Aproksimirajte broj  π koristeći Gregory - Leibnizovu formulu
    // π ≈ 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...). Ispišite rezultat s 30 članova.

      auto pi_series = views::iota(0, 30)
        | views::transform([](int n) {
            return 1.0 / (2 * n + 1) * (n % 2 == 0 ? 1 : -1);
        });

      double pi_approx = 4 * accumulate(pi_series, 0.0);

      fmt::print("3. Aproksimacija broja π: {}\n", pi_approx);
    }

    {
    // 4. Selektirati domenu u web adresi i konverirati ju u string. Ispisati.

    auto const str = std::string{"https://en.test.org"};  // -> org

        auto result = str
        | views::reverse
        | views::take_while([](char c) { return c != '.'; })
        | views::reverse
        | to<std::string>;

        fmt::print("4. Selektirana domena: {}\n", result);
    }

   {
      //5.  Pretvoriti CAMELCASE string u SNAKE_CASE.
      std::string str{"ovoJeMojaCamelCaseVarijabla"};

      auto snake_case = str | ranges::views::transform([](char c) {
        return std::string{std::isupper(static_cast<unsigned char>(c)) ? '_' : '\0'} + static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
       });

      std::string result = ranges::accumulate(snake_case, std::string{});
      fmt::print("5. Snake case: {}\n", result);
    }

    {
      //6.  Izračunati euklidsku udaljenost između dvije točke zadana tipom std::array<double,n>.
      std::array<double,4> a{1,2,3,4}, b{4,3,2,1};
         auto squared_diff = ranges::view::transform(
        ranges::view::zip(a, b),
        [](auto pair) {
            return std::pow(std::get<0>(pair) - std::get<1>(pair), 2);
            }
        );

       double distance = std::sqrt(ranges::accumulate(squared_diff, 0.0));

       fmt::print("6. Euklidska udaljenost: {}\n", distance);
    }

    {
    //7.  Provjeriti korektnost ISBN-13 broja (na primjer 9780306406157).
    //    Polazeći s lijeva na desno treba naizmjenično množiti znamenke s 1 odnosno 3.
    //    (Prvu znamenku množimo s 1, drugu s 3, treću s 1 itd. Broj ima 13 znamenaka.)
    //    Zatim zbrojimo tako dobivenih
    //    prvih 12 vrijednosti i izračunamo ostatak sume modulo 10. Ako je dobiveni broj nakon toga
    //    različit od nule, oduzmemo ga od 10. Izračunata vrijednost mora biti jednaka 13. znamenci.

       long int n = 9780306406157;

       long int m = n;
       std::vector<int> isbn;
       ranges::generate_n(std::back_inserter(isbn), 13, [&m]() {
        int digit = m % 10;
        m /= 10;
        return digit;
        });
      std::reverse(isbn.begin(), isbn.end());

      auto transform_view = ranges::views::iota(0, 12)
          | ranges::views::transform([&isbn](int i) { return isbn[i] * ((i % 2 == 0) ? 1 : 3); });

      int sum_result = ranges::accumulate(transform_view, 0);
      int remainder = sum_result % 10;
      int check_digit = (remainder != 0) ? 10 - remainder : 0;

      bool is_valid = check_digit == isbn[12];

      if (is_valid) {
          fmt::print("7. ISBN-13 broj {} je korektan.\n", n);
       } else {
          fmt::print("7. ISBN-13 broj {} nije korektan.\n", n);
         }
     }

     {
      //8.  Naći i ispisati sve troznamenkaste narcisoidne brojeve. Broj je narcisoidan ako je
      //    jednak sumi svojih znameni dignutih na treću potenciju. Na primjer, 153 = 1³ + 5³ + 3³.

        auto is_narcissistic = [](int num) {
        auto digits = to<std::vector<int>>(views::ints(0, 10) | views::transform([](int n) {
            return n * n * n;
        }));
        return num == accumulate(views::ints(0, 3) | views::transform([num, &digits](int i) {
            return digits[(num / static_cast<int>(std::pow(10, i))) % 10];
        }), 0);
    };

    std::vector<int> narcissistic_numbers;
    copy_if(views::ints(100, 1000), back_inserter(narcissistic_numbers), is_narcissistic);

      fmt::print("8. Troznamenkasti narcisoidni brojevi: {}\n", fmt::join(narcissistic_numbers, " "));
      }

      return 0;
}
