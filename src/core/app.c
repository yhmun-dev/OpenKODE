#include <config.h>
#include <KD/kd.h>
#include <KD/KHR_thread_storage.h>
#include <stdlib.h>

KDThreadStorageKeyKHR tls_key;

KD_API KD_NORETURN void KD_APIENTRY kdExit(KDint status)
{
    exit(status);
}

KD_API KDint KD_APIENTRY kdInit(int argc, char *argv[])
{
    (void) kdCreateThreadStorageKHR(&tls_key, KD_NULL);
    return 0;
}

KD_API void KD_APIENTRY kdDeinit(void)
{
    kdDeleteThreadStorageKHR(tls_key);
}
