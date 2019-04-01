#include "light_sun.hpp"
#include <cmath>

//various tables used for the sun position algorithm

#define L0SIZE 64
#define L1SIZE 34
#define L2SIZE 20
#define L3SIZE 7
#define L4SIZE 3
#define L5SIZE 1
#define B0SIZE 5
#define B1SIZE 2
#define R0SIZE 40
#define R1SIZE 10
#define R2SIZE 6
#define R3SIZE 2
#define R4SIZE 1
#define YSIZE 63

LightSun::LightSun(const Spectrum& intensity, const Ray& sunray, float world_r)
        :Light(intensity), lray(sunray), radius_w(world_r)
{

}

static const uint32_t L0A[L0SIZE] = {
        175347046, 3341656, 34894, 3497, 3418, 3136, 2676, 2343, 1324, 1273,
        1199, 990, 902, 857, 780, 753, 505, 492, 357, 317, 284, 271, 243, 206,
        205, 202, 156, 132, 126, 115, 103, 102, 102, 99, 98, 86, 85, 85, 80, 79,
        75, 74, 74, 70, 62, 61, 57, 56, 56, 52, 52, 51, 49, 41, 41, 39, 37, 37,
        36, 36, 33, 30, 30, 25
};

static const double L0B[L0SIZE] = {
        0, 4.6692568, 4.6261, 2.7441, 2.8289, 3.6277, 4.4181, 6.1352, 0.7425,
        2.0371, 1.1096, 5.233, 2.045, 3.508, 1.179, 2.533, 4.583, 4.205, 2.92,
        5.849, 1.899, 0.315, 0.345, 4.806, 1.869, 2.458, 0.833, 3.411, 1.083,
        0.645, 0.636, 0.976, 4.267, 6.21, 0.68, 5.98, 1.3, 3.67, 1.81, 3.04,
        1.76, 3.5, 4.68, 0.83, 3.98, 1.82, 2.78, 4.39, 3.47, 0.19, 1.33, 0.28,
        0.49, 5.37, 2.4, 6.17, 6.04, 2.57, 1.71, 1.78, 0.59, 0.44, 2.74, 3.16
};

static const double L0C[L0SIZE] = {
        0, 6283.07585, 12566.1517, 5753.3849, 3.5231, 77713.7715, 7860.4194,
        3930.2097, 11506.7698, 529.691, 1577.3435, 5884.927, 26.298, 398.149,
        5223.694, 5507.553, 18849.228, 775.523, 0.067, 11790.629, 796.298,
        10977.079, 5486.778, 2544.314, 5573.143, 6069.777, 213.299, 2942.463,
        20.775, 0.98, 4694.003, 15720.839, 7.114, 2146.17, 155.42, 161000.69,
        6275.96, 71430.7, 17260.15, 12036.46, 5088.63, 3154.69, 801.82, 9437.76,
        8827.39, 7084.9, 6286.6, 14143.5, 6279.55, 12139.55, 1748.02, 5856.48,
        1194.45, 8429.24, 19651.05, 10447.39, 10213.29, 1059.38, 2352.87,
        6812.77, 17789.85, 83996.85, 1349.87, 4690.48
};

static const uint64_t L1A[L1SIZE] = {
        628331966747, 206059, 4303, 425, 119, 109, 93, 72, 68, 67, 59, 56, 45,
        36, 29, 21, 19, 19, 17, 16, 16, 15, 12, 12, 12, 12, 11, 10, 10, 9, 9, 8,
        6, 6
};

static const double L1B[L1SIZE] = {
        0, 2.678235, 2.6351, 1.59, 5.796, 2.966, 2.59, 1.14, 1.87, 4.41, 2.89,
        2.17, 0.4, 0.47, 2.65, 5.34, 1.85, 4.97, 2.99, 0.03, 1.43, 1.21, 2.83,
        3.26, 5.27, 2.08, 0.77, 1.3, 4.24, 2.7, 5.64, 5.3, 2.65, 4.67
};

