#include "OpenGLCircleStrategy.h"
#include <iostream>

void OpenGLCircleStrategy::operator()(Circle const & circle) const {
    std::cout << "Iscrtavanje kruga pomocu OpenGL strategije." << std::endl;
    std::cout << "Geometrijski oblik: Krug, Radijus: " << circle.radius() << ", Centar: (" << circle.center().x << ", " << circle.center().y << ")" << std::endl;

}
