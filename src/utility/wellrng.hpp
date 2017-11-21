//Created,  19 May 2017
//Last Edit 19 May 2017

/**
 *  \file wellrng.hpp
 *  \brief     Implements the WELL rng
 *  \details   C++ implementation of the WELL pseudo random number generator,
 *             originally published by Francois Panneton and Pierre L'Ecuyer
 *  \version   0.1
 *  \date      19 May 2017
 */


#ifndef __WELLRNG_HPP__
#define __WELLRNG_HPP__

///The number of states of the prng
#define WELL_R 32

/**
 *  \class WELLrng wellrng.hpp "utility/wellrng.hpp"
 *  \brief WELL pseudo random number generator
 *
 *  This class is a wrapper for the WELL pseudo random number generator
 *  developed by Francois Panneton and Pierre L'Ecuyer. The init is embedded
 *  into the class and the generator does not use global variable anymore, thus
 *  it is now thread safe
 */
class WELLrng
{
public:
    
    /** \brief Default constructor
     *
     *  Initialize the prng engine with the given seed
     *
     *  \param[in] seed 128 bytes representing the seed of this prng
     */
    WELLrng(const unsigned int seed[WELL_R]);
    
    ///Default destructor
    ~WELLrng() = default;
    
    /** \brief Generate a random float number
     *
     *  Generate a random number in the range [0.0,1.0] following an uniform
     *  distribution
     *
     *  \return The generated number
     */
    float getNumber();
    
private:
    unsigned int state_i;
    unsigned int state[WELL_R];
    unsigned int z0;
    unsigned int z1;
    unsigned int z2;
};

#endif
