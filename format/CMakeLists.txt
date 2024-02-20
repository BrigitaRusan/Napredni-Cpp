cmake_minimum_required(VERSION 3.12)
project(MyFormat)

# Postavite jezik za CMake
set(CMAKE_CXX_STANDARD 17)

# Pronađite fmt biblioteku
find_package(fmt REQUIRED)

# Dodajte izvršnu datoteku za projekt
add_executable(MyFormat main.cpp)

# Povežite fmt biblioteku s izvršnom datotekom
target_link_libraries(MyFormat PRIVATE fmt::fmt)
