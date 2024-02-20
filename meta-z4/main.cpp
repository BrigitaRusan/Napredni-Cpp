#include <fmt/format.h>
#include <type_traits>
#include <array>
#include <cassert>
#include <cstdint> // za (u)intptr_t
#include <vector>
#include <unordered_set>


//Metafunkcija RemoveReference koja uklanja referencu s danog tipa.
template <typename T>
struct RemoveReference {
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;
};

// Alias template za RemoveReference
template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;

//Metafunkcija AddLValueReference koja na tip dodaje lijevu referencu.
template <typename T>
struct AddLValueReference {
    using type = T&;
};

template <>
struct AddLValueReference<void> {
    using type = void;
};

// Alias template za AddLValueReference
template <typename T>
using AddLValueReference_t = typename AddLValueReference<T>::type;

// Metafunkcija IsArray koja vraća true ako je tip polje, inače false.
template <typename T>
struct IsArray : std::false_type {};

template <typename T>
struct IsArray<T[]> : std::true_type {};

template <typename T, std::size_t N>
struct IsArray<T[N]> : std::true_type {};

// Alias template za IsArray
template <typename T>
constexpr bool IsArray_v = IsArray<T>::value;

// Operator zbrajanja za std::array
// TREBALI STE SAMI DEFINIRATI COMMON_TYPE!  -5
template <typename T, typename S>
auto operator+(const std::array<T, 3>& lhs, const std::array<S, 3>& rhs) 
    -> std::array<std::common_type_t<T, S>, 3> {
    std::array<std::common_type_t<T, S>, 3> result{};
    for (std::size_t i = 0; i < 3; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

// Metafunkcija IsBaseOf
template <typename B, typename D>
struct IsBaseOf {
private:
    template<typename T>
    static std::true_type test( B*); // ako je moguća konverzija
    static std::false_type test(...); // inače nije

public:
    // TO NIJE IMPLEMENTACIJA KOJA SE TRAŽI!  -10
    static constexpr bool value = std::is_base_of<B, D>::value;
};


// Predložak varijable hasConstReverseIterator_v<Container> i metafunkciju ConstReverseIteratorType<Container>
template <typename Container, typename = void>
struct hasConstReverseIterator : std::false_type {};

template <typename Container>
struct hasConstReverseIterator<Container, std::void_t<typename Container::const_reverse_iterator>> : std::true_type {};

template <typename Container>
constexpr bool hasConstReverseIterator_v = hasConstReverseIterator<Container>::value;

template <typename Container, typename = void>
struct ConstReverseIteratorType {};

template <typename Container>
struct ConstReverseIteratorType<Container, std::enable_if_t<hasConstReverseIterator_v<Container>>> {
    using type = typename Container::const_reverse_iterator;
};

// Predložak varijable hasMember_x<T>
template <typename T, typename = std::void_t<>>
struct HasMember_x : std::false_type {
};

template <typename T>
struct HasMember_x<T, std::void_t<decltype(std::declval<T>().x)>> :
    std::negation<std::is_function<decltype(&T::x)>> {
};

template <typename T>
constexpr inline bool hasMember_x = HasMember_x<T>::value;


// Klase za testiranje
class B {};
class D : public B {};
class C{};

class E : public B, public C {};

class Base{
    public:
    virtual ~Base() = default;
};
class Derived : public Base {};


class AAA{
    public:
        int x;
};
class BBB{
    public:
        void x() const {}
};
class CCC{
    int y;
};


// Ne mijenjati main!
int main(){
    // 1.
    static_assert(std::is_same_v<RemoveReference_t<int &>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int &&>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int const &>, int const>);

    // 2.
    static_assert(std::is_same_v<AddLValueReference_t<int>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<void>, void>);

    // 3.
    static_assert(IsArray_v<int> == false);
    static_assert(IsArray_v<int[]> == true);
    static_assert(IsArray_v<int[3]> == true);

    // 4.
    std::array<int,3> a{1,2,3};
    std::array<float,3> b{1.0f, 2.0f, 3.0f};
    auto c = a+b;
    assert(c[0] == 2);
    assert(c[1] == 4);
    assert(c[2] == 6);
    static_assert(std::is_same_v<std::decay_t<decltype(c[0])>, float>); 

    // 5.
    static_assert( IsBaseOf<B,D>::value );
    static_assert( !IsBaseOf<B,C>::value );
    static_assert( IsBaseOf<B,B>::value );
    static_assert( !IsBaseOf<int,long>::value );
    static_assert( !IsBaseOf<void,void>::value );
    static_assert( !IsBaseOf<void,B>::value );  //

    static_assert( IsBaseOf<const B,D>::value );
    static_assert( IsBaseOf<B, volatile D>::value ); //

    static_assert( IsBaseOf<B,E>::value );
    static_assert( IsBaseOf<C,E>::value );

    // 6.
    static_assert(hasConstReverseIterator_v<std::vector<int>>);
    static_assert(!hasConstReverseIterator_v<std::unordered_set<int>>);

    ConstReverseIteratorType<std::vector<int>>::type it;
//  ConstReverseIteratorType<std::unordered_set<int>>::type it1;  // ne kompilira se

    // 7.
    static_assert(hasMember_x<AAA>);
    static_assert(!hasMember_x<BBB>);
    static_assert(!hasMember_x<CCC>);


    return 0;
}
