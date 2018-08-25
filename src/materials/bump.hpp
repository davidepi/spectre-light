//Created,  18 Aug 2018
//Last Edit 20 Aug 2018

/**
 *  \file bump.hpp
 *  \brief     Interface for bump mapping
 *  \details   Class exposing the bump() method interface
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      20 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_BUMP_HPP__
#define __TEXTURE_BUMP_HPP__

#include "primitives/hit_point.hpp"
#include "materials/shading_space.hpp"

/**
 * \brief Exposes the interface to perform bump mapping
 *
 *  This class is an interface useful for the creation of the shading normal.
 *  It exposes a single method, bump(), responsible for the shading normal
 *  creation from the passed HitPoint. This method is called by the various
 *  BxDF in order to calculate incoming and outgoing wo and wi vectors.
 */
class Bump
{
public:

    /**
     *  \brief Default destructor
     */
    virtual ~Bump() = default;

    /**
     *  \brief Generates the shading normal
     *
     *  Given an HitPoint, this class creates its shading space matrix
     *  \param[in] hp The HitPoint that will hold information useful for
     *  the shading normal calculation
     *  \param[out] matrix The ShadingSpace class that will be filled with
     *  the three orthonormal vectors expressing the shading space
     *  \param[out] point The displaced (shading) hit point
     *  \param[out] normal The shading normal
     */
    virtual void bump(const HitPoint* hp, ShadingSpace* matrix, Point3* point,
                      Normal* normal) const;
};

#endif
