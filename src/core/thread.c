#include <config.h>
#include <KD/kd.h>
#include <errno.h>

#if HAVE_PTHREAD_H
    #include <pthread.h>
#endif

#if HAVE_SEMAPHORE_H
    #include <semaphore.h>
#endif

KD_API KDThreadAttr *KD_APIENTRY kdThreadAttrCreate(void)
{
    #if HAVE_PTHREAD_H
        pthread_attr_t *attr = (pthread_attr_t *)kdMalloc(sizeof(pthread_attr_t));
        if (!attr) {
            return KD_NULL;
        }
        errno = pthread_attr_init(attr);
        if (errno != 0) {
            kdFree(attr);
            return KD_NULL;
        }
        return (KDThreadAttr *)attr;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadAttrFree(KDThreadAttr *attr)
{
    #if HAVE_PTHREAD_H
        errno = pthread_attr_destroy((pthread_attr_t *)attr);
        kdFree(attr);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadAttrSetDetachState(KDThreadAttr *attr, KDint detachstate)
{
    #if HAVE_PTHREAD_H
        switch (detachstate) {
            case KD_THREAD_CREATE_JOINABLE:
                detachstate = PTHREAD_CREATE_JOINABLE;
                break;
            case KD_THREAD_CREATE_DETACHED:
                detachstate = PTHREAD_CREATE_DETACHED;
                break;
            default:
                kdSetError(KD_EINVAL);
                return -1;
        }
        errno = pthread_attr_setdetachstate((pthread_attr_t *)attr, detachstate);
        if (errno != 0) {
            return -1;
        }
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadAttrSetStackSize(KDThreadAttr *attr, KDsize stacksize)
{
    #if HAVE_PTHREAD_H
        errno = pthread_attr_setstacksize((pthread_attr_t *)attr, stacksize);
        if (errno != 0) {
            return -1;
        }
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDThread *KD_APIENTRY kdThreadCreate(const KDThreadAttr *attr, void *(*start_routine)(void *), void *arg)
{
    #if HAVE_PTHREAD_H
        pthread_t *thread = (pthread_t *)kdMalloc(sizeof(pthread_t));
        if (!attr) {
            return KD_NULL;
        }
        errno = pthread_create(thread, (pthread_attr_t *)attr, start_routine, arg);
        if (errno != 0) {
            kdFree(thread);
            return KD_NULL;
        }
        return (KDThread *)thread;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KD_NORETURN void KD_APIENTRY kdThreadExit(void *retval)
{
    #if HAVE_PTHREAD_H
        pthread_exit(retval);
        return;
    #else
        kdSetError(KD_ENOSYS);
    #endif
}

KD_API KDint KD_APIENTRY kdThreadJoin(KDThread *thread, void **retval)
{
    #if HAVE_PTHREAD_H
        errno = pthread_join(*(pthread_t *)thread, retval);
        if (errno != 0) {
            return -1;
        }
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadDetach(KDThread *thread)
{
    #if HAVE_PTHREAD_H
        errno = pthread_detach(*(pthread_t *)thread);
        if (errno != 0) {
            return -1;
        }
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDThread *KD_APIENTRY kdThreadSelf(void)
{
    #if HAVE_PTHREAD_H
        pthread_t thread = pthread_self();
        // todo: track the value
        (void) thread;
        return KD_NULL;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadOnce(KDThreadOnce *once_control, void (*init_routine)(void))
{
    #if HAVE_PTHREAD_H
        if (!once_control->impl) {
            pthread_once_t *once = kdMalloc(sizeof(pthread_once_t));
            if (!once) {
                return -1;
            }
            // *once = PTHREAD_ONCE_INIT;
            errno = pthread_once(once, init_routine);
            if (errno != 0) {
                kdFree(once);
                return -1;
            }
            once_control->impl = once;
        }
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDThreadMutex *KD_APIENTRY kdThreadMutexCreate(const void *mutexattr)
{
    #if HAVE_PTHREAD_H
        pthread_mutex_t *mutex = (pthread_mutex_t *)kdMalloc(sizeof(pthread_mutex_t));
        if (!mutex) {
            return KD_NULL;
        }
        // *mutex = PTHREAD_MUTEX_INITIALIZER;
        errno = pthread_mutex_init(mutex, (const pthread_mutexattr_t *)mutexattr);
        if (errno != 0) {
            kdFree(mutex);
            return KD_NULL;
        }
        return (KDThreadMutex *)mutex;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadMutexFree(KDThreadMutex *mutex)
{
    #if HAVE_PTHREAD_H
        errno = pthread_mutex_destroy((pthread_mutex_t *)mutex);
        kdFree(mutex);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadMutexLock(KDThreadMutex *mutex)
{
    #if HAVE_PTHREAD_H
        errno = pthread_mutex_lock((pthread_mutex_t *)mutex);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadMutexUnlock(KDThreadMutex *mutex)
{
    #if HAVE_PTHREAD_H
        errno = pthread_mutex_unlock((pthread_mutex_t *)mutex);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDThreadCond *KD_APIENTRY kdThreadCondCreate(const void *attr)
{
    #if HAVE_PTHREAD_H
        pthread_cond_t *cond = (pthread_cond_t *)kdMalloc(sizeof(pthread_cond_t));
        if (!cond) {
            return KD_NULL;
        }
        // *cond = PTHREAD_COND_INITIALIZER;
        errno = pthread_cond_init(cond, (const pthread_condattr_t *)attr);
        if (errno != 0) {
            kdFree(cond);
            return KD_NULL;
        }
        return (KDThreadCond *)cond;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadCondFree(KDThreadCond *cond)
{
    #if HAVE_PTHREAD_H
        errno = pthread_cond_destroy((pthread_cond_t *)cond);
        kdFree(cond);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadCondSignal(KDThreadCond *cond)
{
    #if HAVE_PTHREAD_H
        errno = pthread_cond_signal((pthread_cond_t *)cond);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadCondBroadcast(KDThreadCond *cond)
{
    #if HAVE_PTHREAD_H
        errno = pthread_cond_broadcast((pthread_cond_t *)cond);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadCondWait(KDThreadCond *cond, KDThreadMutex *mutex)
{
    #if HAVE_PTHREAD_H
        errno = pthread_cond_wait((pthread_cond_t *)cond, (pthread_mutex_t *)mutex);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDThreadSem *KD_APIENTRY kdThreadSemCreate(KDuint value)
{
    #if HAVE_SEMAPHORE_H
        sem_t *sem = (sem_t *)kdMalloc(sizeof(sem_t));
        if (!sem) {
            return KD_NULL;
        }
        errno = sem_init(sem, 0, value);
        if (errno != 0) {
            kdFree(sem);
            return KD_NULL;
        }
        return (KDThreadSem *)sem;
    #else
        kdSetError(KD_ENOSYS);
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadSemFree(KDThreadSem *sem)
{
    #if HAVE_SEMAPHORE_H
        errno = sem_destroy((sem_t *)sem);
        kdFree(sem);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadSemWait(KDThreadSem *sem)
{
    #if HAVE_SEMAPHORE_H
        errno = sem_wait((sem_t *)sem);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}

KD_API KDint KD_APIENTRY kdThreadSemPost(KDThreadSem *sem)
{
    #if HAVE_SEMAPHORE_H
        errno = sem_post((sem_t *)sem);
        return 0;
    #else
        kdSetError(KD_ENOSYS);
        return -1;
    #endif
}
