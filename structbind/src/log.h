#pragma once
#include <string>
#include <array>
#include <fmt/format.h>

class Log{
    std::string _sender;
    int _priority;
    std::array<char,3> _code;
    std::string _message;
public:
    Log(std::string sender, int priority, std::array<char,3> code, std::string message);

    // Getteri za članove klase
    // Implementacija malih metoda ide u klasu kako bi bile inline.
    std::string& sender();
    int& priority();
    std::array<char, 3>& code();
    std::string& message();

    // Konstantni getteri za članove klase
    const std::string& sender() const;
    int priority() const;
    const std::array<char, 3>& code() const;
    const std::string& message() const;
};

// Specijalizacija za std::tuple_size
template <>
struct std::tuple_size<Log> {
    static constexpr std::size_t value = 4;
};

// Specijalizacije za std::tuple_element
template <std::size_t N>
struct std::tuple_element<N, Log> {};

template <>
struct std::tuple_element<0, Log> {
    using type = std::string;
};

template <>
struct std::tuple_element<1, Log> {
    using type = int;
};

template <>
struct std::tuple_element<2, Log> {
    using type = std::array<char, 3>;
};

template <>
struct std::tuple_element<3, Log> {
    using type = std::string;
};

// Specijalizacija za std::get funkcije
template <std::size_t N> decltype(auto) get(const Log&);
template <std::size_t N> decltype(auto) get(Log&);
template <std::size_t N> decltype(auto) get(Log&&);

// Setter za promjenu prioriteta poruke
void setPriority(Log& log, int newPriority);

// Implementacije fja std:get
template <>
inline decltype(auto) get<0>(const Log& log) { return log.sender();}

template <>
inline decltype(auto) get<1>(const Log& log) { return log.priority();}

template <>
inline decltype(auto) get<2>(const Log& log) { return log.code();}

template <>
inline decltype(auto) get<3>(const Log& log) { return log.message();}


template <>
inline decltype(auto) get<0>(Log& log) { return log.sender();}

template <>
inline decltype(auto) get<1>(Log& log) { return log.priority();}

template <>
inline decltype(auto) get<2>(Log& log) { return log.code();}

template <>
inline decltype(auto) get<3>(Log& log) { return log.message();}



template <>
inline decltype(auto) get<0>(Log&& log) { return log.sender();}

template <>
inline decltype(auto) get<1>(Log&& log) { return log.priority();}

template <>
inline decltype(auto) get<2>(Log&& log) { return log.code();}

template <>
inline decltype(auto) get<3>(Log&& log) { return log.message();}
