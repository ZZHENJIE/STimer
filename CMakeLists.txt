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

    target_link_libraries(${PROJECT_NAME}
        ${SDL3_LIBRARY}
        curl
    )

elseif(WIN32)
    if(MINGW)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
        find_package(SDL3 CONFIG REQUIRED)
        find_package(libcurl CONFIG REQUIRED)

        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL3::SDL3
            libcurl::libcurl
        )
    endif()
endif()
