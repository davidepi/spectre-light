//author: Davide Pizzolotto
//license: GNU GPLv3

#include "mesh.hpp"

Mesh::Mesh(unsigned int size)
{
    Mesh::count = 0; //number of triangles added
    Mesh::alloc = size; //number of triangles allocated

    //can't use malloc, vtable pointer would be uninitialized
    Mesh::tris = new Triangle[size];
}

Mesh::~Mesh()
{
    delete[] Mesh::tris;
}

void Mesh::add_triangle(const Point3& a, const Point3& b, const Point3& c,
                        const Normal& n)
{
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.p = a;
    v0.n = n;
    v1.p = b;
    v1.n = n;
    v2.p = c;
    v2.n = n;
    Mesh::add_triangle(&v0, &v1, &v2);
}

void Mesh::add_triangle(const Vertex* a, const Vertex* b, const Vertex* c)
{
    if(Mesh::count == _MAX_TRIS_) //max tris per primitive
    {
        Console.severe(MESSAGE_MAXTRISNUMBER);
    }
    else
    {
        if(Mesh::count == Mesh::alloc) //need to realloc a bigger area
        {
            unsigned int newsize = alloc << 1<_MAX_TRIS_?alloc << 1:_MAX_TRIS_;
            Triangle* tmp = new Triangle[newsize];
            memcpy((void*)tmp, (void*)Mesh::tris, Mesh::count*sizeof(Triangle));
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
        Triangle* tmp = new Triangle[Mesh::count];
        memcpy((void*)tmp, (void*)Mesh::tris, Mesh::count*sizeof(Triangle));
        delete[] Mesh::tris;
        Mesh::tris = tmp;
        Mesh::alloc = Mesh::count;
    }

    //precompute the surface of the mesh and the aabb
    for(unsigned int i = 0; i<count; i++)
    {
        AABB tmp = Mesh::tris[i].compute_AABB();
        aabb.engulf(&tmp);
    }

    bvh.buildTree(Mesh::tris, count);
}

bool Mesh::intersect(const Ray* r, float* distance, HitPoint* h,
                     const MaskBoolean* mask) const
{
    return bvh.intersect(r, distance, h, mask);
}

AABB Mesh::compute_AABB() const
{
    return Mesh::aabb;
}

AABB Mesh::compute_AABB(const Matrix4* trans) const
{
#ifdef DEBUG
    if(trans == NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    const Point3 p0 = *trans*Point3(Mesh::aabb.bounds[0].x,
                                    Mesh::aabb.bounds[0].y,
                                    Mesh::aabb.bounds[0].z);
    const Point3 p1 = *trans*Point3(Mesh::aabb.bounds[1].x,
                                    Mesh::aabb.bounds[0].y,
                                    Mesh::aabb.bounds[0].z);
    const Point3 p2 = *trans*Point3(Mesh::aabb.bounds[1].x,
                                    Mesh::aabb.bounds[1].y,
                                    Mesh::aabb.bounds[0].z);
    const Point3 p3 = *trans*Point3(Mesh::aabb.bounds[0].x,
                                    Mesh::aabb.bounds[1].y,
                                    Mesh::aabb.bounds[0].z);
    const Point3 p4 = *trans*Point3(Mesh::aabb.bounds[0].x,
                                    Mesh::aabb.bounds[0].y,
                                    Mesh::aabb.bounds[1].z);
    const Point3 p5 = *trans*Point3(Mesh::aabb.bounds[1].x,
                                    Mesh::aabb.bounds[0].y,
                                    Mesh::aabb.bounds[1].z);
    const Point3 p6 = *trans*Point3(Mesh::aabb.bounds[1].x,
                                    Mesh::aabb.bounds[1].y,
                                    Mesh::aabb.bounds[1].z);
    const Point3 p7 = *trans*Point3(Mesh::aabb.bounds[0].x,
                                    Mesh::aabb.bounds[1].y,
                                    Mesh::aabb.bounds[1].z);

    const Point3 pmi = min(
            min(min(min(min(min(min(p0, p1), p2), p3), p4), p5), p6), p7);
    const Point3 pma = max(
            max(max(max(max(max(max(p0, p1), p2), p3), p4), p5), p6), p7);
    return AABB(min(pmi, pma), max(pmi, pma));
}

float Mesh::surface() const
{
    float totalArea = 0;
    for(unsigned int i = 0; i<Mesh::count; i++)
    {
        totalArea += tris[i].surface();
    }
    return totalArea;
}

float Mesh::surface(const Matrix4* transform) const
{
    float totalArea = 0;
    for(unsigned int i = 0; i<Mesh::count; i++)
    {
        totalArea += tris[i].surface(transform);
    }
    return totalArea;
}

int Mesh::get_faces_number() const
{
    return Mesh::count;
}

void Mesh::get_densities_array(const Matrix4* transform, float* array) const
{
    float sum = 0;
    for(unsigned int i = 0; i<count; i++)
    {
        sum += tris[i].surface(transform);
        array[i] = sum;
    }
}

void Mesh::sample_point(float r0, float r1, const float* densities, Point3* p,
                        Normal* n) const
{
    //flatten the random value between 0.0 and the total area
    float extSample = lerp(r0, 0.0f, densities[count-1]);

    //divide et impera search
    int start = 0;
    int end = count-1;
    int mid;
    //the sample in the interval [0,1]. After processing the lerp step
    float sample01;

    //limit cases, they generate infinite loops
    //first triangle of the array
    if(extSample<densities[0])
    {
        sample01 = inverse_lerp(extSample, 0, densities[0]);
        tris[0].sample_point(sample01, r1, NULL, p, n);
        return;
    }
    //last triangle of the array
    if(extSample>densities[end-1])
    {
        sample01 = inverse_lerp(extSample-densities[end-1], 0,
                                densities[end]-densities[end-1]);
        tris[end].sample_point(sample01, r1, NULL, p, n);
        return;
    }

    //find the sampled triangle by using cumulative areas (cdf)
    while(true)
    {
        mid = (start+end)/2;
        //mid contains the value
        if(densities[mid]<=extSample && densities[mid+1]>extSample)
            break;
        else if(densities[mid]>extSample)
            end = mid;
        else
            start = mid;
    }

    //sample the triangle
    sample01 = inverse_lerp(extSample-densities[mid], 0,
                            densities[mid+1]-densities[mid]);
    tris[mid].sample_point(sample01, r1, NULL, p, n);
}
