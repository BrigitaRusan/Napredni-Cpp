#include "circle.h"
#include "square.h"
#include "VulkanCircleStrategy.h"
#include "VulkanSquareStrategy.h"

#include "OpenGLCircleStrategy.h"
#include "OpenGLSquareStrategy.h"

#include <vector>
#include <memory>


int main(){
    std::vector<Shape*> shapes;
    Circle * c1 = new Circle( 1,{2,3}, VulkanCircleStrategy{} );
    Circle * c2 = new Circle( 2,{0,1}, OpenGLCircleStrategy{} );
    Square * s1 = new Square( 1,{0,0}, VulkanSquareStrategy{} );
    Square * s2 = new Square( 3,{2,3}, OpenGLSquareStrategy{} );
    shapes.push_back(c1); shapes.push_back(s1);
    shapes.push_back(c2); shapes.push_back(s2);
    for(Shape * s : shapes)
        s->draw();
    delete s2; delete s1; delete c2; delete c1;
  return 0;
}
