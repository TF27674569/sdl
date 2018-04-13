cmake_minimum_required(VERSION 3.4.1)

add_library(
             SDL2Main

             SHARED

             #配置入口函数
             src/main/cpp/sdl/src/main/android/SDL_android_main.c
             src/main/cpp/sdl_test.cpp )


#头文件
include_directories(src/main/cpp/sdl/include)
#资源文件
include_directories(src/main/cpp/sdl/src)

#SDL2重要的库
add_library( SDL2
             SHARED
             IMPORTED)

#库路径
set_target_properties( SDL2
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/cpp/${ANDROID_ABI}/libSDL2.so)




find_library(
              log-lib
              log )



target_link_libraries(
                       SDL2Main
                       #链接SDL2 库
                       SDL2
                       ${log-lib} )