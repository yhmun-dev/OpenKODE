#include <config.h>
#include <KD/KHR_float64.h>
#include <math.h>
#include <stdlib.h>

KD_API KDfloat64KHR KD_APIENTRY kdAcosKHR(KDfloat64KHR x)
{
    return acos(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdAsinKHR(KDfloat64KHR x)
{
    return asin(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdAtanKHR(KDfloat64KHR x)
{
    return atan(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdAtan2KHR(KDfloat64KHR y, KDfloat64KHR x)
{
    return atan2(y, x);
}

KD_API KDfloat64KHR KD_APIENTRY kdCosKHR(KDfloat64KHR x)
{
    return cos(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdSinKHR(KDfloat64KHR x)
{
    return sin(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdTanKHR(KDfloat64KHR x)
{
    return tan(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdExpKHR(KDfloat64KHR x)
{
    return exp(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdLogKHR(KDfloat64KHR x)
{
    return log(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdFabsKHR(KDfloat64KHR x)
{
    return fabs(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdPowKHR(KDfloat64KHR x, KDfloat64KHR y)
{
    return pow(x, y);
}

KD_API KDfloat64KHR KD_APIENTRY kdSqrtKHR(KDfloat64KHR x)
{
    return sqrt(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdCeilKHR(KDfloat64KHR x)
{
    return ceil(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdFloorKHR(KDfloat64KHR x)
{
    return floor(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdRoundKHR(KDfloat64KHR x)
{
    return round(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdInvsqrtKHR(KDfloat64KHR x)
{
    return 1.0 / sqrt(x);
}

KD_API KDfloat64KHR KD_APIENTRY kdFmodKHR(KDfloat64KHR x, KDfloat64KHR y)
{
    return fmod(x, y);
}

KD_API KDfloat64KHR KD_APIENTRY kdStrtodKHR(const KDchar *s, KDchar **endptr)
{
    return strtod(s, endptr);
}
