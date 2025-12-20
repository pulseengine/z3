# CMake toolchain file for wasi-sdk
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/wasi-sdk.cmake ..

# Detect wasi-sdk location
if(NOT DEFINED WASI_SDK_PREFIX)
    if(DEFINED ENV{WASI_SDK_PREFIX})
        set(WASI_SDK_PREFIX $ENV{WASI_SDK_PREFIX})
    elseif(EXISTS "/opt/wasi-sdk")
        set(WASI_SDK_PREFIX "/opt/wasi-sdk")
    elseif(EXISTS "$ENV{HOME}/wasi-sdk")
        set(WASI_SDK_PREFIX "$ENV{HOME}/wasi-sdk")
    else()
        message(FATAL_ERROR "WASI_SDK_PREFIX not set and wasi-sdk not found in standard locations")
    endif()
endif()

message(STATUS "Using wasi-sdk from: ${WASI_SDK_PREFIX}")

# Target system
set(CMAKE_SYSTEM_NAME WASI)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR wasm32)

# Compilers
set(CMAKE_C_COMPILER "${WASI_SDK_PREFIX}/bin/clang")
set(CMAKE_CXX_COMPILER "${WASI_SDK_PREFIX}/bin/clang++")
set(CMAKE_AR "${WASI_SDK_PREFIX}/bin/llvm-ar")
set(CMAKE_RANLIB "${WASI_SDK_PREFIX}/bin/llvm-ranlib")
set(CMAKE_C_COMPILER_TARGET "wasm32-wasip2")
set(CMAKE_CXX_COMPILER_TARGET "wasm32-wasip2")

# Sysroot
set(CMAKE_SYSROOT "${WASI_SDK_PREFIX}/share/wasi-sysroot")

# Flags
set(CMAKE_C_FLAGS_INIT "-fno-exceptions")
set(CMAKE_CXX_FLAGS_INIT "-fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--no-entry")

# Don't look for programs on the host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Force single-threaded build for WASI (no pthread support in preview2)
set(Z3_SINGLE_THREADED ON CACHE BOOL "Force single-threaded for WASI" FORCE)
set(Z3_POLLING_TIMER ON CACHE BOOL "Use polling timer for WASI" FORCE)

# Disable features not available in WASI
set(Z3_BUILD_EXECUTABLE OFF CACHE BOOL "Disable executable for WASI" FORCE)
set(Z3_BUILD_PYTHON_BINDINGS OFF CACHE BOOL "Disable Python for WASI" FORCE)
set(Z3_BUILD_JAVA_BINDINGS OFF CACHE BOOL "Disable Java for WASI" FORCE)
set(Z3_BUILD_DOTNET_BINDINGS OFF CACHE BOOL "Disable .NET for WASI" FORCE)

# Mark as WASI build
set(Z3_WASI_BUILD ON)
