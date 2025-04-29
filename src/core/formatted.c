#include <config.h>
#include <KD/KHR_formatted.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

KD_API KDint KD_APIENTRY kdSnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdVsnprintfKHR(buf, bufsize, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, KDVaListKHR ap)
{
    return vsnprintf(buf, bufsize, format, *((va_list *)ap));
}

KD_API KDint KD_APIENTRY kdSprintfKHR(KDchar *buf, const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdVsprintfKHR(buf, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsprintfKHR(KDchar *buf, const KDchar *format, KDVaListKHR ap)
{
    return vsprintf(buf, format, *((va_list *)ap));
}

KD_API KDint KD_APIENTRY kdFprintfKHR(KDFile *file, const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdVfprintfKHR(file, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVfprintfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap)
{
    return vfprintf((FILE *)file, format, *((va_list *)ap));
}

KD_API KDint KD_APIENTRY kdLogMessagefKHR(const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdFprintfKHR((KDFile *)stdout, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdSscanfKHR(const KDchar *str, const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdVsscanfKHR(str, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsscanfKHR(const KDchar *str, const KDchar *format, KDVaListKHR ap)
{
    return vsscanf(str, format, *((va_list *)ap));
}

KD_API KDint KD_APIENTRY kdFscanfKHR(KDFile *file, const KDchar *format, ...)
{
    va_list ap;
    va_start(ap, format);
    KDint rc = kdVfscanfKHR(file, format, (KDVaListKHR)&ap);
    va_end(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVfscanfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap)
{
    return vfscanf((FILE *)file, format, *((va_list *)ap));
}
