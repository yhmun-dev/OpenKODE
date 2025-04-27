#include <config.h>
#include <KD/KHR_thread_storage.h>

KD_API KDThreadStorageKeyKHR KD_APIENTRY kdMapThreadStorageKHR(const void * id)
{
    return 0;
}

/* kdSetThreadStorageKHR: Stores thread-local data. */
KD_API KDint KD_APIENTRY kdSetThreadStorageKHR(KDThreadStorageKeyKHR key, void * data)
{
    return 0;
}

KD_API void * KD_APIENTRY kdGetThreadStorageKHR(KDThreadStorageKeyKHR key)
{
    return KD_NULL;
}
