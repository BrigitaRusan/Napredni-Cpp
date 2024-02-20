#include <iostream>
#include <cassert>
#include <type_traits>

// Zadatak 1.
// a. prva verzija koja koristi rekurziju i specijalizaciju predloška.

//template <unsigned int d, unsigned int k>
//struct Dim{
//        static constexpr unsigned int value = (k == 0 || d == k) ? 1 : Dim<d - 1, k - 1>::value + Dim<d - 1, k>::value;
//};

// Eventualne specifikacije

//template <>
//struct Dim<0,0>{
//    static constexpr unsigned int value = 1;
//};


// b. druga verzija koja koristi c++11 constexpr funkciju. 
//    Funkcija se sastoji od samo jedne return naredbe, 

//constexpr unsigned int dim(unsigned int d, unsigned int k){
//    return (k == 0 || d == 0) ? 1 : dim(d - 1, k - 1) + dim(d - 1, k);
    //return (k == 0 || d == 0) ? 1 : (d + k) * (d + k - 1) / (2 * k + 1);
//}

// c. treća verzija koja koristi c++14 constexpr funkciju i ne koristi
//  rekurziju.
//constexpr unsigned int dim14(unsigned int d, unsigned int k){
//        if (k > d) return 0;
//	unsigned int result = 1;
 //   for (unsigned int i = 0; i < k; ++i) {
 //       result *= (d - i);
 //       result /= (i + 1);
 //   }
//    return result;
//}


// Zadatak 2.
// a. C++11 verzija
//constexpr int p = 31;
//constexpr int64_t m = 1'000'000'009LL;

int p = 31;
int64_t m = 1000000009LL;

constexpr int64_t hash11(const char *s) {
    return (*s == '\0') ? 0 : ((static_cast<int64_t>(*s - 'a' + 1) * static_cast<int64_t>(*s - 'a' + 1)) + hash11(s + 1)) % m;
}


// b. C++14 verzija
constexpr int64_t hash14(const char *s){
    int64_t hashValue = 0;
    int64_t p_pow = 1;
int p = 31;
int64_t m = 1000000009LL;

    for (int i = 0; s[i] != '\0'; ++i) {
        hashValue = (hashValue + (s[i] - 'a' + 1) * p_pow );
        p_pow = (p_pow * p) % m;
    }
    return hashValue;
}




int main(){
        // Ovaj kod ne brisati! Možete dodavati svoje testove.
        // Zadatak 1.
        // 1.
/*        static_assert(Dim<0,3>::value == 1);
        static_assert(Dim<3,0>::value == 1);
        static_assert(Dim<3,1>::value == 4);
        static_assert(Dim<3,2>::value ==s[index] - 'a' + 1 10);
        static_assert(Dim<3,3>::value == 20);
        static_assert(Dim<5,3>::value == 56);
        // 2.
        static_assert(dim(0,3) == 1);
        static_assert(dim(3,0) == 1);
        static_assert(dim(3,1) == 4);
        static_assert(dim(3,2) == 10);
        static_assert(dim(3,3) == 20);
        static_assert(dim(5,3) == 56);
        //3.
        static_assert(dim14(0,3) == 1);
        static_assert(dim14(3,0) == 1);
        static_assert(dim14(3,1) == 4);
        static_assert(dim14(3,2) == 10);
        static_assert(dim14(3,3) == 20);
        static_assert(dim14(5,3) == 56);
*/
        // Zadatak 2.
        constexpr const char * s1="abcder";
        constexpr const char * s2="ertamabcdernn";
        constexpr const char * s3="afgtbbnjiocbfrewqdeloikjuhbvcr";
        constexpr const char * s4="utdtbbnjiocbzrewddegoimjeh";

        std::cout << hash11(s1) << "\n";
        std::cout << hash11(s2) << "\n";
        std::cout << hash11(s3) << "\n";
        std::cout << hash11(s4) << "\n";

        std::cout << hash14(s1) << "\n";
        std::cout << hash14(s2) << "\n";
        std::cout << hash14(s3) << "\n";
        std::cout << hash14(s4) << "\n";


      /*  static_assert(hash11(s1) == 520064433);
        static_assert(hash11(s2) == 202527068);
        static_assert(hash11(s3) == 615720090);
        static_assert(hash11(s4) == 814096530);

        static_assert(hash14(s1)==hash11(s1));
        static_assert(hash14("ertamabcdernn")==hash11("ertamabcdernn"));
        static_assert(hash14(s3)==hash11(s3));
        static_assert(hash14(s4)==hash11(s4));
*/
        return 0;
}
