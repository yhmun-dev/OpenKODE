#include <config.h>
#include <KD/kd.h>

KD_API void *KD_APIENTRY kdMalloc(KDsize size)
{
    return KD_NULL;
}

KD_API void KD_APIENTRY kdFree(void *ptr)
{
}

KD_API void *KD_APIENTRY kdRealloc(void *ptr, KDsize size)
{
    return KD_NULL;
}
