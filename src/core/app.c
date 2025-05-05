#include <config.h>
#include <KD/kd.h>
#include <stdlib.h>

extern void init_locale(void);
extern void init_file(void);
extern void init_tls(void);

extern void deinit_file(void);
extern void deinit_tls(void);

KD_API KD_NORETURN void KD_APIENTRY kdExit(KDint status)
{
#ifdef _WIN32
    _exit(status);
#else
    exit(status);
#endif
}

KD_API KDint KD_APIENTRY kdInit(int argc, char *argv[])
{
    init_locale();
    init_file();
    init_tls();
    kdSetError(0);
    return 0;
}

KD_API void KD_APIENTRY kdDeinit(void)
{
    deinit_tls();
    deinit_file();
}
