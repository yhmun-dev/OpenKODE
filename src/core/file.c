#include <config.h>
#include <KD/kd.h>

static void write_stat(struct KDStat *buf, KDmode st_mode, KDoff st_size, KDtime st_mtime)
{
    buf->st_mode = st_mode;
    buf->st_size = st_size;
    buf->st_mtime = st_mtime;
}

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

#if HAVE_DIRENT_H
    #include <dirent.h>
#endif

#if HAVE_SYS_STATVFS_H
    #include <sys/statvfs.h>
#endif

#if HAVE_UNISTD_H
    #include <unistd.h>
#endif

KD_API KDFile *KD_APIENTRY kdFopen(const KDchar *pathname, const KDchar *mode)
{
    return (KDFile *)fopen(pathname, mode);
}

KD_API KDint KD_APIENTRY kdFclose(KDFile *file)
{
    return fclose((FILE *)file);
}

KD_API KDint KD_APIENTRY kdFflush(KDFile *file)
{
    return fflush((FILE *)file);
}

KD_API KDsize KD_APIENTRY kdFread(void *buffer, KDsize size, KDsize count, KDFile *file)
{
    return fread(buffer, size, count, (FILE *)file);
}

KD_API KDsize KD_APIENTRY kdFwrite(const void *buffer, KDsize size, KDsize count, KDFile *file)
{
    return fwrite(buffer, size, count, (FILE *)file);
}

KD_API KDint KD_APIENTRY kdGetc(KDFile *file)
{
    return fgetc((FILE *)file);
}

KD_API KDint KD_APIENTRY kdPutc(KDint c, KDFile *file)
{
    return fputc(c, (FILE *)file);
}

KD_API KDchar *KD_APIENTRY kdFgets(KDchar *buffer, KDsize buflen, KDFile *file)
{
    return fgets(buffer, buflen, (FILE *)file);
}

KD_API KDint KD_APIENTRY kdFEOF(KDFile *file)
{
    return feof((FILE *)file);
}

KD_API KDint KD_APIENTRY kdFerror(KDFile *file)
{
    return ferror((FILE *)file);
}

KD_API void KD_APIENTRY kdClearerr(KDFile *file)
{
    clearerr((FILE *)file);
}

KD_API KDint KD_APIENTRY kdFseek(KDFile *file, KDoff offset, KDfileSeekOrigin origin)
{
    return fseek((FILE *)file, offset, origin);
}

KD_API KDoff KD_APIENTRY kdFtell(KDFile *file)
{
    return ftell((FILE *)file);
}

KD_API KDint KD_APIENTRY kdMkdir(const KDchar *pathname)
{
    #ifdef _WIN32
        return mkdir(pathname);
    #else
        return mkdir(pathname, S_IRUSR | S_IWUSR | S_IXUSR |
                            S_IRGRP | S_IWGRP |
                            S_IROTH | S_IWOTH);
    #endif
}

KD_API KDint KD_APIENTRY kdRmdir(const KDchar *pathname)
{
    return rmdir(pathname);
}

KD_API KDint KD_APIENTRY kdRename(const KDchar *src, const KDchar *dest)
{
    return rename(src, dest);
}

KD_API KDint KD_APIENTRY kdRemove(const KDchar *pathname)
{
    return remove(pathname);
}

KD_API KDint KD_APIENTRY kdTruncate(const KDchar *pathname, KDoff length)
{
    #if HAVE_TRUNCATE
        return truncate(pathname, length);
    #else
        return 0;
    #endif
}

KD_API KDint KD_APIENTRY kdStat(const KDchar *pathname, struct KDStat *buf)
{
    struct stat s = {};
    KDint rc = stat(pathname, &s);
    if (!rc) {
        write_stat(buf, (KDmode)s.st_mode, s.st_size, s.st_mtime);
    }
    return rc;
}

KD_API KDint KD_APIENTRY kdFstat(KDFile *file, struct KDStat *buf)
{
    KDint fd = kdFileno(file);
    struct stat s = {};
    KDint rc = fstat(fd, &s);
    if (!rc) {
        write_stat(buf, (KDmode)s.st_mode, s.st_size, s.st_mtime);
    }
    return rc;
}

