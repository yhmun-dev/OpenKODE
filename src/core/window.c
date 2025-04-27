#include <config.h>
#ifndef KD_WINDOW_SUPPORTED
#define KD_WINDOW_SUPPORTED
#endif
#include <KD/kd.h>

KD_API KDWindow *KD_APIENTRY kdCreateWindow(EGLDisplay display, EGLConfig config, void *eventuserptr)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdDestroyWindow(KDWindow *window)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSetWindowPropertybv(KDWindow *window, KDint pname, const KDboolean *param)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSetWindowPropertyiv(KDWindow *window, KDint pname, const KDint32 *param)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSetWindowPropertycv(KDWindow *window, KDint pname, const KDchar *param)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetWindowPropertybv(KDWindow *window, KDint pname, KDboolean *param)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetWindowPropertyiv(KDWindow *window, KDint pname, KDint32 *param)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetWindowPropertycv(KDWindow *window, KDint pname, KDchar *param, KDsize *size)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdRealizeWindow(KDWindow *window, EGLNativeWindowType *nativewindow)
{
    return 0;
}
