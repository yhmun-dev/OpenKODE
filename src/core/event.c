#include <config.h>
#include <KD/kd.h>

KD_API const KDEvent *KD_APIENTRY kdWaitEvent(KDust timeout)
{
    return KD_NULL;
}

KD_API void KD_APIENTRY kdSetEventUserptr(void *userptr)
{
}

KD_API void KD_APIENTRY kdDefaultEvent(const KDEvent *event)
{
}

KD_API KDint KD_APIENTRY kdPumpEvents(void)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdInstallCallback(KDCallbackFunc *func, KDint eventtype, void *eventuserptr)
{
    return 0;
}

KD_API KDEvent *KD_APIENTRY kdCreateEvent(void)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdPostEvent(KDEvent *event)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdPostThreadEvent(KDEvent *event, KDThread *thread)
{
    return 0;
}

KD_API void KD_APIENTRY kdFreeEvent(KDEvent *event)
{
}