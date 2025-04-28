#include <config.h>
#include <KD/kd.h>
#include <stdlib.h>

KD_API void *KD_APIENTRY kdMalloc(KDsize size)
{
    void *mem = malloc(size);
    if (!mem) {
        kdSetError(KD_ENOMEM);
    }
    return mem;
}

KD_API void KD_APIENTRY kdFree(void *ptr)
{
    free(ptr);
}

KD_API void *KD_APIENTRY kdRealloc(void *ptr, KDsize size)
{
    void *mem = realloc(ptr, size);
    if (!mem) {
        kdSetError(KD_ENOMEM);
    }
    return mem;
}

KD_API void *KD_APIENTRY kdCalloc(KDsize num, KDsize size)
{
    void *mem = calloc(num, size);
    if (!mem) {
        kdSetError(KD_ENOMEM);
    }
    return mem;
}
