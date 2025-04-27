#include <config.h>
#include <KD/kd.h>

KD_API KDint KD_APIENTRY kdQueryAttribi(KDint attribute, KDint *value)
{
    return 0;
}

KD_API const KDchar *KD_APIENTRY kdQueryAttribcv(KDint attribute)
{
    return KD_NULL;
}

KD_API const KDchar *KD_APIENTRY kdQueryIndexedAttribcv(KDint attribute, KDint index)
{
    return KD_NULL;
}
