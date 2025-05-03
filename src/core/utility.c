#include <config.h>
#include <KD/kd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void decompose_float(KDfloat32 f, KDint *sign, KDint *exponent, KDuint *mantissa)
{
    KDuint32 float_as_int;

    memcpy(&float_as_int, &f, sizeof(float_as_int));

    *mantissa = float_as_int & 0x7FFFFF;
    *exponent = float_as_int >> 23 & 0xFF;
    *sign = float_as_int >> 31 & 1;
}

KDfloat32 compose_float(KDuint sign, KDuint exponent, KDuint mantissa)
{
    KDuint32  float_as_int = 0;
    KDfloat32 result;

    float_as_int += mantissa & 0x7FFFFF;
    float_as_int += (exponent & 0xFF) << 23;
    float_as_int += (sign & 1) << 31;

    memcpy(&result, &float_as_int, sizeof(result));
    return result;
}

KDboolean is_digit_for_base(KDchar const ch, KDint base)
{
    switch (ch)
    {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            return KD_TRUE;
        case '8': case '9':
            return base >= 10 ? KD_TRUE : KD_FALSE;
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            return base >= 16 ? KD_TRUE : KD_FALSE;
        default:
            return KD_FALSE;
    }
}

KDint char_to_digit(KDchar ch)
{
    if (ch >= 97) {
        return ch - 97 + 10;
    }
    if (ch >= 65) {
        return ch - 65 + 10;
    }
    return ch - 48;
}

KD_API KDint KD_APIENTRY kdAbs(KDint i)
{
    if (i == KDINT_MIN) {
       return KDINT_MAX;
    }
    return abs(i);
}

KD_API KDfloat32 KD_APIENTRY kdStrtof(const KDchar *s, KDchar **endptr)
{
    KDchar     *pos = (KDchar *)s;
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
    } else if (*pos == '-') {
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
        } else if (mantissa_start_pos[mantissa_length] == '.') {
            point_pos = mantissa_length++;
        } else {
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
    } else if (mantissa_read_length > 11 && point_pos != -1) {
        mantissa_read_length = 11;
    }

    if (point_pos != -1) {
        mantissa_power = point_pos - mantissa_read_length + 1 - number_of_postdecimal_zeros;
    } else {
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
        } else if (*pos == '-') {
            exponent_sign = -1;
            ++pos;
        }
        if ((unsigned)*pos - '0' >= 10) {
            /* No exponent digits -- rewind. */
            pos = rewind;
        } else {
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

    (void) mantissa_power;
    (void) exponent;
    (void) exponent_sign;
    return strtof(s, endptr);
}

KD_API KDint KD_APIENTRY kdStrtol(const KDchar *s, KDchar **endptr, KDint base)
{
    return strtol(s, endptr, base);
}

KD_API KDuint KD_APIENTRY kdStrtoul(const KDchar *s, KDchar **endptr, KDint base)
{
    return strtoul(s, endptr, base);
}

KD_API KDssize KD_APIENTRY kdLtostr(KDchar *buffer, KDsize buflen, KDint number)
{
    KDssize rc = snprintf(buffer, buflen, "%d", number);
    if (rc < 0 || rc >= buflen) {
        return -1;
    }
    return rc;
}

KD_API KDssize KD_APIENTRY kdUltostr(KDchar *buffer, KDsize buflen, KDuint number, KDint base)
{
    const char *format = "";
    switch (base) {
        case 0:
        case 10:
            format = "%u";
            break;
        case 8:
            format = "%o";
            break;
        case 16:
            format = "%x";
            break;
        default:
            return -1;
    }
    KDssize rc = snprintf(buffer, buflen, format, number);
    if (rc < 0 || rc >= buflen) {
        return -1;
    }
    return rc;
}

KD_API KDssize KD_APIENTRY kdFtostr(KDchar *buffer, KDsize buflen, KDfloat32 number)
{
    KDint   sign;
    KDint   exponent;
    KDuint  mantissa;

    decompose_float(number, &sign, &exponent, &mantissa);
    if (exponent == 255)
    {
        if (!mantissa) {

        } else {
            kdStrcpy_s(buffer, 4, "nan");
            return 3;
        }
    }

    KDssize rc = snprintf(buffer, buflen, "%.9g", number);
    if (rc < 0 || rc >= buflen) {
        return -1;
    }
    return rc;
}

KD_API KDint KD_APIENTRY kdCryptoRandom(KDuint8 *buf, KDsize buflen)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdTolower(KDint c)
{
    return tolower(c);
}

KD_API KDint KD_APIENTRY kdToupper(KDint c)
{
    return toupper(c);
}

KD_API KDint KD_APIENTRY kdIslower(KDint c)
{
    return islower(c);
}

KD_API KDint KD_APIENTRY kdIsupper(KDint c)
{
    return isupper(c);
}

KD_API KDint KD_APIENTRY kdIsalpha(KDint c)
{
    return isalpha(c);
}

KD_API KDint KD_APIENTRY kdIsdigit(KDint c)
{
    return isdigit(c);
}

KD_API KDint KD_APIENTRY kdIsspace(KDint c)
{
    return isspace(c);
}

KD_API KDint KD_APIENTRY kdIsprint(KDint c)
{
    return isprint(c);
}

KD_API KDint KD_APIENTRY kdAtoi(const KDchar *str)
{
    return atoi(str);
}

KD_API KDfloat KD_APIENTRY kdAtof(const KDchar *str)
{
    return (KDfloat)atof(str);
}

KD_API KDdouble KD_APIENTRY kdAtod(const KDchar *str)
{
    return atof(str);
}
