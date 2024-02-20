#include "demengle.h"

#include <iostream>
#include <concepts>
#include <type_traits>
#include <span>

/* Zadatak 1. Napisati koncept FPCont koji ispituje da li tip T
 *            ima metode begin() i end(), da li se povratna vrijednost od
 *            begin() dade dereferncirati te da li daje nešto konvertibilno u
 *            tip double.
 */
// -5 bodova
template <typename T>
concept FPCont = requires(T t) {
     t.begin();
    t.end();
    {*t.begin()} -> std::convertible_to<double>; 
//    { t.begin() } -> std::same_as<decltype(t.end())>; // NIJE SE TRAŽILO
//     *t.begin();  // NEMA TIPA !
};

// Klase X,Y i Z služe za testiranje Zadatka 1.
class X{};

struct Y{
    void begin(){}
    void end(){}
};

struct Z{
    float * begin(){ return nullptr;}
    float * end(){ return nullptr; }
};

// Zadatak 2.  Napraviti koncept Same<T,S> koji je istina ako su
//             tipovi T i S jednaki nakon zanemarivanja dekoracija const i
//             volatile.

template <typename T, typename S>
concept Same = std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<S>>;


// Zadatak 3. Napisati koncept Number koji je istinit za sve cjelobrojne
//          tipove i sve tipove s pokretnim zarezom, osim za tip bool
//          i sve moguće char tipove. (bool i char-ovi su cjelobrojni tipovi).
//          Ograničeni predložak mult() služi za testiranje koncepta.
//

// Neograničeni predložak funkcije mult() - samo kako ne bi imali grešku pri kompilaciji.
// UPUTA: Ako demengle_type_name(x) ne radi na vašem sustavu, zamijenite
//        ga s typeid(x).name(). Isto za y.

auto mult(auto x, auto y){
    std::cerr << "Greška. Tip od x = " << demengle_type_name(x)
              << ". Tip od y = " << demengle_type_name(y) << "\n";
    return -1;
}

// -10 bodova
template<typename T>
//concept Number = std::is_integral_v<T> || std::is_floating_point_v<T> 
concept Number = (std::integral<T> || std::floating_point<T>) // ZAGRADE SU BITNE!!
                 && !std::is_same_v<T, bool> && !std::is_same_v<T, char> &&
                  !std::is_same_v<T, signed char> && !std::is_same_v<T, unsigned char> &&
                  !std::is_same_v<T, char8_t> && !std::is_same_v<T, char16_t> &&
                  !std::is_same_v<T, char32_t> && !std::is_same_v<T, wchar_t>;

template<Number T, Number U>
auto mult(T x, U y){
    return x * y;
}


// ZADATAK 4. Napraviti koncept Pointer koji predstavlja pointer. Pri tome je pointer (po
//          našoj definiciji)  "void *" ili nešto što se dade dereferencirati.
//          Napravite predložak "print(auto const & val)" koji ispisuje vrijednost val
//    { t.begin() } -> std::convertible_to<typename std::add_pointer<decltype(*t.begin())>::type>;
//    { t.end() };/          te napravite preopterećenje predloška print() koje uzima pokazivač val i ispisuje *val.
//          Ispravno preopterećenje postići koristeći koncept Pointer.

template<typename T>
concept Pointer = std::is_pointer_v<T>;  // TREBALO JE UZETI NAŠU DEFINICIJU!!!!

template<typename T>
requires (!Pointer<T>)
void print(const T& val) {
    std::cout << val << std::endl;
}

template <Pointer T>
void print(T val) {
    std::cout << *val << std::endl;
}

// ZADATAK 5.
// Treba napisati koncept Two koji proizvoljan niz argumenata zadovoljava ako svi argumenti
// pripadaju zadanom skupu od dva tipa int i char.


template<typename T>
concept Satisfies = std::same_as<T, int> || std::same_as<T, char>;

template<typename... Args>
concept Two = (sizeof...(Args) >= 2) && (Satisfies<Args> && ...);


// Funkcija koja može uzeti proizvoljan broj parametara ali samo
// tipa int i char (u bilo kojem poretku).
template<typename... Args>
requires Two<Args...>
void f1(Args... args){
	std::cout << "OK\n";
}

/* Zadatak 6. Napisati koncept InPlaceEngine koji provjerava da tip
 *          ima metodu process() koja kao argument uzima std::span<double>.
 *          Klasa Wrapper je parametrizirana s tipom koji mora imati
 *          metodu process(). Zamijenite opći predložak Wrapper s
 *          predloškom ograničenim na tipove koji zadovoljavaju
 *          koncept InPlaceEngine. Implementirajte metodu Wrapper::reset()
 *          tako da poziva Engine::reset() ako takva metoda postoji,
 *          a ne radi ništa ako ne postoji. Pri tome koristiti
 *          samo if constexpr i requires!
 */


template <typename T>
concept InPlaceEngine = requires(T t) {
    { t.process(std::span<double>()) };
//    { t.reset(std::span<double>()) } -> std::same_as<void>; // TO NIJE POTREBNO 
};

// Polazni kod klase Wrapper - neograničeni predložak
template <typename Engine>
class Wrapper{
    public:
        Wrapper(Engine e) : engine_(std::move(e)) {}
        void process(std::span<double> buf){
            engine_.process(buf);
        }
            // Ako Engine::reset() postoji, pozovi ga.
            // Ako ne postoji ispiši "reset ne postoji".
            // Koristiti if constexpr i requires!
        void reset() {
         if constexpr (requires (Engine e) {e.reset();}){
              engine_.reset();
           }
            else {
              std::cout << "reset ne postoji\n";
           }
        }
    private:
        Engine engine_;
};

// Engine klase za testiranje.
struct Engine1{
    void process(std::span<double> sp){ std::cout << "process\n"; }
};
struct Engine2{
    void process(std::span<double> sp){ std::cout << "process\n"; }
    void reset() const { std::cout << "resret\n"; }
};
struct Engine3{
};
