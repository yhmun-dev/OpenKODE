#include <config.h>
#include <KD/kd.h>
#include <locale.h>

#define LOCALE "en_US"

void init_locale(void)
{
    setlocale(LC_ALL, LOCALE ".UTF-8");
}

KD_API const KDchar *KD_APIENTRY kdGetLocale(void)
{
    return LOCALE;
}
