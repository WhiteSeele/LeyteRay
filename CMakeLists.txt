cmake_minimum_required(VERSION 3.29)
project(leyteRay)

set(CMAKE_CXX_STANDARD 20)

include_directories(src
        src/utils
        src/core
        src/color
        src/ray
        src/world
        src/materials
        src/Profile)

add_executable(leyteRay src/main.cpp
        src/utils/stb_image.h
        src/core/vec3.h
        src/utils/ImageManager.h
        src/ray/Ray.cpp
        src/ray/Ray.h
        src/world/hit.h
        src/world/Sphere.cpp
        src/world/Sphere.h
        src/world/HittableList.cpp
        src/world/HittableList.h
        src/utils/common.h
        src/core/Interval.h
        src/Camera.cpp
        src/Camera.h
        src/Profile/TimerProfile.cpp
        src/Profile/TimerProfile.h
        src/core/utils.h
        src/materials/material.h
)
