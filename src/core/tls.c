#include <config.h>
#include <KD/kd.h>
#include <KD/KHR_thread_storage.h>

extern KDThreadStorageKeyKHR tls_key;

KD_API void *KD_APIENTRY kdGetTLS(void)
{
    return kdGetThreadStorageKHR(tls_key);
}

KD_API void KD_APIENTRY kdSetTLS(void *ptr)
{
    (void) kdSetThreadStorageKHR(tls_key, ptr);
}
