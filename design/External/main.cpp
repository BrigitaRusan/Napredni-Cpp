#include "circle.h"
#include "square.h"
#include "shape.h"
#include "VulkanStrategy.h"
#include "OpenGLStrategy.h"
#include <vector>
#include <memory>

int main(){
    std::vector<ShapeConcept*> shapes;
    VulkanStrategy strategy1{};
    OpenGLStrategy strategy2{};
    ShapeModel<Circle> * c1 = new ShapeModel<Circle>(Circle(1,{2,3}), strategy1);
    ShapeModel<Circle> * c2 = new ShapeModel<Circle>(Circle(2,{0,1}), strategy2);
    ShapeModel<Square> * s1 = new ShapeModel<Square>(Square(1,{0,0}), strategy1);
    ShapeModel<Square> * s2 = new ShapeModel<Square>(Square(3,{2,3}), strategy2);
    shapes.push_back(c1); shapes.push_back(s1);
    shapes.push_back(c2); shapes.push_back(s2);
    for(ShapeConcept * s : shapes)
        s->draw();
    delete s2; delete s1; delete c2; delete c1;
    return 0;
}
