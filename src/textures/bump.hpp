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

/**
 * \brief Exposes the interface to perform bump mapping
 *
 *  This class is an interface useful for the creation of the shading normal.
 *  It exposes a single method, bump(), responsible for the shading normal
 *  creation in the passed HitPoint. This method is called by the various
 *  BxDF in order to calculate incoming and outgoing wo and wi vectors.
 */
class Bump
{
public:

    /**
     *  \brief Generates the shading normal
     *
     *  Given an HitPoint, this class updates its shading normal
     * \param[in,out] hp The HitPoint that will hold information useful for
     *  the shading normal calculation and the mutable shading normal that
     *  will be updated
     */
    virtual void bump(const HitPoint* hp) const;
};

#endif
