#include "texture_bump.hpp"

void TextureBump::bump(const HitPoint& hp)const
{
    hp.normal_s = hp.normal_g;
}
