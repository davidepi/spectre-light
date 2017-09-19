//Original code by:
//      Francois Panneton and Pierre L'Ecuyer, University of Montreal
//      Makoto Matsumoto, Hiroshima University

//Edited because I need a thread safe version, thus I embedded everything into
//a class

#include "wellrng.hpp"

WELLrng::WELLrng(const unsigned int seed[WELL_R])
{
    WELLrng::state_i = 0;
    for(int i=0;i<WELL_R;i++)
    {
        state[i] = seed[i];
    }
}

float WELLrng::getNumberf()
{
    z0 = state[(state_i+31) & 0x0000001FU];
    z1 = (state[state_i ]) ^ (state[(state_i+3) & 0x0000001FU] ^
                              (state[(state_i+3) & 0x0000001FU]>>8));
    z2 = (state[(state_i+24) & 0x0000001FU] ^
          (state[(state_i+24) & 0x0000001FU]<<(-(-19)))) ^
        (state[(state_i+10) & 0x0000001FU] ^
         (state[(state_i+10) & 0x0000001FU]<<(-(-14))));
    state[state_i ] = z1 ^ z2;
    state[(state_i+31) & 0x0000001FU] = (z0^(z0<<(-(-11)))) ^
    (z1^(z1<<(-(-7)))) ^ (z2^(z2<<(-(-13)))) ;
    state_i = (state_i + 31) & 0x0000001FU;
    return ((float) state[state_i] * 2.32830643653869628906e-10f);
}

double WELLrng::getNumber()
{
    z0 = state[(state_i+31) & 0x0000001FU];
    z1 = (state[state_i ]) ^ (state[(state_i+3) & 0x0000001FU] ^
                              (state[(state_i+3) & 0x0000001FU]>>8));
    z2 = (state[(state_i+24) & 0x0000001FU] ^
          (state[(state_i+24) & 0x0000001FU]<<(-(-19)))) ^
    (state[(state_i+10) & 0x0000001FU] ^
     (state[(state_i+10) & 0x0000001FU]<<(-(-14))));
    state[state_i ] = z1 ^ z2;
    state[(state_i+31) & 0x0000001FU] = (z0^(z0<<(-(-11)))) ^
    (z1^(z1<<(-(-7)))) ^ (z2^(z2<<(-(-13)))) ;
    state_i = (state_i + 31) & 0x0000001FU;
    return ((double) state[state_i] * 2.32830643653869628906e-10f);
}
