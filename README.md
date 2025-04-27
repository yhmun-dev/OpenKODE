![OpenKODE logo](https://www.khronos.org/assets/uploads/ceimg/openkode_100px_june16_-_28de80_-_83b47e519e43822e4b6abc8472ac29c4ccb7c40e.jpg)

OpenKODE® is a royalty-free, open standard that combines a set of native APIs to increase source portability for rich media and graphics applications. OpenKODE reduces mobile platform fragmentation by providing a cross-platform API for accessing operating system resources, and a media architecture for portable access to advanced mixed graphics acceleration.

To get more details, go to [https://www.khronos.org/openkode](https://www.khronos.org/openkode/)

![Build status](https://github.com/yhmun-dev/OpenKODE/actions/workflows/build_action.yml/badge.svg)

### Build Requirements
  - [Meson 1.1.0 or later](https://mesonbuild.com/Getting-meson.html)
  - [Ninja](https://ninja-build.org)

### Build Instructions
  - __Configure__
    - Run `meson setup build/ [--buildtype debug|release]`
    - Add `--default-library static` if static is desired (note: default is shared but windows always sets static)
    - Add `--backend=[vs2022 or older]` if visual studio is desired
  - __Compile__
    - Run `meson compile -C build/`
  - __Install__
    - Run `meson install -C build/`

### Test Instructions
  - __Clone Private Repo__
    - Run `git clone https://oauth2:<secret_token>@github.com/yhmun-dev/OpenKODE-CTS.git test`
    - Contact me [yhmun0409@gmail.com](mailto:yhmun0409@gmail.com) if you desire the personal access token
