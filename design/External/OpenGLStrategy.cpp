#include "OpenGLStrategy.h"
#include <iostream>

void OpenGLStrategy::operator()(Circle const & circle) const {
    std::cout << "Iscrtavanje kruga preko OpenGLStrategy" << std::endl;
}

void OpenGLStrategy::operator()(Square const & square) const {
    std::cout << "Iscrtavanje kvadrata preko OpenGLStrategy" << std::endl;

}

