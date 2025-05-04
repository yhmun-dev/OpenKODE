project('openkode', 'c',
          version: '1.0.3',
          license: 'MIT',
    license_files: 'LICENSE',
    meson_version: '>= 1.2.0')

proj_name = meson.project_name()
proj_ver = meson.project_version()
prefix = get_option('prefix')
inc_dirs = include_directories('include', 'src')
dat_dir = prefix / get_option('datadir')
bin_dir = prefix / get_option('bindir')
lib_dir = prefix / get_option('libdir')

cc = meson.get_compiler('c')
system = host_machine.system()
subsystem = host_machine.subsystem()
cpu_family = host_machine.cpu_family()

g_args = []
if get_option('b_ndebug') == 'true'
    g_args += '-DKD_NDEBUG'
endif

if get_option('default_library') == 'static' or system == 'windows'
    g_args += '-DKHRONOS_STATIC'
endif
add_global_arguments(g_args, language: 'c')

subdir('src')

lib_deps = []
if host_machine.system() == 'windows'
    core_lib = static_library(proj_name + '-core',
                    sources: core_srcs,
        include_directories: inc_dirs,
                install_dir: lib_dir,
                    install: true)
else
    lib_deps += cc.find_library('m', required: true)
    core_lib = library(proj_name + '-core',
                    sources: core_srcs,
        include_directories: inc_dirs,
               dependencies: lib_deps,
                    version: proj_ver,
                  soversion: proj_ver.split('.')[0],
                install_dir: lib_dir,
                    install: true)
endif

entry_lib = static_library(proj_name,
                sources: ['src/main.c'],
    include_directories: inc_dirs,
            install_dir: lib_dir,
                install: true)

openkode_libs = [core_lib, entry_lib]
openkode_dep = declare_dependency(
              link_with: openkode_libs,
    include_directories: inc_dirs)

openkode_app = executable('openkode',
                sources: ['src/app/main.c'],
           dependencies: openkode_dep,
          win_subsystem: 'windows',
            install_dir: bin_dir,
                install: false)

install_data(meson.project_license_files(),
            install_dir: prefix / 'licenses' / proj_name)

install_subdir('include',
            install_dir: prefix)

pkg_cfg = import('pkgconfig')
pkg_cfg.generate(
           name: proj_name,
       filebase: proj_name,
        version: proj_ver,
      libraries: openkode_libs,
    description: 'SVT (Scalable Video Technology) for AV1 encoder library',
)

# In the root directory, run `https://oauth2:<secret_token>@github.com/yhmun-dev/OpenKODE-CTS.git test` to fetch the private repository
if get_option('enable_test')
    subdir('test')
endif
