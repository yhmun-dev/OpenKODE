#include <config.h>
#include <KD/kd.h>
#include <errno.h>
#include <string.h>

static int kd2posix(KDint error)
{
    #define CASE_ERR(code) \
        case KD_##code: return code;
    switch (error) {
        CASE_ERR(EACCES);
        CASE_ERR(EADDRINUSE);
        CASE_ERR(EADDRNOTAVAIL);
        CASE_ERR(EAFNOSUPPORT);
        CASE_ERR(EAGAIN);
        CASE_ERR(EALREADY);
        CASE_ERR(EBADF);
        CASE_ERR(EBUSY);
        CASE_ERR(ECONNREFUSED);
        CASE_ERR(ECONNRESET);
        CASE_ERR(EDEADLK);
        CASE_ERR(EDESTADDRREQ);
        CASE_ERR(EEXIST);
        CASE_ERR(EFBIG);
        CASE_ERR(EHOSTUNREACH);
        // case KD_EHOST_NOT_FOUND:
        CASE_ERR(EINVAL);
        CASE_ERR(EIO);
        CASE_ERR(EILSEQ);
        CASE_ERR(EISCONN);
        CASE_ERR(EISDIR);
        CASE_ERR(EMFILE);
        CASE_ERR(ENAMETOOLONG);
        CASE_ERR(ENOENT);
        CASE_ERR(ENOMEM);
        CASE_ERR(ENOSPC);
        CASE_ERR(ENOSYS);
        CASE_ERR(ENOTCONN);
        case KD_ENO_DATA:
            return ENODATA;
        case KD_ENO_RECOVERY:
            return ENOTRECOVERABLE;
        CASE_ERR(EOPNOTSUPP);
        CASE_ERR(EOVERFLOW);
        CASE_ERR(EPERM);
        CASE_ERR(ERANGE);
        CASE_ERR(ETIMEDOUT);
        // case KD_ETRY_AGAIN:
        case 0:
            return 0;
        default:
            return -1;
    }
    #undef CASE_ERR
}

KD_API KDint KD_APIENTRY kdGetError(void)
{
    #define CASE_ERR(code) \
        case code: return KD_##code
    switch (errno) {
        CASE_ERR(EACCES);
        CASE_ERR(EADDRINUSE);
        CASE_ERR(EADDRNOTAVAIL);
        CASE_ERR(EAFNOSUPPORT);
        CASE_ERR(EAGAIN);
        CASE_ERR(EALREADY);
        CASE_ERR(EBADF);
        CASE_ERR(EBUSY);
        CASE_ERR(ECONNREFUSED);
        CASE_ERR(ECONNRESET);
        CASE_ERR(EDEADLK);
        CASE_ERR(EDESTADDRREQ);
        CASE_ERR(EEXIST);
        CASE_ERR(EFBIG);
        CASE_ERR(EHOSTUNREACH);
        // return KD_EHOST_NOT_FOUND;
        CASE_ERR(EINVAL);
        CASE_ERR(EIO);
        CASE_ERR(EILSEQ);
        CASE_ERR(EISCONN);
        CASE_ERR(EISDIR);
        CASE_ERR(EMFILE);
        CASE_ERR(ENAMETOOLONG);
        CASE_ERR(ENOENT);
        CASE_ERR(ENOMEM);
        CASE_ERR(ENOSPC);
        CASE_ERR(ENOSYS);
        CASE_ERR(ENOTCONN);
        case ENODATA:
            return KD_ENO_DATA;
        case ENOTRECOVERABLE:
            return KD_ENO_RECOVERY;
        CASE_ERR(EOPNOTSUPP);
        CASE_ERR(EOVERFLOW);
        CASE_ERR(EPERM);
        CASE_ERR(ERANGE);
        CASE_ERR(ETIMEDOUT);
        // return KD_ETRY_AGAIN;
        case 0:
            return 0;
        default:
            return -1;
    }
    #undef CASE_ERR
}

KD_API void KD_APIENTRY kdSetError(KDint error)
{
    errno = kd2posix(error);
}

KD_API const KDchar *KD_APIENTRY kdStrerror(KDint error)
{
    int e = kd2posix(error);
    return strerror(e);
}
