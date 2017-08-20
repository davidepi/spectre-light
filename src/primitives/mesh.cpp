#include "mesh.hpp"

Mesh::Mesh(unsigned int size)
{
    Mesh::count=0; //number of triangles added
    Mesh::alloc=size; //number of triangles allocated

    //can't use malloc, vtable pointer would be uninitialized
    Mesh::tris = new Triangle[size];
    Mesh::area = 0;
}

Mesh::~Mesh()
{
   delete[] Mesh::tris;
}

void Mesh::addTriangle(const Point3 *a, const Point3 *b, const Point3 *c,
                       const Normal *n)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = *a;
    v0.n = *n;
    v1.p = *b;
    v1.n = *n;
    v2.p = *c;
    v2.n = *n;
    Mesh::addTriangle(&v0,&v1,&v2);
}

void Mesh::addTriangle(const Vertex *a, const Vertex *b, const Vertex *c)
{
    if(Mesh::count==_MAX_TRIS_) //max tris per primitive
    {
        Console.warning(MESSAGE_MAXTRISNUMBER);
    }
    else
    {
        if(Mesh::count == Mesh::alloc) //need to realloc a bigger area
        {
            unsigned int newsize = alloc<<1<_MAX_TRIS_?alloc<<1:_MAX_TRIS_;
            Triangle* tmp = new Triangle[newsize];
            memcpy(tmp, Mesh::tris, Mesh::count*sizeof(Triangle));
            delete[] Mesh::tris;
            Mesh::tris = tmp;
            Mesh::alloc = newsize;
        }
        Mesh::tris[Mesh::count].a = *a;
        Mesh::tris[Mesh::count].b = *b;
        Mesh::tris[Mesh::count].c = *c;
        Mesh::count++;
    }
}

void Mesh::finalize()
{
    //shrink memory to fit exactly the number of triangle used
    //just in case the constructor was called with a wrong parameter and the
    //array doubled
    if(Mesh::alloc>Mesh::count)
    {
        Triangle *tmp = new Triangle[Mesh::count];
        memcpy(tmp, Mesh::tris, Mesh::count*sizeof(Triangle));
        delete[] Mesh::tris;
        Mesh::tris = tmp;
        Mesh::alloc = Mesh::count;
    }

    //precompute the surface of the mesh and the aabb
    for(int i=0;i<count;i++)
    {
        Mesh::area += Mesh::tris[i].surface();
        AABB tmp = Mesh::tris[i].computeAABB();
        aabb.engulf(&tmp);
    }

    bvh.buildTree(Mesh::tris,count);
}

bool Mesh::intersect(const Ray* r,float* distance, HitPoint* h)const
{
    return bvh.intersect(r,distance,h);
}

AABB Mesh::computeAABB()const
{
    return Mesh::aabb;
}

AABB Mesh::computeWorldAABB(const Matrix4 *trans) const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(trans==NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    Point3 pmin = *trans * Mesh::aabb.bounds[0];
    Point3 pmax = *trans * Mesh::aabb.bounds[1];
    return AABB(min(pmin,pmax), max(pmin,pmax));
}

float Mesh::surface()const
{
    return Mesh::area;
}

void Mesh::getRandomPoint(float r, float r1, Point3 *p, Normal *n) const
{
    Console.critical("Unimplemented Mesh::getRandomPoint");
}
