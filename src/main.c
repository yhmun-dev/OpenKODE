#include <KD/kd.h>

int main(int argc, char *argv[])
{
    int rc = kdInit(argc, argv);
    if (rc == 0) {
        rc = kdMain(argc, (const KDchar *const *)argv);
    }
    kdDeinit();
    return rc;
}

#ifdef _WIN32
#include <stdlib.h>
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int CmdShow)
{
    return main(__argc, __argv);
}
#endif
