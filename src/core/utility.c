#include <config.h>
#include <KD/kd.h>
#include <ctype.h>
#include <stdlib.h>

KD_API KDint KD_APIENTRY kdAbs(KDint i)
{
    if (i == KDINT_MIN) {
       return KDINT_MAX;
    }
    return abs(i);
}

KD_API KDfloat32 KD_APIENTRY kdStrtof(const KDchar *s, KDchar **endptr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStrtol(const KDchar *s, KDchar **endptr, KDint base)
{
    return 0;
}

KD_API KDuint KD_APIENTRY kdStrtoul(const KDchar *s, KDchar **endptr, KDint base)
{
    return 0;
}

KD_API KDssize KD_APIENTRY kdLtostr(KDchar *buffer, KDsize buflen, KDint number)
{
    return 0;
}

KD_API KDssize KD_APIENTRY kdUltostr(KDchar *buffer, KDsize buflen, KDuint number, KDint base)
{
    return 0;
}

KD_API KDssize KD_APIENTRY kdFtostr(KDchar *buffer, KDsize buflen, KDfloat32 number)
{
    return 0;
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
