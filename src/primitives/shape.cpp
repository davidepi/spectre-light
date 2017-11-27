//author: Davide Pizzolotto
//license: GNU GPLv3

#include "shape.hpp"

unsigned static int _shape_ID_pool = 1;

Shape::Shape() : id(_shape_ID_pool++)
{
    
}

unsigned int Shape::getID()const
{
    return Shape::id;
}

int Shape::getNumberOfFaces()const
{
    return 1;
}

void Shape::getDensitiesArray(const Matrix4*,float*)const
{
    return;
}
