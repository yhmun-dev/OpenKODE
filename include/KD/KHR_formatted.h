
/*******************************************************
 * OpenKODE Core extension: KD_KHR_formatted
 *******************************************************/
/* KD/KHR_formatted.h for OpenKODE Core */
#ifndef __kd_KHR_formatted_h_
#define __kd_KHR_formatted_h_
#include <KD/kd.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

typedef va_list KDVaListKHR;

#define KD_VA_START_KHR(a, x)       va_start(a, x)
#define KD_VA_ARG_INT32_KHR(a)      va_arg(a, KDint32)
#define KD_VA_ARG_INT64_KHR(a)      va_arg(a, KDint64)
#define KD_VA_ARG_FLOAT32_KHR(a)    va_arg(a, KDdouble)
#define KD_VA_ARG_PTR_KHR(a)        va_arg(a, void *)
#define KD_VA_END_KHR(a)            va_end(a)

/* kdSnprintfKHR, kdVsnprintfKHR, kdSprintfKHR, kdVsprintfKHR: Formatted output to a buffer. */
KD_API KDint KD_APIENTRY kdSnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, ...);
KD_API KDint KD_APIENTRY kdVsnprintfKHR(KDchar *buf, KDsize bufsize, const KDchar *format, KDVaListKHR ap);
KD_API KDint KD_APIENTRY kdSprintfKHR(KDchar *buf, const KDchar *format, ...);
KD_API KDint KD_APIENTRY kdVsprintfKHR(KDchar *buf, const KDchar *format, KDVaListKHR ap);

/* kdFprintfKHR, kdVfprintfKHR: Formatted output to an open file. */
KD_API KDint KD_APIENTRY kdFprintfKHR(KDFile *file, const KDchar *format, ...);
KD_API KDint KD_APIENTRY kdVfprintfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap);

/* kdLogMessagefKHR: Formatted output to the platform&#8217;s debug logging facility. */
KD_API KDint KD_APIENTRY kdLogMessagefKHR(const KDchar *format, ...);

/* kdSscanfKHR, kdVsscanfKHR: Read formatted input from a buffer. */
KD_API KDint KD_APIENTRY kdSscanfKHR(const KDchar *str, const KDchar *format, ...);
KD_API KDint KD_APIENTRY kdVsscanfKHR(const KDchar *str, const KDchar *format, KDVaListKHR ap);

/* kdFscanfKHR, kdVfscanfKHR: Read formatted input from a file. */
KD_API KDint KD_APIENTRY kdFscanfKHR(KDFile *file, const KDchar *format, ...);
KD_API KDint KD_APIENTRY kdVfscanfKHR(KDFile *file, const KDchar *format, KDVaListKHR ap);

#ifdef __cplusplus
}
#endif

#endif /* __kd_KHR_formatted_h_ */
