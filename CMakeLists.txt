cmake_minimum_required(VERSION 3.29)
project(leyteRay)

set(CMAKE_CXX_STANDARD 20)

include_directories(src
        src/utils
        src/math
        src/color
        src/ray)

add_executable(leyteRay src/main.cpp
        src/utils/stb_image.h
        src/math/vec3.h
        src/color/color.h
        src/utils/ImageManager.h
        src/ray/Ray.cpp
        src/ray/Ray.h)
