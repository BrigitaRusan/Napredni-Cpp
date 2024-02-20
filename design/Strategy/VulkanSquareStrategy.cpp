#include "VulkanSquareStrategy.h"
#include <iostream>

void VulkanSquareStrategy::operator()(Square const & square) const {

    std::cout << "Iscrtavanje kvadrata pomocu Vulkan strategije." << std::endl;
    std::cout << "Geometrijski oblik: Kvadrat, Stranica: " << square.side() << ", Gornji lijevi kut: (" << square.upper_left_corner().x << ", " << square.upper_left_corner().y << ")" << std::endl;

}
