#include "bdf.hpp"
Bdf::Bdf(BdfFlags flags)
{
    Bdf::type = flags;
}

Bdf::~Bdf()
{

}

Color Bdf::df_s(const Vec3 *wo, Vec3 *wi) const
{
    return df(wo,wi);
}