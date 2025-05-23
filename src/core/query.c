#include <config.h>
#include <KD/kd.h>

KD_API KDint KD_APIENTRY kdQueryAttribi(KDint attribute, KDint *value)
{
    kdSetError(KD_EINVAL);
    return -1;
}

KD_API const KDchar *KD_APIENTRY kdQueryAttribcv(KDint attribute)
{
    switch (attribute)
    {
        case KD_ATTRIB_VENDOR:
            return VENDOR;
        case KD_ATTRIB_VERSION:
            return VERSION;
        case KD_ATTRIB_PLATFORM:
            return PLATFORM;
        default:
            kdSetError(KD_EINVAL);
            return KD_NULL;
    }
}

KD_API const KDchar *KD_APIENTRY kdQueryIndexedAttribcv(KDint attribute, KDint index)
{
    kdSetError(KD_EINVAL);
    return KD_NULL;
}
