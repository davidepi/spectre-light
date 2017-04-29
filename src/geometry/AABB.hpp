//Created,  25 Feb 2016
//Last Edit 29 Apr 2017

/**
 *  \file aabb.hpp
 *  \brief     AABB class definition and its inline functions
 *  \details   An Axis Aligned Bounding Box, used to enclose some geometry
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      29 April 2017
 *  \copyright GNU GPLv3
 */


#ifndef __AABBOX_HPP__
#define __AABBOX_HPP__
#include "point3.hpp"

class AABB
{
private:
public:
    Point3 bmin;
    Point3 bmax;
    
    AABB();
    AABB(const Point3 p);
    AABB(const Point3* min, const Point3* max);
    
    void expand(float value);
    
    void engulf(const Point3* p1);
    void engulf(const AABB* aabb);
    
    bool overlaps(const AABB* aabb)const;
    bool inside(const Point3* p)const;
    
    float surface()const;
    float volume()const;
    
    int longest_axis();
    
    Vec3 offset(const Point3* p)const;
    
    //♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
    
    AABB operator+(const Point3& p)const;
    void operator+=(const Point3& p);
    AABB operator+(const AABB& aabb)const;
    void operator+=(const AABB& aabb);
    bool operator <   (const AABB& a)const;
    bool operator >   (const AABB& a)const;
    bool operator <=  (const AABB& b)const;
    bool operator >=  (const AABB& b)const;
    bool operator ==  (const AABB& a)const;
    bool operator !=  (const AABB& b)const;
    
    //♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
};

AABB Union(const AABB* aabb, const Point3* p);
AABB Union(const AABB* aabb, const AABB* bbaa);
#endif