KD_API KDint KD_APIENTRY kdAccess(const KDchar *pathname, KDint amode)
{
    return access(pathname, amode);
}

KD_API KDDir *KD_APIENTRY kdOpenDir(const KDchar *pathname)
{
    #if HAVE_DIRENT_H
        return (KDDir *)opendir(pathname);
    #else
        return KD_NULL;
    #endif
}

KD_API KDDirent *KD_APIENTRY kdReadDir(KDDir *dir)
{
    #if HAVE_DIRENT_H
        return (KDDirent *)readdir((DIR *)dir);
    #else
        return KD_NULL;
    #endif
}

KD_API KDint KD_APIENTRY kdCloseDir(KDDir *dir)
{
    #if HAVE_DIRENT_H
        return closedir((DIR *)dir);
    #else
        return 0;
    #endif
}

KD_API KDoff KD_APIENTRY kdGetFree(const KDchar *pathname)
{
    KDoff off = -1;
    #if HAVE_SYS_STATVFS_H
        struct statvfs info;
        if (!statvfs(pathname, &info)) {
            off = info.f_bavail * info.f_frsize;
        }
    #endif
    return off;
}

KD_API KDint KD_APIENTRY kdFileno(KDFile *file)
{
    return fileno((FILE *)file);
}

KD_API KDint KD_APIENTRY kdUngetc(KDint ch, KDFile *file)
{
    return ungetc(ch, (FILE *)file);
}

KD_API KDssize KD_APIENTRY kdGetline(KDchar **lineptr, KDsize *buflen, KDFile *file)
{
    #ifdef _WIN32
        return 0;
    #else
        return getline(lineptr, buflen, (FILE *)file);
    #endif
}

KD_API KDint KD_APIENTRY kdPuts(const KDchar *str, KDFile *file)
{
    return fputs(str, (FILE *)file);
}

KD_API void KD_APIENTRY kdRewind(KDFile *file)
{
    rewind((FILE *)file);
}

KD_API KDint KD_APIENTRY kdLstat(const KDchar *pathname, struct KDStat *buf)
{
    #ifdef _WIN32
        return 0;
    #else
        struct stat s;
        KDint rc = lstat(pathname, &s);
        if (!rc) {
            write_stat(buf, (KDmode)s.st_mode, s.st_size, s.st_mtime);
        }
        return rc;
    #endif
}

KD_API KDFile *KD_APIENTRY kdFmemopn(void *buf, KDsize size, const KDchar *mode)
{
    #ifdef _WIN32
        return KD_NULL;
    #else
        return (KDFile *)fmemopen(buf, size, mode);
    #endif
}

KD_API KDint KD_APIENTRY kdFgetpos(KDFile *file, KDoff *pos)
{
    return fgetpos((FILE *)file, (fpos_t *)pos);
}

KD_API KDint KD_APIENTRY kdOpen(const KDchar* pathname, KDint flags, KDint mode)
{
    return open(pathname, flags, mode);
}

KD_API KDint KD_APIENTRY kdClose(KDint fd)
{
    return fd;
}

KD_API KDoff KD_APIENTRY kdLseek(KDint fd, KDint position, KDint startpoint)
{
    return lseek(fd, position, startpoint);
}

KD_API KDssize KD_APIENTRY kdRead(KDint fd, void *buf, KDint len)
{
    return read(fd, buf, len);
}

KD_API KDssize KD_APIENTRY kdWrite(KDint fd, void *buf, KDint len)
{
    return write(fd, buf, len);
}

KD_API KDint KD_APIENTRY kdChdir(const KDchar *pathname)
{
    return chdir(pathname);
}

KD_API KDint KD_APIENTRY kdLink(const KDchar *oldfile, const KDchar *newname)
{
    #ifdef _WIN32
        return 0;
    #else
        return link(oldfile, newname);
    #endif
}

KD_API KDint KD_APIENTRY kdUnlink(const KDchar *pathname)
{
    return unlink(pathname);
}

KD_API void KD_APIENTRY kdSync(void)
{
    #ifdef _WIN32
        return;
    #else
        sync();
    #endif
}

KD_API KDint KD_APIENTRY kdIsatty(KDint fd)
{
    return isatty(fd);
}
