#include "VulkanStrategy.h"
#include <iostream>

void VulkanStrategy::operator()(Circle const & circle) const {
    std::cout << "Iscrtavanje kruga preko VulkanStrategy" << std::endl;
}

void VulkanStrategy::operator()(Square const & square) const {
    std::cout << "Iscrtavanje kvadrata preko VulkanStrategy" << std::endl;
}
