//Created,  23 Jul 2017
//Last Edit 30 Jul 2017

/**
 *  \file occlusion_tester.hpp
 *  \brief Test if a Ray intersects with the expected Asset
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  30 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __OCCLUSION_TESTER_HPP__
#define __OCCLUSION_TESTER_HPP__

#include "utility/scene.hpp"
#include "primitives/asset.hpp"

/**
 * \class OcclusionTester occlusion_tester.hpp "utility/occlusion_tester.hpp"
 * \brief Console logging
 *
 *  This class is used to check if a path between a point and an asset is free
 *  or if there are other asset in between.
 *
 *  If the path is occluded, a simple caching mechanism is used. The class
 *  stores the last occluding asset and the intersection is tested against
 *  this one first. For this reason, as soon as an occlusion is found,
 *  nearby points' occlusion testings will be faster
 */
class OcclusionTester
{
public:

    /** \brief default Constructor
     *
     *  \param[in] s The scene used for the occlusion testing
     */
    OcclusionTester(const Scene* s);

    /** \brief Check if a path is occluded
     *
     *  Given a ray and an expected distance, this method check if the nearest
     *  intersection is less than the expected one
     *
     *  \param[in] r The ray used for the test
     *  \param[in] expected_dist The expected distance of the light
     *  \return true if the first intersection is closer than the light distance
     */
    bool isOccluded(const Ray* r, float* expected_dist);

private:

    //scene
    const Scene* s;

    //test this asset first
    const Asset* lasthit[DEFAULT_BOUNCES];
};


#endif
