#include <utility>
#include <initializer_list>
#include <stdexcept>

/* Klasa koja implementira statički alocirani vektor.
 */
template <typename T, std::size_t N>
class Array{
    T  data[N];
public:
    // Dodijeljeni konstruktor i konstruktor koji inicijalizira
    Array() {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = T();
        }
    }

    Array(const T& other) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = other;
        }
    }

    // Konstruktor inicijalizacijskom listom
    Array(const std::initializer_list<T>& list) {
        if (list.size() > N) {
            throw std::runtime_error("List size bigger than capacity");
        }
        std::size_t i = 0;
        for (const auto& element : list) {
            data[i++] = element;
        }
    }

    // Konstruktor kopije i operator pridruživanja kopiranjem
    Array(const Array& other) {
        std::copy(other.data, other.data + N, data);
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            std::copy(other.data, other.data + N, data);
        }
        return *this;
    }

    // Operator indeksiranja
    T& operator[](std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    const T& operator[](std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Range-for petlja
    T* begin() { return data; }
    T* end() { return data + N; }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + N;
    }

};

template <typename T, typename S, std::size_t N>
bool operator==(Array<T,N> const & lhs, Array<S,N> const & rhs){
    //return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}
