#include <config.h>
#include <KD/kd.h>
#include <string.h>

#ifdef _WIN32
    #define strcasecmp      _stricmp
    #define strncasecmp     _strnicmp
#endif

KD_API void *KD_APIENTRY kdMemchr(const void *src, KDint byte, KDsize len)
{
    return memchr(src, byte, len);
}

KD_API KDint KD_APIENTRY kdMemcmp(const void *src1, const void *src2, KDsize len)
{
    return memcmp(src1, src2, len);
}

KD_API void *KD_APIENTRY kdMemcpy(void *buf, const void *src, KDsize len)
{
    return memcpy(buf, src, len);
}

KD_API void *KD_APIENTRY kdMemmove(void *buf, const void *src, KDsize len)
{
    return memmove(buf, src, len);
}

KD_API void *KD_APIENTRY kdMemset(void *buf, KDint byte, KDsize len)
{
    return memset(buf, byte, len);
}

KD_API KDchar *KD_APIENTRY kdStrchr(const KDchar *str, KDint ch)
{
    return strchr(str, ch);
}

KD_API KDint KD_APIENTRY kdStrcmp(const KDchar *str1, const KDchar *str2)
{
    return strcmp(str1, str2);
}

KD_API KDsize KD_APIENTRY kdStrlen(const KDchar *str)
{
    return strlen(str);
}

KD_API KDsize KD_APIENTRY kdStrnlen(const KDchar *str, KDsize maxlen)
{
    for (KDsize i = 0; i < maxlen; ++i) {
        if (!str[i]) {
            return i;
        }
    }
    return maxlen;
}

KD_API KDint KD_APIENTRY kdStrncat_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srcmaxlen)
{
    if (!buflen) {
        return KD_ERANGE;
    }

    KDsize dstlen = kdStrlen(buf);
    KDsize srclen = kdStrnlen(src, srcmaxlen);
    KDchar *ptr = buf + dstlen;
    if (buflen < (dstlen + srclen + 1)) {
        buf[0] = 0;
        return KD_ERANGE;
    }
    for (KDsize i = 0; i < srclen; ++i ) {
        ptr[i] = src[i];
    }
    ptr[srclen] = 0;
    return 0;
}

KD_API KDint KD_APIENTRY kdStrncmp(const KDchar *str1, const KDchar *str2, KDsize maxlen)
{
    return strncmp(str1, str2, maxlen);
}

KD_API KDint KD_APIENTRY kdStrcpy_s(KDchar *buf, KDsize buflen, const KDchar *src)
{
    if (!buflen) {
        return KD_EINVAL;
    }

    for (KDsize i = 0; i < buflen; ++i) {
        buf[i] = src[i];
        if (!src[i]) {
            return 0;
        }
    }
    buf[0] = 0;
    return KD_EINVAL;
}

KD_API KDint KD_APIENTRY kdStrncpy_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srclen)
{
    if (!buflen) {
        return KD_EINVAL;
    }

    if (buflen <= srclen) {
        for (KDsize i = 0; i < buflen; ++i) {
            buf[i] = src[i];
            if (!src[i]) {
                return 0;
            }
        }
        buf[0] = 0;
        return KD_EINVAL;
    }

    for (KDsize i = 0; i < srclen; ++i) {
        buf[i] = src[i];
        if (!src[i]) {
            return 0;
        }
    }
    buf[srclen] = 0;
    return 0;
}

KD_API KDchar *KD_APIENTRY kdStrrchr(const KDchar *str, KDint ch)
{
    return strrchr(str, ch);
}

KD_API KDint KD_APIENTRY kdStrcasecmp(const KDchar *str1, const KDchar *str2)
{
    return strcasecmp(str1, str2);
}

KD_API KDint KD_APIENTRY kdStrncasecmp(const KDchar *str1, const KDchar *str2, KDsize maxlen)
{
    return strncasecmp(str1, str2, maxlen);
}

KD_API KDchar *KD_APIENTRY kdStrcat(KDchar *buf, const KDchar *src)
{
    return strcat(buf, src);
}

KD_API KDchar *KD_APIENTRY kdStrncat(KDchar *buf, const KDchar *src, KDsize maxlen)
{
    return strncat(buf, src, maxlen);
}

KD_API KDchar *KD_APIENTRY kdStrcpy(KDchar *buf, const KDchar *src)
{
    return strcpy(buf, src);
}

KD_API KDchar *KD_APIENTRY kdStrncpy(KDchar *buf, const KDchar *src, KDsize maxlen)
{
    return strncpy(buf, src, maxlen);
}

KD_API KDchar *KD_APIENTRY kdStrtok( KDchar *str, const KDchar *delim)
{
    return strtok(str, delim);
}

KD_API KDchar *KD_APIENTRY kdStrstr(const KDchar *str1, const KDchar *str2)
{
    return strstr(str1, str2);
}

KD_API KDsize KD_APIENTRY kdStrspn(const KDchar *str1, const KDchar *str2)
{
    return strspn(str1, str2);
}

KD_API KDsize KD_APIENTRY kdStrcspn( const KDchar *str1, const KDchar *str2)
{
    return strcspn(str1, str2);
}

KD_API KDchar *KD_APIENTRY kdStrdup(const KDchar *str)
{
    return strdup(str);
}

KD_API KDchar *KD_APIENTRY kdStrndup(const KDchar *str, KDsize maxlen)
{
    KDsize len = kdStrnlen(str, maxlen);
    if (len > maxlen) {
        len = maxlen;
    }
    KDchar *ret = (KDchar *)kdMalloc(len + 1);
    kdStrncpy(ret, str, len);
    ret[len] = '\0';
    return ret;
}
