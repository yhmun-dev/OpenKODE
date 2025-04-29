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

#ifdef __cplusplus
}
#endif

#endif /* __kdext_h_ */
