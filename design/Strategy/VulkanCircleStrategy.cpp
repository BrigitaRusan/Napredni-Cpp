#include "VulkanCircleStrategy.h"
#include <iostream>

void VulkanCircleStrategy::operator()(Circle const & circle) const {

    std::cout << "Iscrtavanje kruga pomocu Vulkan strategije." << std::endl;
    std::cout << "Geometrijski oblik: Krug, Radijus: " << circle.radius() << ", Centar: (" << circle.center().x << ", " << circle.center().y << ")" << std::endl;

}
