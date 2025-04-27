#include <config.h>
#include <KD/KHR_perfcounter.h>

KD_API KDint KD_APIENTRY kdGetNumberOfCountersKHR(void)
{
    return 0;
}

KD_API const KDCounterInfoKHR *KD_APIENTRY kdGetCounterInformationKHR(KDint index)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdActivateCountersKHR(const KDint *indexes, KDint numindexes)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdDeactivateCountersKHR(const KDint *indexes, KDint numindexes)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStartSamplingKHR(void)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdStopSamplingKHR(void)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetCounterValuesKHR(const KDint *indexes, KDint numindexes, KDint64 *values)
{
    return 0;
}