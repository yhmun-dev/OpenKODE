#include <config.h>
#include <KD/kd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_SYS_STATVFS_H
    #include <sys/statvfs.h>
#endif

#if HAVE_UNISTD_H
    #include <unistd.h>
#endif

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>

    extern void set_win2posix_err(void);
#endif

#if HAVE_DIRENT_H
    #include <dirent.h>

    struct KDDir
    {
        DIR            *dir;
        KDDirent        dirent;
    };
#elif _WIN32
    struct KDDir
    {
        HANDLE          handle;
        WIN32_FIND_DATA data;
        KDDirent        dirent;
    };
#endif

static void write_stat(struct KDStat *buf, KDmode st_mode, KDoff st_size, KDtime st_mtime)
{
    buf->st_mode  = st_mode;
    buf->st_size  = st_size;
    buf->st_mtime = st_mtime;
}

#include <fcntl.h>
#include <sys/stat.h>

enum {
    e_res    = 0,
    e_data      ,
    e_removal   ,
    e_tmp       ,
    e_root      ,
    e_max       ,
};

static KDchar *v_paths[e_max] = {
    "/res",
    "/data",
    "/removal",
    "/tmp",
    "/"
};

static KDchar *r_paths[e_max] = {};

void deinit_file(void)
{
    for (KDint i = 0; i < e_max; i++) {
        free(r_paths[i]);
    }
}

void init_file(void)
{
#ifdef _WIN32
    wchar_t *wpath;
    HRESULT res = SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &wpath);
    assert(res == S_OK);

    size_t wsize = wcslen(wpath);
    size_t msize = wsize * 3 + 1;
    char *mpath = (char *)malloc(msize);
    assert(mpath);

    size_t csize = 0;
    wcstombs_s(&csize, mpath, msize, wpath, wsize);
    CoTaskMemFree(wpath);

    KDchar* paths[] = {
        "Res",
        "Data",
        "Removal",
        "Temp",
    };

    msize = strlen(mpath);
    KDsize len = msize + strlen(paths[e_tmp]) + 2;
    r_paths[e_tmp] = (KDchar *)malloc(len);
    assert(r_paths[e_tmp]);
    snprintf(r_paths[e_tmp], len, "%s\\%s", mpath, paths[e_tmp]);

    strcat(mpath, "\\OpenKODE");
    msize = strlen(mpath);
    r_paths[e_root] = mpath;

    for (KDint i = 0; i < e_tmp; i++) {
        len = msize + strlen(paths[i]) + 2;
        r_paths[i] = (KDchar *)malloc(len);
        assert(r_paths[i]);
        snprintf(r_paths[i], len, "%s\\%s", mpath, paths[i]);
    }

    mkdir(r_paths[e_root]);
    mkdir(r_paths[e_res]);
    mkdir(r_paths[e_data]);
    mkdir(r_paths[e_removal]);
#else
    mode_t mode = S_IRWXU | S_IRGRP | S_IROTH;
    const char *path = getenv("OPENKODE_HOME");
    if (path) {
        r_paths[e_root] = strdup(path);
    } else {
        path = getenv("HOME");
        asprintf(&r_paths[e_root], "%s/openkode", path);
    }
    assert(r_paths[e_root]);
    mkdir(r_paths[e_root], mode);

    r_paths[e_tmp] = strdup("/tmp");
    assert(r_paths[e_tmp]);

    for (KDint i = 0; i < e_tmp; i++) {
        asprintf(&r_paths[i], "%s%s", r_paths[e_root], v_paths[i]);
        assert(r_paths[i]);
        mkdir(r_paths[i], mode);
    }
    chmod(r_paths[e_res], S_IRUSR | S_IROTH);
#endif
}

static KDchar *get_full_path(const KDchar *pathname)
{
    KDchar *path = KD_NULL;
    if (!strncmp(pathname, "/native/", 8)) {
        path = strdup(pathname + 8);
    } else {
        for (KDsize i = 0; i < e_max; i++) {
            KDsize vlen = strlen(v_paths[i]);
            if (!strncmp(pathname, v_paths[i], vlen) && !(strlen(pathname) > vlen && pathname[vlen] != '/')) {
                KDsize rlen = strlen(r_paths[i]);
                KDsize plen = strlen(pathname + vlen);
                KDsize len = rlen + plen + 1;
                path = (KDchar *)malloc(len);
                snprintf(path, len, "%s%s", r_paths[i], pathname + vlen);
                break;
            }
        }
    }
    return path;
}

