cmake_minimum_required(VERSION 3.8)
project(aMazeGL)

set(CMAKE_CXX_STANDARD 11)

set(LINKER_FLAGS "-lSDL2 -lSDL2main -lGL -ldl")
link_libraries("${LINKER_FLAGS}")

set(SOURCE_FILES
        glad/glad.c
        glad/glad.h
        glad/khrplatform.h
        stb_image.h
        obj_loader.h obj_loader.cpp
        main.cpp
        Display.cpp Display.h
        Shader.cpp Shader.h
        Mesh.cpp Mesh.h
        Texture.cpp Texture.h
        Transform.cpp Transform.h
        Camera.cpp Camera.h
        Material.cpp Material.h
        Light.cpp Light.h
        Entity.cpp Entity.h
        Map.cpp Map.h)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

add_executable(aMazeGL ${SOURCE_FILES})