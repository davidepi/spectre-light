#include "obox.hpp"

OBox::OBox() : Shape(),fbl(0,0,0),fbr(1,0,0),ftl(0,1,0),bbl(0,0,1)
{
    
}

OBox::OBox(Point3* b, Vec3* x, Vec3* y, Vec3* z) : Shape(),
fbl(b->x,b->y,b->z),fbr(x->x,x->y,x->z),ftl(y->x,y->y,y->z),bbl(z->x,z->y,z->z)
{
#ifdef _LOW_LEVEL_CHECKS_ //ensure that the corners are correctly positioned
    bool consistent = true;
    if(fbl.x > fbr.x)
    {
        consistent = false;
        severe("Non-consistent oriented box corners. Rearranging them...");
        swap(&fbl.x,&fbr.x);
    }
    if(fbl.y > ftl.y)
    {
        consistent = false;
        severe("Non-consistent oriented box corners. Rearranging them...");
        swap(&fbl.y,&ftl.y);
    }
    if(fbl.z > bbl.z)
    {
        consistent = false;
        severe("Non-consistent oriented box corners. Rearranging them...");
        swap(&fbl.z,&bbl.z);
    }
    if(!consistent)
    {
        char out[150]; //17+10+105+1(\0)=133. 150 just in case int is more than
                       //10 letters, otherwise it will write outside the buffer
        strcpy(out,"The oriented box "); //17 letters
        sprintf(out+17,"%d",OBox::getID()); //at most 10 letters
        strcat(out," has been modified due to non conistency, thus applying ");
        strcat(out,"transformation could exhibit undetermined effects");//105
        warning(out);
    }
#endif
}

OBox::OBox(Vec3* e, Matrix4* transformation) : Shape(),fbl(0,0,0),fbr(e->x,0,0),
ftl(0,0,e->y),bbl(0,0,e->z)
{
    transformMatrix = transformation;
}

void OBox::recomputeAABB()
{
    const Point3 max(OBox::fbr.x,OBox::ftl.y,OBox::bbl.z);
    OBox::aabb = AABB(&(OBox::fbl),&max);
}

AABB OBox::computeAABB()const
{
    const Point3 max(OBox::fbr.x,OBox::ftl.y,OBox::bbl.z);
    return AABB(&(OBox::fbl),&max);
}

float OBox::surface()const
{
    float xe = fbr.x-fbl.x; //x edge
    float ze = bbl.z-fbl.z; //z edge
    float la = 2*(xe+ze)*(ftl.y-fbl.y); //lateral surface = perimeter * heigth
    return la+2*xe*ze;
}

void OBox::obj2world()
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        severe("Trying to convert a box to world-space with a NULL matrix");
        return;
    }
#endif
    OBox::fbl = (*transformMatrix)*OBox::fbl;
    OBox::fbr = (*transformMatrix)*OBox::fbr;
    OBox::ftl = (*transformMatrix)*OBox::ftl;
    OBox::bbl = (*transformMatrix)*OBox::bbl;
}

void OBox::world2obj()
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        severe("Trying to convert a box to world-space with a NULL matrix");
        return;
    }
#endif
    Matrix4 inv;
    transformMatrix->inverse(&inv);
    OBox::fbl = inv*OBox::fbl;
    OBox::fbr = inv*OBox::fbr;
    OBox::ftl = inv*OBox::ftl;
    OBox::bbl = inv*OBox::bbl;
}

bool OBox::intersect(const Ray* r,float* distance,float* error)const
{
    //TODO: missing implementation
    return false;
}
