#include <config.h>
#include <KD/kd.h>

KD_API KDThreadAttr *KD_APIENTRY kdThreadAttrCreate(void)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadAttrFree(KDThreadAttr *attr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadAttrSetDetachState(KDThreadAttr *attr, KDint detachstate)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadAttrSetStackSize(KDThreadAttr *attr, KDsize stacksize)
{
    return 0;
}

KD_API KDThread *KD_APIENTRY kdThreadCreate(const KDThreadAttr *attr, void *(*start_routine)(void *), void *arg)
{
    return KD_NULL;
}

KD_API KD_NORETURN void KD_APIENTRY kdThreadExit(void *retval)
{
}

KD_API KDint KD_APIENTRY kdThreadJoin(KDThread *thread, void **retval)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadDetach(KDThread *thread)
{
    return 0;
}

KD_API KDThread *KD_APIENTRY kdThreadSelf(void)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadOnce(KDThreadOnce *once_control, void (*init_routine)(void))
{
    return 0;
}

KD_API KDThreadMutex *KD_APIENTRY kdThreadMutexCreate(const void *mutexattr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadMutexFree(KDThreadMutex *mutex)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadMutexLock(KDThreadMutex *mutex)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadMutexUnlock(KDThreadMutex *mutex)
{
    return 0;
}

KD_API KDThreadCond *KD_APIENTRY kdThreadCondCreate(const void *attr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondFree(KDThreadCond *cond)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondSignal(KDThreadCond *cond)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondBroadcast(KDThreadCond *cond)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondWait(KDThreadCond *cond, KDThreadMutex *mutex)
{
    return 0;
}

KD_API KDThreadSem *KD_APIENTRY kdThreadSemCreate(KDuint value)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadSemFree(KDThreadSem *sem)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadSemWait(KDThreadSem *sem)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadSemPost(KDThreadSem *sem)
{
    return 0;
}