KD_API KDFile *KD_APIENTRY kdFopen(const KDchar *pathname, const KDchar *mode)
{
#ifdef _WIN32
    if (!strncmp("/res/", pathname, 5) && (mode[0] == 'a' || mode[0] == 'w')) {
        kdSetError(KD_EACCES);
        return KD_NULL;
    }
#endif
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return KD_NULL;
    }
    KDFile *file = (KDFile *)fopen(path, mode);
    if (file) {
        kdSetError(0);
    }
    free(path);
    return file;
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
    KDint rc = feof((FILE *)file);
    return rc == 0 ? rc : KD_EOF;
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
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = -1;
#ifdef _WIN32
    rc = mkdir(path);
#else
    rc = mkdir(path, S_IRUSR | S_IWUSR | S_IXUSR |
                     S_IRGRP | S_IWGRP |
                     S_IROTH | S_IWOTH);
#endif
    free(path);
    return rc;
}

KD_API KDint KD_APIENTRY kdRmdir(const KDchar *pathname)
{
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = rmdir(path);
    free(path);
    return rc;
}

KD_API KDint KD_APIENTRY kdRename(const KDchar *src, const KDchar *dest)
{
    KDchar *s_path = get_full_path(src);
    if (!s_path) {
        return -1;
    }
    KDchar *d_path = get_full_path(dest);
    if (!d_path) {
        free(d_path);
        return -1;
    }
    KDint rc = rename(s_path, d_path);
    free(s_path);
    free(d_path);
    return rc;
}

KD_API KDint KD_APIENTRY kdRemove(const KDchar *pathname)
{
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = remove(path);
    free(path);
    return rc;
}

KD_API KDint KD_APIENTRY kdTruncate(const KDchar *pathname, KDoff length)
{
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = -1;
#if HAVE_TRUNCATE
    rc = truncate(path, length);
#elif _WIN32
    HANDLE file = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file) {
        DWORD hsize = 0;
        DWORD lsize = GetFileSize(file, &hsize);
        KDoff size = ((KDoff)hsize << 32) | lsize;
        if (size >= length) {
            if (SetFilePointer(file, (long)length, &hsize, FILE_BEGIN) != 0xFFFFFFFF) {
                rc = 0;
            }
        } else {
            KDoff csize = size;
            KDoff wsize = 0;
            DWORD wbytes = 0;
            KDuint8 tmp[4096] = "";
            if (SetFilePointer(file, 0, 0, FILE_END) != 0xFFFFFFFF) {
                rc = 0;
                while (csize != length) {
                    wsize = ((csize + 4096) > length) ? length - csize : 4096;
                    if (!WriteFile(file, tmp, (long)wsize, &wbytes, NULL) || wsize != wbytes) {
                        rc = -1;
                        break;
                    }
                    csize += wsize;
                }
            }
        }
        if (rc == 0 && !SetEndOfFile(file)) {
            rc = -1;
        }
        if (rc != 0) {
            set_win2posix_err();
        }
        CloseHandle(file);
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(path);
    return rc;
}

KD_API KDint KD_APIENTRY kdStat(const KDchar* pathname, struct KDStat* buf)
{
    if (!strcmp("/", pathname) || !strcmp("/removable", pathname)) {
        kdSetError(KD_EACCES);
        return -1;
    }
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    struct stat s = {};
    KDint rc = stat(path, &s);
    if (!rc) {
        write_stat(buf, (KDmode)s.st_mode, s.st_size, s.st_mtime);
    }
    free(path);
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
    if (!strcmp("/", pathname) || !strcmp("/removable", pathname) ||
        ((!strcmp("/res", pathname) || !strncmp("/res/", pathname, 5)) && (amode & (KD_W_OK | KD_X_OK)))) {
        kdSetError(KD_EACCES);
        return -1;
    }
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = access(path, amode);
    free(path);
    return rc;
}

