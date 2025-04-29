#include <config.h>
#include <KD/kd.h>
#include <time.h>

#if HAVE_SYS_TIME_H
    #include <sys/time.h>
#endif

static KDTm * tm2Kd(const struct tm *t, struct KDTm *k)
{
    k->tm_sec   = t->tm_sec;
    k->tm_min   = t->tm_min;
    k->tm_hour  = t->tm_hour;
    k->tm_mday  = t->tm_mday;
    k->tm_mon   = t->tm_mon;
    k->tm_year  = t->tm_year;
    k->tm_wday  = t->tm_wday;
    k->tm_yday  = t->tm_yday;
    k->tm_isdst = t->tm_isdst;
    return k;
}

static struct tm * kd2tm(const struct KDTm *k, struct tm *t)
{
    t->tm_sec   = k->tm_sec;
    t->tm_min   = k->tm_min;
    t->tm_hour  = k->tm_hour;
    t->tm_mday  = k->tm_mday;
    t->tm_mon   = k->tm_mon;
    t->tm_year  = k->tm_year;
    t->tm_wday  = k->tm_wday;
    t->tm_yday  = k->tm_yday;
    t->tm_isdst = k->tm_isdst;
    return t;
}

KD_API KDust KD_APIENTRY kdGetTimeUST(void)
{
    return time(KD_NULL);
}

KD_API KDtime KD_APIENTRY kdTime(KDtime *timep)
{
    return time((time_t *)timep);
}

KD_API KDTm *KD_APIENTRY kdGmtime_r(const KDtime *timep, KDTm *result)
{
    struct tm *t = gmtime((time_t *)timep);
    return tm2Kd(t, result);
}

KD_API KDTm *KD_APIENTRY kdLocaltime_r(const KDtime *timep, KDTm *result)
{
    struct tm* t = localtime((time_t *)timep);
    return tm2Kd(t, result);
}

KD_API KDust KD_APIENTRY kdUSTAtEpoch(void)
{
    // todo: figure out correct definition of this API
    return time(KD_NULL);
}

KD_API KDint KD_APIENTRY kdGettimeofday(struct KDTimeval *tv, struct KDTimezone *tz)
{
    #if HAVE_GETTIMEOFDAY
        struct timeval v;
        struct timezone z;
        KDint rc = gettimeofday(&v, &z);
        if (tv) {
            tv->tv_sec = v.tv_sec;
            tv->tv_usec = v.tv_usec;
        }
        if (tz) {
            tz->tz_minuteswest = z.tz_minuteswest;
            tz->tz_dsttime = z.tz_dsttime;
        }
        return rc;
    #else
        return 0;
    #endif
}

KD_API KDint KD_APIENTRY kdSettimeofday(const struct KDTimeval *tv, const struct KDTimezone *tz)
{
    #if HAVE_SETTIMEOFDAY
        struct timeval v;
        struct timezone z;
        v.tv_sec = tv->tv_sec;
        v.tv_usec = tv->tv_usec;
        z.tz_minuteswest = tz->tz_minuteswest;
        z.tz_dsttime = tz->tz_dsttime;
        return settimeofday(&v, &z);
    #else
        return 0;
    #endif
}

KD_API KDdouble KD_APIENTRY kdDifftime(KDtime end, KDtime beginning)
{
    return difftime((time_t) end, (time_t) beginning);
}

KD_API KDtime KD_APIENTRY kdMktime(struct KDTm *timeptr)
{
    struct tm t;
    kd2tm(timeptr, &t);
    return (KDtime)mktime(&t);
}

KD_API KDtime KD_APIENTRY kdTimegm(struct KDTm *timeptr)
{
    #if HAVE_TIMEGM
        struct tm t;
        kd2tm(timeptr, &t);
        return (KDtime)timegm(&t);
    #else
        return 0;
    #endif
}

KD_API KDsize KD_APIENTRY kdStrftime(KDchar *ptr, KDsize maxsize, const KDchar *format, const struct KDTm *timeptr)
{
    struct tm t;
    kd2tm(timeptr, &t);
    return strftime(ptr, maxsize, format, &t);
}
