#include <config.h>
#include <KD/kd.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>

static struct {
    DWORD werr;
    int   perr;
} err_list[] = {
    {ERROR_INVALID_FUNCTION     , EINVAL    },  // 1
    {ERROR_FILE_NOT_FOUND       , ENOENT    },  // 2
    {ERROR_PATH_NOT_FOUND       , ENOENT    },  // 3
    {ERROR_TOO_MANY_OPEN_FILES  , EMFILE    },  // 4
    {ERROR_ACCESS_DENIED        , EACCES    },  // 5
    {ERROR_INVALID_HANDLE       , EBADF     },  // 6
    {ERROR_ARENA_TRASHED        , ENOMEM    },  // 7
    {ERROR_NOT_ENOUGH_MEMORY    , ENOMEM    },  // 8
    {ERROR_INVALID_BLOCK        , ENOMEM    },  // 9
    {ERROR_BAD_ENVIRONMENT      , E2BIG     },  // 10
    {ERROR_BAD_FORMAT           , ENOEXEC   },  // 11
    {ERROR_INVALID_ACCESS       , EINVAL    },  // 12
    {ERROR_INVALID_DATA         , EINVAL    },  // 13
    {ERROR_INVALID_DRIVE        , ENOENT    },  // 15
    {ERROR_CURRENT_DIRECTORY    , EACCES    },  // 16
    {ERROR_NOT_SAME_DEVICE      , EXDEV     },  // 17
    {ERROR_NO_MORE_FILES        , ENOENT    },  // 18
    {ERROR_LOCK_VIOLATION       , EACCES    },  // 33
    {ERROR_BAD_NETPATH          , ENOENT    },  // 53
    {ERROR_NETWORK_ACCESS_DENIED, EACCES    },  // 65
    {ERROR_BAD_NET_NAME         , ENOENT    },  // 67
    {ERROR_FILE_EXISTS          , EEXIST    },  // 80
    {ERROR_CANNOT_MAKE          , EACCES    },  // 82
    {ERROR_FAIL_I24             , EACCES    },  // 83
    {ERROR_INVALID_PARAMETER    , EINVAL    },  // 87
    {ERROR_NO_PROC_SLOTS        , EAGAIN    },  // 89
    {ERROR_DRIVE_LOCKED         , EACCES    },  // 108
    {ERROR_BROKEN_PIPE          , EPIPE     },  // 109
    {ERROR_DISK_FULL            , ENOSPC    },  // 112
    {ERROR_INVALID_TARGET_HANDLE, EBADF     },  // 114
    {ERROR_INVALID_HANDLE       , EINVAL    },  // 124
    {ERROR_WAIT_NO_CHILDREN     , ECHILD    },  // 128
    {ERROR_CHILD_NOT_COMPLETE   , ECHILD    },  // 129
    {ERROR_DIRECT_ACCESS_HANDLE , EBADF     },  // 130
    {ERROR_NEGATIVE_SEEK        , EINVAL    },  // 131
    {ERROR_SEEK_ON_DEVICE       , EACCES    },  // 132
    {ERROR_DIR_NOT_EMPTY        , ENOTEMPTY },  // 145
    {ERROR_NOT_LOCKED           , EACCES    },  // 158
    {ERROR_BAD_PATHNAME         , ENOENT    },  // 161
    {ERROR_MAX_THRDS_REACHED    , EAGAIN    },  // 164
    {ERROR_LOCK_FAILED          , EACCES    },  // 167
    {ERROR_ALREADY_EXISTS       , EEXIST    },  // 183
    {ERROR_FILENAME_EXCED_RANGE , ENOENT    },  // 206
    {ERROR_NESTING_NOT_ALLOWED  , EAGAIN    },  // 215
    {ERROR_NOT_ENOUGH_QUOTA     , ENOMEM    }   // 1816
};

void set_win2posix_err(void)
{
    DWORD err = GetLastError();
    KDsize max = sizeof(err_list) / sizeof(err_list[0]);
    for (KDsize i = 0; i < max; ++i)  {
        if (err == err_list[i].werr) {
            errno = err_list[i].perr;
            return;
        }
    }
    if (err >= ERROR_WRITE_PROTECT && err <= ERROR_SHARING_BUFFER_EXCEEDED) {
        errno = EACCES;
    } else if (err >= ERROR_INVALID_STARTING_CODESEG && err <= ERROR_INFLOOP_IN_RELOC_CHAIN) {
        errno = ENOEXEC;
    } else {
        errno = EINVAL;
    }
}
#endif

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
    KDint err = errno;
    switch (err) {
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
        case ENFILE:
            return KD_EMFILE;
        case ENOTDIR:
            return KD_ENOENT;
        case ENOTEMPTY:
            return KD_EEXIST;
        case EROFS:
            return KD_EACCES;
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
