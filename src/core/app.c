#include <config.h>
#include <KD/kd.h>
#include <stdlib.h>

KD_API KD_NORETURN void KD_APIENTRY kdExit(KDint status)
{
    exit(status);
}

KD_API KDint KD_APIENTRY kdInit(int argc, char *argv[])
{
    return 0;
}

KD_API void KD_APIENTRY kdDeinit(void)
{
}