static const double L1C[L1SIZE] = {
        0, 6283.07585, 12566.1517, 3.523, 26.298, 1577.344, 18849.23, 529.69,
        398.15, 5507.55, 5223.69, 155.42, 796.3, 775.52, 7.11, 0.98, 5486.78,
        213.3, 6275.96, 2544.31, 2146.17, 10977.08, 1748.02, 5088.63, 1194.45,
        4694, 553.57, 6286.6, 1349.87, 242.73, 951.72, 2352.87, 9437.76, 4690.48
};

static const uint32_t L2A[L2SIZE] = {
        52919, 8720, 309, 27, 16, 16, 10, 9, 7, 5, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2
};

static const double L2B[L2SIZE] = {
        0, 1.0721, 0.867, 0.05, 5.19, 3.68, 0.76, 2.06, 0.83, 4.66, 1.03, 3.44,
        5.14, 6.05, 1.19, 6.12, 0.31, 2.28, 4.38, 3.75
};

static const double L2C[L2SIZE] = {
        0, 6283.0758, 12566.152, 3.52, 26.3, 155.42, 18849.23, 77713.77, 775.52,
        1577.34, 7.11, 5573.14, 796.3, 5507.55, 242.73, 529.69, 398.15, 553.57,
        5223.69, 0.98
};

static const uint16_t L3A[L3SIZE] = {
        289, 35, 17, 3, 1, 1, 1
};

static const double L3B[L3SIZE] = {
        5.844, 0, 5.49, 5.2, 4.72, 5.3, 5.97
};

static const double L3C[L3SIZE] = {
        6283.076, 0, 12566.15, 155.42, 3.52, 18849.23, 242.73
};

static const uint8_t L4A[L4SIZE] = {114, 8, 1};
static const double L4B[L4SIZE] = {3.142, 4.13, 3.84};
static const double L4C[L4SIZE] = {0, 6283.08, 12566.15};
static const uint8_t L5A[L5SIZE] = {1};
static const float L5B[L5SIZE] = {3.14f};
static const uint8_t L5C[L5SIZE] = {0};
static const uint16_t B0A[B0SIZE] = {280, 102, 80, 44, 32};
static const double B0B[B0SIZE] = {3.199, 5.422, 3.88, 3.7, 4};
static const double B0C[B0SIZE] = {84334.662, 5507.553, 5223.69, 2352.87,
                                   1577.34};
static const uint8_t B1A[B1SIZE] = {9, 6};
static const double B1B[B1SIZE] = {3.9, 1.73};
static const double B1C[B1SIZE] = {5507.55, 5223.69};
static const uint32_t R0A[R0SIZE] = {
        100013989, 1670700, 13956, 3084, 1628, 1576, 925, 542, 472, 346, 329,
        307, 243, 212, 186, 175, 110, 98, 86, 86, 65, 63, 57, 56, 49, 47, 45,
        43, 39, 38, 37, 37, 36, 35, 33, 32, 32, 28, 28, 26
};
static const double R0B[R0SIZE] = {
        0, 3.0984635, 3.05525, 5.1985, 1.1739, 2.8469, 5.453, 4.564, 3.661,
        0.964, 5.9, 0.299, 4.273, 5.847, 5.022, 3.012, 5.055, 0.89, 5.69, 1.27,
        0.27, 0.92, 2.01, 5.24, 3.25, 2.58, 5.54, 6.01, 5.36, 2.39, 0.83, 4.9,
        1.67, 1.84, 0.24, 0.18, 1.78, 1.21, 1.9, 4.59
};
static const double R0C[R0SIZE] = {
        0, 6283.07585, 12566.1517, 77713.7715, 5753.3849, 7860.4194, 11506.77,
        3930.21, 5884.927, 5507.553, 5223.694, 5573.143, 11790.629, 1577.344,
        10977.079, 18849.228, 5486.778, 6069.78, 15720.84, 161000.69, 17260.15,
        529.69, 83996.85, 71430.7, 2544.31, 775.52, 9437.76, 6275.96, 4694,
        8827.39, 19651.05, 12139.55, 12036.46, 2942.46, 7084.9, 5088.63, 398.15,
        6286.6, 6279.55, 10447.39
};
static const uint32_t R1A[R1SIZE] = {
        103019, 1721, 702, 32, 31, 25, 18, 10, 9, 9
};
static const double R1B[R1SIZE] = {
        1.10749, 1.0644, 3.142, 1.02, 2.84, 1.32, 1.42, 5.91, 1.42, 0.27
};
static const double R1C[R1SIZE] = {
        6283.07585, 12566.1517, 0, 18849.23, 5507.55, 5223.69, 1577.34,
        10977.08, 6275.96, 5486.78
};
static const uint16_t R2A[R2SIZE] = {4359, 124, 12, 9, 6, 3};
static const double R2B[R2SIZE] = {5.7846, 5.579, 3.14, 3.63, 1.87, 5.47};
static const double R2C[R2SIZE] = {6283.0758, 12566.152, 0, 77713.77, 5573.14,
                                   18849.23};