KD_API KDDir *KD_APIENTRY kdOpenDir(const KDchar *pathname)
{
    if (!strcmp(pathname, "/")) {
        kdSetError(KD_EACCES);
        return KD_NULL;
    }

    KDchar *path = get_full_path(pathname);
    if (!path) {
        return KD_NULL;
    }
    KDDir *ret = KD_NULL;
#if HAVE_DIRENT_H
    DIR *dir = opendir(pathname);
    if (dir) {
        ret = (KDDir *)malloc(sizeof(KDDir));
        if (!ret) {
            closedir(dir);
        } else {
            ret->dir = dir;
        }
    }
#elif _WIN32
    KDchar *wpath = (KDchar *)malloc(strlen(path) + 5);
    if (wpath) {
        strcpy(wpath, path);
        strcat(wpath, "\\*");

        WIN32_FIND_DATA data;
        HANDLE handle = FindFirstFile(wpath, &data);
        if (handle != INVALID_HANDLE_VALUE) {
            ret = (KDDir *)malloc(sizeof(dir));
            if (dir) {
                ret->handle = handle;
                ret->data = data;
                ret->dirent.d_name = KD_NULL;
            }
        }
        free(wpath);
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(path);
    return ret;
}

KD_API KDDirent *KD_APIENTRY kdReadDir(KDDir *dir)
{
    KDDirent *ret = KD_NULL;
#if HAVE_DIRENT_H
    struct dirent *dirent = readdir(dir->dir);
    if (dirent) {
        ret = &dir->dirent;
        ret->d_name = dirent->d_name;
    }
#elif _WIN32
    if (!dir->dirent.d_name) {
        ret = &dir->dirent;
        ret->d_name = dir->data.cFileName;
    } else if (FindNextFile(dir->handle, &dir->data)) {
        ret = &dir->dirent;
        ret->d_name = dir->data.cFileName;
    } else if (GetLastError() != ERROR_NO_MORE_FILES) {
        set_win2posix_err();
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    return ret;
}

KD_API KDint KD_APIENTRY kdCloseDir(KDDir *dir)
{
    KDint rc = -1;
#if HAVE_DIRENT_H
    rc = closedir(dir->dir);
#elif _WIN32
    if (!FindClose(dir->handle)) {
        set_win2posix_err();
    } else {
        rc = 0;
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(dir);
    return rc;
}

KD_API KDoff KD_APIENTRY kdGetFree(const KDchar *pathname)
{
    if (!strcmp("/", pathname) ||
        !strcmp("/removable" , pathname) ||
        !strncmp("/removable/", pathname, 11)) {
        kdSetError(KD_EACCES);
        return -1;
    }

    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDoff rc = -1;
#if HAVE_SYS_STATVFS_H
    struct statvfs info;
    if (!statvfs(path, &info)) {
        rc = info.f_bavail * info.f_frsize;
    }
#elif _WIN32
    PULARGE_INTEGER space;
    if (!GetDiskFreeSpaceEx(path, (PULARGE_INTEGER)&space, NULL, NULL)) {
        set_win2posix_err();
    } else {
        rc = (KDoff)space;
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(path);
    return rc;
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
    kdSetError(KD_ENOSYS);
    return -1;
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
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = -1;
#if HAVE_LSTAT
    struct stat s;
    rc = lstat(path, &s);
    if (!rc) {
        write_stat(buf, (KDmode)s.st_mode, s.st_size, s.st_mtime);
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(path);
    return rc;
}

KD_API KDFile *KD_APIENTRY kdFmemopn(void *buf, KDsize size, const KDchar *mode)
{
    KDFile *file = KD_NULL;
#if HAVE_FMEMOPEN
    file = (KDFile *)fmemopen(buf, size, mode);
#else
    kdSetError(KD_ENOSYS);
#endif
    return file;
}

KD_API KDint KD_APIENTRY kdFgetpos(KDFile *file, KDoff *pos)
{
    return fgetpos((FILE *)file, (fpos_t *)pos);
}

KD_API KDint KD_APIENTRY kdOpen(const KDchar* pathname, KDint flags, KDint mode)
{
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = open(path, flags, mode);
    free(path);
    return rc;
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
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = chdir(path);
    free(path);
    return rc;
}

KD_API KDint KD_APIENTRY kdLink(const KDchar *oldfile, const KDchar *newname)
{
    KDchar *o_path = get_full_path(oldfile);
    if (!o_path) {
        return -1;
    }
    KDchar *n_path = get_full_path(newname);
    if (!n_path) {
        return -1;
    }
    KDint rc = -1;
#if HAVE_LINK
    rc = link(o_path, n_path);
#elif _WIN32
    if (CreateSymbolicLink(o_path, n_path, 0) == FALSE) {
        set_win2posix_err();
    } else {
        rc = 0;
    }
#else
    kdSetError(KD_ENOSYS);
#endif
    free(o_path);
    free(n_path);
    return rc;
}

KD_API KDint KD_APIENTRY kdUnlink(const KDchar *pathname)
{
    KDchar *path = get_full_path(pathname);
    if (!path) {
        return -1;
    }
    KDint rc = unlink(path);
    free(path);
    return rc;
}

KD_API void KD_APIENTRY kdSync(void)
{
#if HAVE_SYNC
    sync();
#else
    kdSetError(KD_ENOSYS);
#endif
}

KD_API KDint KD_APIENTRY kdIsatty(KDint fd)
{
    return isatty(fd);
}
