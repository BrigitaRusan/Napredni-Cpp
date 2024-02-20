#include "log.h"
#include <iostream>
#include <fmt/format.h>

int main(){
    Log log("Salje", 2, {'A', 'B', 'C'}, "Poruka");

    auto [sender, priority, code, message] = log;

    std::cout << "Sender: " << sender << ", Priority: " << priority << ", Code: ";
    for (char c : code) {
       std::cout << c;
    }
    std::cout << ", Message: " << message << std::endl;

    setPriority(log,3); // Promjena prioriteta
    std::cout << "Novi prioritet: " << log.priority() << std::endl;
    return 0;
}
