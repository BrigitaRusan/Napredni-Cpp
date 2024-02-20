#include "OpenGLSquareStrategy.h"
#include <iostream>

void OpenGLSquareStrategy::operator()(const Square &square) const {

    std::cout << "Iscrtavanje kvadrata pomocu OpenGL strategije." << std::endl;
    std::cout << "Geometrijski oblik: Kvadrat, Stranica: " << square.side() << ", Gornji lijevi kut: (" << square.upper_left_corner().x << ", " << square.upper_left_corner().y << ")" << std::endl;
}
