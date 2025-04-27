#include <config.h>
#include <KD/kd.h>

KD_API KDFile *KD_APIENTRY kdFopen(const KDchar *pathname, const KDchar *mode)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdFclose(KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdFflush(KDFile *file)
{
    return 0;
}

KD_API KDsize KD_APIENTRY kdFread(void *buffer, KDsize size, KDsize count, KDFile *file)
{
    return 0;
}

KD_API KDsize KD_APIENTRY kdFwrite(const void *buffer, KDsize size, KDsize count, KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetc(KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdPutc(KDint c, KDFile *file)
{
    return 0;
}

KD_API KDchar *KD_APIENTRY kdFgets(KDchar *buffer, KDsize buflen, KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdFEOF(KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdFerror(KDFile *file)
{
    return 0;
}

KD_API void KD_APIENTRY kdClearerr(KDFile *file)
{
}

KD_API KDint KD_APIENTRY kdFseek(KDFile *file, KDoff offset, KDfileSeekOrigin origin)
{
    return 0;
}

KD_API KDoff KD_APIENTRY kdFtell(KDFile *file)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdMkdir(const KDchar *pathname)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdRmdir(const KDchar *pathname)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdRename(const KDchar *src, const KDchar *dest)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdRemove(const KDchar *pathname)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdTruncate(const KDchar *pathname, KDoff length)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStat(const KDchar *pathname, struct KDStat *buf)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdFstat(KDFile *file, struct KDStat *buf)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdAccess(const KDchar *pathname, KDint amode)
{
    return 0;
}

KD_API KDDir *KD_APIENTRY kdOpenDir(const KDchar *pathname)
{
    return KD_NULL;
}

KD_API KDDirent *KD_APIENTRY kdReadDir(KDDir *dir)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdCloseDir(KDDir *dir)
{
    return 0;
}

KD_API KDoff KD_APIENTRY kdGetFree(const KDchar *pathname)
{
    return 0;
}
