#include "shape.hpp"

unsigned static int _shape_ID_pool = 1;

Shape::Shape()
:id(_shape_ID_pool++)
{
    
}

Shape::~Shape()
{
    
}

unsigned int Shape::getID()const
{
    return Shape::id;
}
