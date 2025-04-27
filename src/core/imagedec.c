#include <config.h>
#include <KD/ATX_imgdec.h>

KD_API KDimageATX KD_APIENTRY kdGetImageInfoATX(const KDchar *pathname)
{
    return KD_NULL;
}

KD_API KDimageATX KD_APIENTRY kdGetImageInfoFromStreamATX(KDFile *file)
{
    return KD_NULL;
}

KD_API KDimageATX KD_APIENTRY kdGetImageATX(const KDchar *pathname, KDint format, KDint flags)
{
    return KD_NULL;
}

KD_API KDimageATX KD_APIENTRY kdGetImageFromStreamATX(KDFile *file, KDint format, KDint flags)
{
    return KD_NULL;
}

KD_API void KD_APIENTRY kdFreeImageATX(KDImageATX image)
{
}

KD_API void *KD_APIENTRY kdGetImagePointerATX(KDImageATX image, KDint attr)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdGetImageIntATX(KDImageATX image, KDint attr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdGetImageLevelIntATX(KDImageATX image, KDint attr, KDint level)
{
    return 0;
}
