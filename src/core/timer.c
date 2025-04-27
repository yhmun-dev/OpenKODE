#include <config.h>
#include <KD/kd.h>

KD_API KDTimer *KD_APIENTRY kdSetTimer(KDint64 interval, KDint periodic, void *eventuserptr)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdCancelTimer(KDTimer *timer)
{
    return 0;
}
