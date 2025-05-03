#include <config.h>
#include <KD/kd.h>
#include <math.h>
#include <string.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

KD_API KDfloat32 KD_APIENTRY kdAcosf(KDfloat32 x)
{
    if (x < -1.f || x > 1.f) {
        return NAN;
    }
    return acosf(x);
}

KD_API KDfloat32 KD_APIENTRY kdAsinf(KDfloat32 x)
{
    if (x < -1.f || x > 1.f) {
        return NAN;
    }
    return asinf(x);
}

KD_API KDfloat32 KD_APIENTRY kdAtanf(KDfloat32 x)
{
    return atanf(x);
}

KD_API KDfloat32 KD_APIENTRY kdAtan2f(KDfloat32 y, KDfloat32 x)
{
    return atan2f(y, x);
}

KD_API KDfloat32 KD_APIENTRY kdCosf(KDfloat32 x)
{
    if (isnan(x) || x == INFINITY || x == -INFINITY) {
        return NAN;
    }
    return cosf(x);
}

KD_API KDfloat32 KD_APIENTRY kdSinf(KDfloat32 x)
{
    if (isnan(x) || x == INFINITY || x == -INFINITY) {
        return NAN;
    }
    return sinf(x);
}

KD_API KDfloat32 KD_APIENTRY kdTanf(KDfloat32 x)
{
    if (x == INFINITY || x == -INFINITY) {
        return NAN;
    }
    return tanf(x);
}

KD_API KDfloat32 KD_APIENTRY kdExpf(KDfloat32 x)
{
    if (isnan(x)) {
        return NAN;
    } else if (x == INFINITY) {
        return INFINITY;
    } else if (x == -INFINITY) {
        return 0;
    }
    return expf(x);
}

KD_API KDfloat32 KD_APIENTRY kdLogf(KDfloat32 x)
{
    if (x == -INFINITY || x == -1.f) {
        return NAN;
    } else if (x == 0) {
        return -INFINITY;
    }
    return logf(x);
}

KD_API KDfloat32 KD_APIENTRY kdFabsf(KDfloat32 x)
{
    return fabsf(x);
}

KD_API KDfloat32 KD_APIENTRY kdPowf(KDfloat32 x, KDfloat32 y)
{
    if (isnan(x) && (isnan(y) || y == INFINITY || y == -INFINITY || y == 1.f || y == -1.f)) {
        return NAN;
    } else if ((x == INFINITY || x == -INFINITY) && isnan(y)) {
        return NAN;
    } else if (isnan(x) && y == 0) {
        return 1.f;
    } else if ((x == -1.f || x == 0) && isnan(y)) {
        return NAN;
    } else if (x == 1.f && isnan(y)) {
        return 1.f;
    } else if (x == 0 && y == -1.f) {
        KDuint32 t;
        memcpy(&t, &x, sizeof(KDuint32));
        return t & 0x80000000 ? -INFINITY : INFINITY;
    } else if (x == -1.f && (y == .5f || y == -.5f)) {
        return NAN;
    }
    return powf(x, y);
}

KD_API KDfloat32 KD_APIENTRY kdSqrtf(KDfloat32 x)
{
    if (isnan(x) || x == -INFINITY || x == -1.f) {
        return NAN;
    } else if (x == INFINITY) {
        return INFINITY;
    }
    return sqrtf(x);
}

KD_API KDfloat32 KD_APIENTRY kdCeilf(KDfloat32 x)
{
    return ceilf(x);
}

KD_API KDfloat32 KD_APIENTRY kdFloorf(KDfloat32 x)
{
    return floorf(x);
}

KD_API KDfloat32 KD_APIENTRY kdRoundf(KDfloat32 x)
{
    return roundf(x);
}

KD_API KDfloat32 KD_APIENTRY kdInvsqrtf(KDfloat32 x)
{
    if (isnan(x) || x == -INFINITY || x == -1.f) {
        return NAN;
    }
    return 1.0f / sqrtf(x);
}

KD_API KDfloat32 KD_APIENTRY kdFmodf(KDfloat32 x, KDfloat32 y)
{
    if ((x == INFINITY || x == -INFINITY) && (isnan(y) || y == 0 || y == 1.f || y == -1.f || y == INFINITY || y == -INFINITY)) {
        return NAN;
    } else if ((x == 0 || x == 1 || x == -1) && y == 0) {
        return NAN;
    }
    return fmodf(x, y);
}

KD_API KDint KD_APIENTRY kdIsNan(KDfloat32 x)
{
    return isnan(x);
}

KD_API KDfloat32 KD_APIENTRY kdInfinity(void)
{
    return INFINITY;
}
