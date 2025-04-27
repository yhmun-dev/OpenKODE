#include <config.h>
#include <KD/kd.h>

KD_API KDust KD_APIENTRY kdGetTimeUST(void)
{
    return 0;
}

KD_API KDtime KD_APIENTRY kdTime(KDtime *timep)
{
    return 0;
}

KD_API KDTm *KD_APIENTRY kdGmtime_r(const KDtime *timep, KDTm *result)
{
    return KD_NULL;
}

KD_API KDTm *KD_APIENTRY kdLocaltime_r(const KDtime *timep, KDTm *result)
{
    return KD_NULL;
}

KD_API KDust KD_APIENTRY kdUSTAtEpoch(void)
{
    return 0;
}
