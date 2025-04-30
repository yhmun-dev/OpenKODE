#ifndef __kdext_h_
#define __kdext_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

KD_API KDint KD_APIENTRY kdInit(int argc, char *argv[]);

KD_API void KD_APIENTRY kdDeinit(void);

KD_API void *KD_APIENTRY kdCalloc(KDsize num, KDsize size);

KD_API void *KD_APIENTRY kdCalloc(KDsize num, KDsize size);

KD_API KDchar *KD_APIENTRY kdStrrchr(const KDchar *str, KDint ch);

KD_API KDint KD_APIENTRY kdStrcasecmp(const KDchar *str1, const KDchar *str2);

KD_API KDint KD_APIENTRY kdStrncasecmp(const KDchar *str1, const KDchar *str2, KDsize maxlen);

KD_API KDchar *KD_APIENTRY kdStrcat(KDchar *buf, const KDchar *src);

KD_API KDchar *KD_APIENTRY kdStrncat(KDchar *buf, const KDchar *src, KDsize maxlen);

KD_API KDchar *KD_APIENTRY kdStrcpy(KDchar *buf, const KDchar *src);

KD_API KDchar *KD_APIENTRY kdStrncpy(KDchar *buf, const KDchar *src, KDsize maxlen);

KD_API KDchar *KD_APIENTRY kdStrtok(KDchar *str, const KDchar *delim);

KD_API KDchar *KD_APIENTRY kdStrstr(const KDchar *str1, const KDchar *str2);

KD_API KDsize KD_APIENTRY kdStrspn(const KDchar *str1, const KDchar *str2);

KD_API KDsize KD_APIENTRY kdStrcspn( const KDchar *str1, const KDchar *str2);

KD_API KDchar *KD_APIENTRY kdStrdup(const KDchar *str);

KD_API KDchar *KD_APIENTRY kdStrndup(const KDchar *str, KDsize maxlen);

KD_API KDint KD_APIENTRY kdTolower(KDint c);

KD_API KDint KD_APIENTRY kdToupper(KDint c);

KD_API KDint KD_APIENTRY kdIslower(KDint c);

KD_API KDint KD_APIENTRY kdIsupper(KDint c);

KD_API KDint KD_APIENTRY kdIsalpha(KDint c);

KD_API KDint KD_APIENTRY kdIsdigit(KDint c);

KD_API KDint KD_APIENTRY kdIsspace(KDint c);

KD_API KDint KD_APIENTRY kdIsprint(KDint c);

KD_API KDint KD_APIENTRY kdAtoi(const KDchar *str);

KD_API KDfloat KD_APIENTRY kdAtof(const KDchar *str);

KD_API KDdouble KD_APIENTRY kdAtod(const KDchar *str);

KD_API KDint KD_APIENTRY kdFileno(KDFile *file);

KD_API KDint KD_APIENTRY kdUngetc(KDint ch, KDFile *file);

KD_API KDssize KD_APIENTRY kdGetline(KDchar **lineptr, KDsize *buflen, KDFile *file);

KD_API KDint KD_APIENTRY kdPuts(const KDchar *str, KDFile *file);

KD_API void KD_APIENTRY kdRewind(KDFile *file);

KD_API KDint KD_APIENTRY kdLstat(const KDchar *pathname, struct KDStat *buf);

KD_API KDFile *KD_APIENTRY kdFmemopn(void *buf, KDsize size, const KDchar *mode);

KD_API KDint KD_APIENTRY kdFgetpos(KDFile *file, KDoff *pos);

KD_API KDint KD_APIENTRY kdOpen(const KDchar* pathname, KDint flags, KDint mode);

KD_API KDint KD_APIENTRY kdClose(KDint fd);

KD_API KDoff KD_APIENTRY kdLseek(KDint fd, KDint position, KDint startpoint);

KD_API KDssize KD_APIENTRY kdRead(KDint fd, void *buf, KDint len);

KD_API KDssize KD_APIENTRY kdWrite(KDint fd, void *buf, KDint len);

KD_API KDint KD_APIENTRY kdChdir(const KDchar *pathname);

KD_API KDint KD_APIENTRY kdLink(const KDchar *oldfile, const KDchar *newname);

KD_API KDint KD_APIENTRY kdUnlink(const KDchar *pathname);

KD_API void KD_APIENTRY kdSync(void);

KD_API KDint KD_APIENTRY kdIsatty(KDint fd);

typedef struct KDTimeval
{
	KDint32 tv_sec;
	KDint32 tv_usec;
} KDTimeval;

typedef struct KDTimezone
{
    KDint32 tz_minuteswest;
    KDint32 tz_dsttime;
} KDTimezone;

KD_API KDint KD_APIENTRY kdGettimeofday(struct KDTimeval *tv, struct KDTimezone *tz);

KD_API KDint KD_APIENTRY kdSettimeofday(const struct KDTimeval *tv, const struct KDTimezone *tz);

KD_API KDdouble KD_APIENTRY kdDifftime(KDtime end, KDtime beginning);

KD_API KDtime KD_APIENTRY kdMktime(struct KDTm *timeptr);

KD_API KDtime KD_APIENTRY kdTimegm(struct KDTm *timeptr);

KD_API const KDchar* KD_APIENTRY kdStrerror(KDint error);

#ifdef __cplusplus
}
#endif

#endif /* __kdext_h_ */
