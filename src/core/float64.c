#include <config.h>
#include <KD/KHR_float64.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

extern void decompose_float(KDfloat32 f, KDint *sign, KDint *exponent, KDuint *mantissa);

extern KDfloat32 compose_float(KDuint sign, KDuint exponent, KDuint mantissa);

extern KDboolean is_digit_for_base(KDchar const ch, KDint base);

extern KDint char_to_digit(KDchar ch);

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
    KDchar     *pos = (KDchar*)s;
    KDint       point_pos = -1;
    KDint       base = 10;
    KDint       base_to_i;
    KDint       i;
    KDchar     *mantissa_start_pos;
    KDint       mantissa_length = 0;
    KDint       mantissa_read_length = 0;
    KDchar     *exponent_start_pos = KD_NULL;
    KDint       exponent_length = 0;
    KDint       exponent_sign = 1;
    KDint       exponent = 0;
    KDint       mantissa_sign = 1;
    KDuint64    mantissa = 0;
    KDint       mantissa_power = 0;
    KDint       number_of_postdecimal_zeros = 0;
    KDfloat32   result;

    while (isspace(*pos)) {
        ++pos;
    }

    if (*pos == '+') {
        ++pos;
    }
    else if (*pos == '-') {
        mantissa_sign = -1;
        ++pos;
    }

    /* inf */
    if ((pos[0] == 'i' || pos[0] == 'I') && (pos[1] == 'n' || pos[1] == 'N') && (pos[2] == 'f' || pos[2] == 'F')) {
        pos += 3;
        result = compose_float(mantissa_sign == 1 ? 0 : 1, 0xFF, 0);
        if (endptr) {
            *endptr = pos;
        }
        return result;
    }

    /* nan */
    if ((pos[0] == 'n' || pos[0] == 'N') && (pos[1] == 'a' || pos[1] == 'A') && (pos[2] == 'n' || pos[2] == 'N')) {
        pos += 3;
        result = compose_float(0, 0xFF, 1);
        if (endptr) {
            *endptr = pos;
        }
        return result;
    }

    mantissa_start_pos = pos;
    for (;;) {
        if (is_digit_for_base(mantissa_start_pos[mantissa_length], base)) {
            ++mantissa_length;
        }
        else if (mantissa_start_pos[mantissa_length] == '.') {
            point_pos = mantissa_length++;
        }
        else {
            break;
        }
    }

    /* if no mantissa at all.. */
    if (!mantissa_length) {
        if (endptr) {
            *endptr = (KDchar*)s;
        }
        return 0.0f;
    }

    /* predecimal zeros */
    while (mantissa_start_pos[0] == '0') {
        ++mantissa_start_pos;
        --mantissa_length;
        if (point_pos != -1) {
            --point_pos;
        }
    }

    /* postdecimal zeros */
    if (mantissa_start_pos[0] == '.') {
        while (mantissa_start_pos[1] == '0') {
            ++mantissa_start_pos;
            --mantissa_length;
            ++number_of_postdecimal_zeros;
        }
    }

    mantissa_read_length = mantissa_length;

    /* cap mantissa reading */
    if (mantissa_read_length > 10 && point_pos == -1) {
        mantissa_read_length = 10;
    }
    else if (mantissa_read_length > 11 && point_pos != -1) {
        mantissa_read_length = 11;
    }

    if (point_pos != -1) {
        mantissa_power = point_pos - mantissa_read_length + 1 - number_of_postdecimal_zeros;
    }
    else {
        mantissa_power = -number_of_postdecimal_zeros;
    }

    base_to_i = 1;
    mantissa = 0;
    for (i = mantissa_read_length - 1; i >= 0; --i) {
        if (i != point_pos) {
            mantissa += char_to_digit(mantissa_start_pos[i]) * base_to_i;
            base_to_i *= base;
        }
    }

    pos = mantissa_start_pos + mantissa_length;

    if ((base == 10 && (*pos == 'e' || *pos == 'E')) || (base == 16 && (*pos == 'p' || *pos == 'P'))) {
        KDchar* rewind = pos;
        ++pos;

        if (*pos == '+') {
            ++pos;
        }
        else if (*pos == '-') {
            exponent_sign = -1;
            ++pos;
        }
        if ((unsigned)*pos - '0' >= 10) {
            /* No exponent digits -- rewind. */
            pos = rewind;
        }
        else {
            while (*pos == '0') {
                ++pos;
            }

            exponent_start_pos = pos;

            while (is_digit_for_base(exponent_start_pos[exponent_length], base)) {
                ++exponent_length;
            }

            base_to_i = 1;
            exponent = 0;
            for (i = exponent_length - 1; i >= 0; --i)
            {
                exponent += char_to_digit(exponent_start_pos[i]) * base_to_i;
                base_to_i *= 10;
            }
        }
    }

    if (endptr) {
        *endptr = exponent_start_pos ? exponent_start_pos + exponent_length : pos;
    }

    /* +/- 0 */
    if (mantissa == 0) {
        return mantissa_sign == 1 ? +0.0f : -0.0f;
    }

    (void)mantissa_power;
    (void)exponent;
    (void)exponent_sign;
    return strtod(s, endptr);
}

KD_API KDssize KD_APIENTRY kdDtostrKHR(KDchar* buffer, KDsize buflen, KDfloat64KHR number)
{
    KDint   sign;
    KDint   exponent;
    KDuint  mantissa;

    decompose_float(number, &sign, &exponent, &mantissa);
    if (exponent == 255)
    {
        if (!mantissa) {

        }
        else {
            kdStrcpy_s(buffer, 4, "nan");
            return 3;
        }
    }

    KDssize rc = snprintf(buffer, buflen, "%.18g", number);
    if (rc < 0 || rc >= buflen) {
        return -1;
    }
    return rc;
}

KD_API KDfloat64KHR KD_APIENTRY kdHugeValKHR(void)
{
    return HUGE_VAL;
}