static const uint8_t R3A[R3SIZE] = {145, 7};
static const double R3B[R3SIZE] = {4.273, 3.92};
static const double R3C[R3SIZE] = {6283.076, 12566.15};
static const uint8_t R4A[R4SIZE] = {4};
static const double R4B[R4SIZE] = {2.56};
static const double R4C[R4SIZE] = {6283.08};
static const int8_t Y0[YSIZE] = {
        0, -2, 0, 0, 0, 0, -2, 0, 0, -2, -2, -2, 0, 2, 0, 2, 0, 0, -2, 0, 2, 0,
        0, -2, 0, -2, 0, 0, 2, -2, 0, -2, 0, 0, 2, 2, 0, -2, 0, 2, 2, -2, -2, 2,
        2, 0, -2, -2, 0, -2, -2, 0, -1, -2, 1, 0, 0, -1, 0, 0, 2, 0, 2
};
static const int8_t Y1[YSIZE] = {
        0, 0, 0, 0, 1, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 0, 2, 1, 0, -1, 0, 0, 0, 1, 1, -1, 0, 0, 0, 0, 0, 0, -1, -1,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 1, -1, -1, 0, -1
};
static const int8_t Y2[YSIZE] = {
        0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, -1, 0, 1, -1, -1, 1, 2, -2, 0, 2, 2,
        1, 0, 0, -1, 0, -1, 0, 0, 1, 0, 2, -1, 1, 0, 1, 0, 0, 1, 2, 1, -2, 0, 1,
        0, 0, 2, 2, 0, 1, 1, 0, 0, 1, -2, 1, 1, 1, -1, 3, 0
};
static const int8_t Y3[YSIZE] = {
        0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 0, 2, 0, 2, 2, 2, 0, 2,
        2, 2, 2, 0, 0, 2, 0, 0, 0, -2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 0,
        2, 0, 2, -2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2
};
static const int8_t Y4[YSIZE] = {
        1, 2, 2, 2, 0, 0, 2, 1, 2, 2, 0, 1, 2, 0, 1, 2, 1, 1, 0, 1, 2, 2, 0, 2,
        0, 0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 2, 2, 0, 2, 1, 0, 2, 1, 1, 1, 0, 1, 1,
        1, 1, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2,
};
static const int32_t NUT_A[YSIZE] = {
        -171996, -13187, -2274, 2062, 1426, 712, -517, -386, -301, 217, -158,
        129, 123, 63, 63, -59, -58, -51, 48, 46, -38, -31, 29, 29, 26, -22, 21,
        17, 16, -16, -15, -13, -12, 11, -10, -8, 7, -7, -7, -7, 6, 6, 6, -6, -6,
        5, -5, -5, -5, 4, 4, 4, -4, -4, -4, 3, -3, -3, -3, -3, -3, -3, -3
};
static const double NUT_B[YSIZE] = {
        -174.2, -1.6, -0.2, 0.2, -3.4, 0.1, 1.2, -0.4, 0, -0.5, 0, 0.1, 0, 0,
        0.1, 0, -0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.1, 0, 0.1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0
};
static const int32_t NUT_C[YSIZE] = {
        92025, 5736, 977, -895, 54, -7, 224, 200, 129, -95, 0, -70, -53, 0, -33,
        26, 32, 27, 0, -24, 16, 13, 0, -12, 0, 0, -10, 0, -8, 7, 9, 7, 6, 0, 5,
        3, -3, 0, 3, 3, 0, -3, -3, 3, 3, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
};
static const double NUT_D[YSIZE] = {
        8.9, -3.1, -0.5, 0.5, -0.1, 0, -0.6, 0, -0.1, 0.3, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/**
 *  \brief Convert any angle to the (0, 2π) interval
 */
static inline double zero_to_2pi(double radians)
{
    radians = fmod(radians, 2*M_PI);
    if(radians<0)
        radians += 2*M_PI;
    return radians;
}

/**
 *  \brief Convert any angle to the (0, 360) interval
 */
static inline double zero_to_360(double degrees)
{
    degrees = fmod(degrees, 360);
    if(degrees<0)
        degrees += 360.0;
    return degrees;
}

LightSun::LightSun(const Spectrum& intensity, const Point3* world_centre,
                   float world_rad, Date time, float latitude,
                   float longitude, float altitude)
        :Light(intensity), radius_w(world_rad)
{
    /*
     * Solar Position Algorithm, implemented following the paper:
     *
     * Reda, I.; Andreas, A., Solar Position Algorithm for Solar Radiation
     * Applications, Solar Energy. Vol. 76(5), 2004; pp. 577-589
     */

    //Variable naming is the same as the one used in the aforementioned paper

    constexpr const double INV86400 = 1.0/(24*60*60);
    constexpr const double INV36525 = 1.0/36525.0;
    constexpr const double INV10_8 = 1.0/100000000;

    //Julian day
    const double JD = time.get_julian_date();
    //Julian Ephemeris Day
    const double JDE = JD+time.get_delta_t()*INV86400;
    //Julian Century
    const double JC = (JD-2451545)*INV36525;
    //Julian Ephemeris Century
    const double JCE = (JDE-2451545)*INV36525;
    //Julian Ephemeris Millennium
    const double JME = JCE/10.0;
    //Earth Heliocentric Longitude -> (L_RAD, l_deg)
    double l0 = 0.f;
    double l1 = 0.f;
    double l2 = 0.f;
    double l3 = 0.f;
    double l4 = 0.f;
    double l5 = 0.f;
    for(int i = 0; i<L0SIZE; i++)
        l0 += L0A[i]*cos(L0B[i]+L0C[i]*JME);
    for(int i = 0; i<L1SIZE; i++)
        l1 += L1A[i]*cos(L1B[i]+L1C[i]*JME);
    for(int i = 0; i<L2SIZE; i++)
        l2 += L2A[i]*cos(L2B[i]+L2C[i]*JME);
    for(int i = 0; i<L3SIZE; i++)
        l3 += L3A[i]*cos(L3B[i]+L3C[i]*JME);
    for(int i = 0; i<L4SIZE; i++)
        l4 += L4A[i]*cos(L4B[i]+L4C[i]*JME);
    for(int i = 0; i<L5SIZE; i++)
        l5 += L5A[i]*cos(L5B[i]+L5C[i]*JME);
    const double L_RAD =
            zero_to_2pi((l0+l1*JME+l2*JME*JME+l3*JME*JME*JME+l4*JME*JME*JME*JME+
                         l5*JME*JME*JME*JME*JME)*INV10_8);

    //Earth Heliocentric Latitude (B_RAD, b_deg)
    double b0 = 0.f;
    double b1 = 0.f;
    for(int i = 0; i<B0SIZE; i++)
        b0 += B0A[i]*cos(B0B[i]+B0C[i]*JME);
    for(int i = 0; i<B1SIZE; i++)
        b1 += B1A[i]*cos(B1B[i]+B1C[i]*JME);
    const double B_RAD = (b0+b1*JME)*INV10_8;
    //Earth Radius Vector R (measured in AU)
    double r0 = 0.f;
    double r1 = 0.f;
    double r2 = 0.f;
    double r3 = 0.f;
    double r4 = 0.f;
    for(int i = 0; i<R0SIZE; i++)
        r0 += R0A[i]*cos(R0B[i]+R0C[i]*JME);
    for(int i = 0; i<R1SIZE; i++)
        r1 += R1A[i]*cos(R1B[i]+R1C[i]*JME);
    for(int i = 0; i<R2SIZE; i++)
        r2 += R2A[i]*cos(R2B[i]+R2C[i]*JME);
    for(int i = 0; i<R3SIZE; i++)
        r3 += R3A[i]*cos(R3B[i]+R3C[i]*JME);
    for(int i = 0; i<R4SIZE; i++)
        r4 += R4A[i]*cos(R4B[i]+R4C[i]*JME);
    const double R =
            (r0+r1*JME+r2*JME*JME+r3*JME*JME*JME+r4*JME*JME*JME*JME)*INV10_8;
    //Earth Geocentric Longitude
    const double THETA_RAD = zero_to_2pi(L_RAD+M_PI);
    //Earth Geocentric Latitude
    const double BETA_RAD = -B_RAD;
    //Nutation in longitude and obliquity
    const double JCE2 = JCE*JCE;
    const double JCE3 = JCE2*JCE;
    constexpr const double INV189474 = 1.0/189474.0;
    constexpr const double INV300000 = 1.0/300000.0;
    constexpr const double INV56250 = 1.0/56250.0;
    constexpr const double INV327270 = 1.0/327270.0;
    constexpr const double INV450000 = 1.0/450000.0;
    double x[5] = {
            297.85036+445267.111480*JCE-0.0019142*JCE2+JCE3*INV189474,
            357.52772+35999.050340*JCE-0.0001603*JCE2-JCE3*INV300000,
            134.96298+477198.867398*JCE+0.0086972*JCE2+JCE3*INV56250,
            93.27191+483202.017538*JCE-0.0036825*JCE2+JCE3*INV327270,
            125.04452-1934.136261*JCE+0.0020708*JCE2+JCE3*INV450000
    };
    double delta_psi_deg = 0.f;
    double delta_epsilon_deg = 0.f;
    constexpr const double INV36000000 = 1.0/36000000.0;
    for(int i = 0; i<YSIZE; i++)
    {
        double s_term = x[0]*Y0[i]+x[1]*Y1[i]+x[2]*Y2[i]+x[3]*Y3[i]+x[4]*Y4[i];
        s_term = radians(s_term);
        delta_psi_deg += (NUT_A[i]+NUT_B[i]*JCE)*sin(s_term);
        delta_epsilon_deg += (NUT_C[i]+NUT_D[i]*JCE)*cos(s_term);
    }
    delta_psi_deg *= INV36000000;
    delta_epsilon_deg *= INV36000000;
    //True Obliquity
    constexpr const double INV3600 = 1.0/3600.0;
    const double U = JME*0.1;
    double epsilon_deg =
            84381.448-4680.93*U-1.55*U*U+1999.25*U*U*U-51.38*U*U*U*U-
            249.67*U*U*U*U*U-39.05*U*U*U*U*U*U+7.12*U*U*U*U*U*U*U+
            27.87*U*U*U*U*U*U*U*U+5.79*U*U*U*U*U*U*U*U*U+
            2.45*U*U*U*U*U*U*U*U*U*U;
    epsilon_deg *= INV3600;
    epsilon_deg += delta_epsilon_deg;
    //Aberration correction
    const double INV_R = 1.0/R;
    const double DELTA_TAU_DEG = -20.4898*INV3600*INV_R;
    //Apparent sun longitude
    const double THETA_DEG = degrees(THETA_RAD);
    const double LAMBDA_DEG = THETA_DEG+delta_psi_deg+DELTA_TAU_DEG;
    //Mean Sidereal Time at Greenwich
    constexpr const double INV38710000 = 1.0/38710000.0;
    double v_deg = 280.46061837+360.98564736629*(JD-2451545)+0.000387933*JC*JC-
                   JC*JC*JC*INV38710000;
    v_deg = zero_to_360(v_deg);
    //Apparent Sidereal Time at Greenwich
    const double EPSILON_RAD = radians(epsilon_deg);
    v_deg += delta_psi_deg*cos(EPSILON_RAD);
    //Geocentric Sun Right Ascension
    const double LAMBDA_RAD = radians(LAMBDA_DEG);
    const double ALPHA_RAD = zero_to_2pi(atan2(
            sin(LAMBDA_RAD)*cos(EPSILON_RAD)-tan(BETA_RAD)*sin(EPSILON_RAD),
            cos(LAMBDA_RAD)));
    const double ALPHA_DEG = degrees(ALPHA_RAD);
    //Geocentric Sun Declination
    const double DELTA_RAD = asin(sin(BETA_RAD)*cos(EPSILON_RAD)+
                                  cos(BETA_RAD)*sin(EPSILON_RAD)*
                                  sin(LAMBDA_RAD));
    //Observer Local Hour Angle (westward from south)
    const double H_DEG = zero_to_360(v_deg+longitude-ALPHA_DEG);
    //Equatorial Horizontal Parallax
    const double XI_DEG = 8.794*INV3600*INV_R;
    //Topocentric sun right ascension
    constexpr const double INV6378140 = 1.0/6378140.0;
    const double LAT_RAD = radians(latitude);
    const double U_RAD = atan(0.99664719*tan(LAT_RAD));
    const double X_RAD = cos(U_RAD)+altitude*INV6378140*cos(LAT_RAD);
    const double Y_RAD =
            0.99664719*sin(U_RAD)+altitude*INV6378140*sin(LAT_RAD);
    const double XI_RAD = radians(XI_DEG);
    const double H_RAD = radians(H_DEG);
    const double DELTA_ALPHA_RAD = atan2(-X_RAD*sin(XI_RAD)*sin(H_RAD),
                                         cos(DELTA_RAD)-
                                         X_RAD*sin(XI_RAD)*cos(H_RAD));
    //Topocentric sun declination
    const double DELTA1_RAD = atan2((sin(DELTA_RAD)-Y_RAD*sin(XI_RAD))*cos
            (DELTA_ALPHA_RAD), cos(DELTA_RAD)-X_RAD*sin(XI_RAD)*cos(H_RAD));
    //Topocentric local hour angle
    const double H1_RAD = H_RAD-DELTA_ALPHA_RAD;
    //Topocentric elevation angle (without atmospheric correction)
    const double E0_RAD = asin(sin(LAT_RAD)*sin(DELTA1_RAD)+
                               cos(LAT_RAD)*cos(DELTA1_RAD)*cos(H1_RAD));
    //Topocentric zenith angle
    //Topocentric azimuth angle (westward from south)
    const double GAMMA_RAD = zero_to_2pi(atan2(sin(H1_RAD),
                                               cos(H1_RAD)*sin(LAT_RAD)-
                                               tan(DELTA1_RAD)*cos(LAT_RAD)));
    //Topocentric azimuth angle (eastward from north)
    const double PHI_RAD = GAMMA_RAD+M_PI;


    //finally set up directions
    //sun position with world_rad 1
    float azimuth = zero_to_2pi(PHI_RAD);
    float elevation = zero_to_2pi(E0_RAD);
    Point3 sunpos((float)cos(azimuth)*world_rad,
                  (float)sin(elevation)*world_rad,
                  (float)sin(azimuth)*world_rad);
    //find the opposite of the direction
    Vec3 reverse_dir = (sunpos-Point3(0, 0, 0)).normalize();
    Ray reverse_ray(*world_centre, reverse_dir);
    //find a position for the sun outside of the world
    lray.origin = reverse_ray.apply(2*world_rad+1);
    lray.direction = -reverse_dir;
}

Spectrum
LightSun::sample_surface(float, float, float, float, Ray* out,
                         float* pdf) const
{
    *out = LightSun::lray;
    *pdf = 1.f;
    return LightSun::c;
}

Spectrum
LightSun::sample_visible_surface(float, float, const Point3*,
                                 Vec3* wiW, float* pdf, float* distance) const
{
    *wiW = -LightSun::lray.direction;
    *pdf = 1.f;
    *distance = 2*LightSun::radius_w+1;
    return LightSun::c;
}

float LightSun::pdf(const Ray*) const
{
    return 1.f;
}

float LightSun::pdf(const Point3*, const Vec3*) const
{
    return 0.f;
}

bool LightSun::renderable() const
{
    return false;
}