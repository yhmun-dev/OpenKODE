#include <config.h>
#include <KD/KHR_thread_storage.h>

#if HAVE_THREADS_H
    #if defined(_WIN32) && !defined(_Noreturn)
    #define _Noreturn __declspec(noreturn)
    #endif
    #include <threads.h>
#elif HAVE_PTHREAD_H
    #include <pthread.h>
#endif

KD_API KDThreadStorageKeyKHR KD_APIENTRY kdMapThreadStorageKHR(const void * id)
{
    return 0;
}

/* kdSetThreadStorageKHR: Stores thread-local data. */
KD_API KDint KD_APIENTRY kdSetThreadStorageKHR(KDThreadStorageKeyKHR key, void * data)
{
    #if HAVE_THREADS_H
        return tss_set((tss_t){key}, data);
    #elif HAVE_PTHREAD_H
        return pthread_setspecific((pthread_key_t)key, data);
    #endif
    return 0;
}

KD_API void * KD_APIENTRY kdGetThreadStorageKHR(KDThreadStorageKeyKHR key)
{
    #if HAVE_THREADS_H
        return tss_get((tss_t){key});
    #elif HAVE_PTHREAD_H
        return pthread_getspecific((pthread_key_t)key);
    #endif
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdCreateThreadStorageKHR(KDThreadStorageKeyKHR *key, void (*destructor)(void *))
{
    #if HAVE_THREADS_H
        return tss_create((tss_t *)key, destructor);
    #elif HAVE_PTHREAD_H
        return pthread_key_create((pthread_key_t *)key, destructor);
    #endif
    return 0;
}

KD_API void KD_APIENTRY kdDeleteThreadStorageKHR(KDThreadStorageKeyKHR key)
{
    #if HAVE_THREADS_H
        tss_delete((tss_t){key});
        return;
    #elif HAVE_PTHREAD_H
        pthread_key_delete((pthread_key_t)key);
        return;
    #endif
}
