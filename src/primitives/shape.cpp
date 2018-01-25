//author: Davide Pizzolotto
//license: GNU GPLv3

#include "shape.hpp"

unsigned static int _shape_ID_pool = 1;

Shape::Shape() : id(_shape_ID_pool++)
{

}

unsigned int Shape::get_id()const
{
    return Shape::id;
}

int Shape::get_faces_number()const
{
    return 1;
}

void Shape::get_densities_array(const Matrix4*,float*)const
{
    return;
}
