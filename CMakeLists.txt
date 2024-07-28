CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(rtwo)


include_directories(include/)

add_executable(rtow src/rtow.cpp
        src/vec3.h
        src/color.h
        src/ray.h
        src/sphere.h
        src/hittable.h
        src/hittable_list.h
        src/math.h
        src/rtow.h
        src/interval.h
        src/camera.h
        src/material.h)
