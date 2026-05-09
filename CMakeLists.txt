cmake_minimum_required(VERSION 3.16)

project(STimer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_subdirectory(src)

if(APPLE)
    set(CMAKE_FRAMEWORK_PATH ~/Library/Frameworks ${CMAKE_FRAMEWORK_PATH})

    macro(find_sdl_framework NAME)
        find_library(${NAME}_LIBRARY ${ARGN})
        if(${NAME}_LIBRARY)
            get_filename_component(${NAME}_FRAMEWORK_PATH "${${NAME}_LIBRARY}" DIRECTORY)
            set(${NAME}_INCLUDE_PATH "${${NAME}_FRAMEWORK_PATH}/${ARGN}.framework/Headers")
            include_directories(${${NAME}_INCLUDE_PATH})
        endif()
    endmacro()

    find_sdl_framework(SDL3 SDL3)
    find_sdl_framework(SDL3_IMAGE SDL3_image)
    find_sdl_framework(SDL3_TTF SDL3_ttf)
    find_sdl_framework(SDL3_MIXER SDL3_mixer)
    find_sdl_framework(OGG ogg)
    find_sdl_framework(PNG png)

    target_link_libraries(${PROJECT_NAME}
        ${SDL3_LIBRARY}
        ${SDL3_IMAGE_LIBRARY}
        ${SDL3_TTF_LIBRARY}
        ${SDL3_MIXER_LIBRARY}
        ${OGG_LIBRARY}
        ${PNG_LIBRARY}
        curl
    )

elseif(WIN32)
    if(MINGW)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
        find_package(SDL3 CONFIG REQUIRED)
        find_package(SDL3_image CONFIG REQUIRED)
        find_package(SDL3_ttf CONFIG REQUIRED)
        find_package(SDL3_mixer CONFIG REQUIRED)
        find_package(libcurl CONFIG REQUIRED)
        find_package(freetype CONFIG REQUIRED)

        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL3::SDL3
            SDL3::SDL3_image
            SDL3::SDL3_ttf
            SDL3::SDL3_mixer
            libcurl::libcurl
            freetype
        )
    endif()
endif()
