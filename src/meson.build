cfg = configuration_data()

cfg.set('VENDOR', 'Younghwan Mun <yhmun0409@gmail.com>')
cfg.set('VERSION', proj_ver)
cfg.set('PLATFORM', '@0@ @1@'.format(system, cpu_family))
cfg.set('PLATFORM_STORAGE', prefix)

cfg.set10('HAVE_DIRENT_H', cc.has_header('dirent.h'))
cfg.set10('HAVE_PTHREAD_H', cc.has_header('pthread.h'))
cfg.set10('HAVE_SEMAPHORE_H', cc.has_header('semaphore.h'))
cfg.set10('HAVE_SYS_STATVFS_H', cc.has_header('sys/statvfs.h'))
cfg.set10('HAVE_SYS_TIME_H', cc.has_header('sys/time.h'))
cfg.set10('HAVE_THREADS_H', cc.has_header('threads.h'))
cfg.set10('HAVE_UNISTD_H', cc.has_header('unistd.h'))

cfg.set10('HAVE_GETTIMEOFDAY', cc.has_function('gettimeofday'))
cfg.set10('HAVE_SETTIMEOFDAY', cc.has_function('settimeofday'))
cfg.set10('HAVE_TIMEGM', cc.has_function('timegm'))
cfg.set10('HAVE_TRUNCATE', cc.has_function('truncate'))

configure_file(
    input: 'config.h.in',
    output: 'config.h',
    configuration: cfg,
)

subdir('core')
