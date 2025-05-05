#include <config.h>
#include <KD/KHR_formatted.h>
#include <stdio.h>
#include <stdlib.h>

KD_API KDint KD_APIENTRY kdSnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdVsnprintfKHR(buf, bufsize, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, KDVaListKHR ap)
{
    return vsnprintf(buf, bufsize, format, ap);
}

KD_API KDint KD_APIENTRY kdSprintfKHR(KDchar *buf, const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdVsprintfKHR(buf, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsprintfKHR(KDchar *buf, const KDchar *format, KDVaListKHR ap)
{
    return vsprintf(buf, format, ap);
}

KD_API KDint KD_APIENTRY kdFprintfKHR(KDFile *file, const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdVfprintfKHR(file, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVfprintfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap)
{
    return vfprintf((FILE *)file, format, ap);
}

KD_API KDint KD_APIENTRY kdLogMessagefKHR(const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdFprintfKHR((KDFile *)stdout, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdSscanfKHR(const KDchar *str, const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdVsscanfKHR(str, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVsscanfKHR(const KDchar *str, const KDchar *format, KDVaListKHR ap)
{
    return vsscanf(str, format, ap);
}

KD_API KDint KD_APIENTRY kdFscanfKHR(KDFile *file, const KDchar *format, ...)
{
    KDVaListKHR ap;
    KD_VA_START_KHR(ap, format);
    KDint rc = kdVfscanfKHR(file, format, ap);
    KD_VA_END_KHR(ap);
    return rc;
}

KD_API KDint KD_APIENTRY kdVfscanfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap)
{
    return vfscanf((FILE *)file, format, ap);
}
