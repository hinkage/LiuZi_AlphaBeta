cmake_minimum_required(VERSION 3.23)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
IF(DEFINED ENV{VCPKG_ROOT})
	MESSAGE(STATUS "No vcpkg root")
ELSE()
	MESSAGE(STATUS "Got vcpkg root:" $ENV{VCPKG_ROOT})
ENDIF()

project(test)

set(
    src_files
    src/game.cpp
    src/alphabeta.cpp
)

if (DEFINED ENV{EMSDK})
	MESSAGE(STATUS "Got EMSDK")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/x64/Release")
    # Set the Emscripten toolchain file
    set(CMAKE_TOOLCHAIN_FILE "D:/All/WASM/emsdk-3.1.56/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
	add_executable(
        liuzi
        ${src_files}
        src/liuzi.cpp
    )
	set(CMAKE_EXECUTABLE_SUFFIX ".js")
    set_target_properties(liuzi PROPERTIES COMPILE_FLAGS "-O3")
    set_target_properties(liuzi PROPERTIES LINK_FLAGS "--no-entry --bind")
    target_include_directories(liuzi PUBLIC "D:/All/WASM/emsdk-3.1.56/upstream/emscripten/cache/sysroot/include")
else()
	MESSAGE(STATUS "No EMSDK")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/x64/Debug")
    add_executable(
        test
        ${src_files}
        test/test.cpp
    )
endif()
