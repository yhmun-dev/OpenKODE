#include <config.h>
#include <KD/kd.h>

KD_API void *KD_APIENTRY kdMemchr(const void *src, KDint byte, KDsize len)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdMemcmp(const void *src1, const void *src2, KDsize len)
{
    return 0;
}

KD_API void *KD_APIENTRY kdMemcpy(void *buf, const void *src, KDsize len)
{
    return KD_NULL;
}

KD_API void *KD_APIENTRY kdMemmove(void *buf, const void *src, KDsize len)
{
    return KD_NULL;
}

KD_API void *KD_APIENTRY kdMemset(void *buf, KDint byte, KDsize len)
{
    return KD_NULL;
}

KD_API KDchar *KD_APIENTRY kdStrchr(const KDchar *str, KDint ch)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdStrcmp(const KDchar *str1, const KDchar *str2)
{
    return 0;
}

KD_API KDsize KD_APIENTRY kdStrlen(const KDchar *str)
{
    return 0;
}

KD_API KDsize KD_APIENTRY kdStrnlen(const KDchar *str, KDsize maxlen)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStrncat_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srcmaxlen)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStrncmp(const KDchar *str1, const KDchar *str2, KDsize maxlen)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStrcpy_s(KDchar *buf, KDsize buflen, const KDchar *src)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStrncpy_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srclen)
{
    return 0;
}
