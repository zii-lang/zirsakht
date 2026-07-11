#pragma once

#ifndef ZCORE_SYSTEM_HPP
#define ZCORE_SYSTEM_HPP

// ---------------------------------------------------------
// Operating System
// ---------------------------------------------------------

#define ZCORE_OS_WINDOWS 0
#define ZCORE_OS_LINUX 0
#define ZCORE_OS_MACOS 0
#define ZCORE_OS_BSD 0
#define ZCORE_OS_UNIX 0
#define ZCORE_OS_UNKNOWN 0

#if defined(_WIN32) || defined(_WIN64)

#undef ZCORE_OS_WINDOWS
#define ZCORE_OS_WINDOWS 1

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#elif defined(__APPLE__) && defined(__MACH__)

#undef ZCORE_OS_MACOS
#define ZCORE_OS_MACOS 1

#elif defined(__linux__)

#undef ZCORE_OS_LINUX
#define ZCORE_OS_LINUX 1

#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)

#undef ZCORE_OS_BSD
#define ZCORE_OS_BSD 1

#elif defined(__unix__) || defined(__unix)

#undef ZCORE_OS_UNIX
#define ZCORE_OS_UNIX 1

#else

#undef ZCORE_OS_UNKNOWN
#define ZCORE_OS_UNKNOWN 1

#endif

// ---------------------------------------------------------
// POSIX
// ---------------------------------------------------------

#define ZCORE_POSIX 0

#if defined(_POSIX_VERSION) || defined(__unix__) || defined(__unix)

#undef ZCORE_POSIX
#define ZCORE_POSIX 1

#endif

// ---------------------------------------------------------
// CPU Architecture
// ---------------------------------------------------------

#define ZCORE_ARCH_X86 0
#define ZCORE_ARCH_X86_64 0
#define ZCORE_ARCH_ARM 0
#define ZCORE_ARCH_ARM64 0
#define ZCORE_ARCH_RISCV32 0
#define ZCORE_ARCH_RISCV64 0
#define ZCORE_ARCH_WASM32 0
#define ZCORE_ARCH_WASM64 0
#define ZCORE_ARCH_UNKNOWN 0

#if defined(__x86_64__) || defined(_M_X64)

#undef ZCORE_ARCH_X86_64
#define ZCORE_ARCH_X86_64 1

#elif defined(__i386__) || defined(_M_IX86)

#undef ZCORE_ARCH_X86
#define ZCORE_ARCH_X86 1

#elif defined(__aarch64__) || defined(_M_ARM64)

#undef ZCORE_ARCH_ARM64
#define ZCORE_ARCH_ARM64 1

#elif defined(__arm__) || defined(_M_ARM)

#undef ZCORE_ARCH_ARM
#define ZCORE_ARCH_ARM 1

#elif defined(__riscv) && (__riscv_xlen == 64)

#undef ZCORE_ARCH_RISCV64
#define ZCORE_ARCH_RISCV64 1

#elif defined(__riscv) && (__riscv_xlen == 32)

#undef ZCORE_ARCH_RISCV32
#define ZCORE_ARCH_RISCV32 1

#elif defined(__wasm64__)

#undef ZCORE_ARCH_WASM64
#define ZCORE_ARCH_WASM64 1

#elif defined(__wasm32__)

#undef ZCORE_ARCH_WASM32
#define ZCORE_ARCH_WASM32 1

#else

#undef ZCORE_ARCH_UNKNOWN
#define ZCORE_ARCH_UNKNOWN 1

#endif

// ---------------------------------------------------------
// Compiler
// ---------------------------------------------------------

#define ZCORE_COMPILER_CLANG 0
#define ZCORE_COMPILER_GCC 0
#define ZCORE_COMPILER_MSVC 0
#define ZCORE_COMPILER_UNKNOWN 0

#if defined(__clang__)

#undef ZCORE_COMPILER_CLANG
#define ZCORE_COMPILER_CLANG 1

#elif defined(_MSC_VER)

#undef ZCORE_COMPILER_MSVC
#define ZCORE_COMPILER_MSVC 1

#elif defined(__GNUC__)

#undef ZCORE_COMPILER_GCC
#define ZCORE_COMPILER_GCC 1

#else

#undef ZCORE_COMPILER_UNKNOWN
#define ZCORE_COMPILER_UNKNOWN 1

#endif

// ---------------------------------------------------------
// Endianness
// ---------------------------------------------------------

#define ZCORE_LITTLE_ENDIAN 0
#define ZCORE_BIG_ENDIAN 0

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#undef ZCORE_LITTLE_ENDIAN
#define ZCORE_LITTLE_ENDIAN 1

#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#undef ZCORE_BIG_ENDIAN
#define ZCORE_BIG_ENDIAN 1

#elif defined(_WIN32)

// Windows targets are little-endian
#undef ZCORE_LITTLE_ENDIAN
#define ZCORE_LITTLE_ENDIAN 1

#endif

// ---------------------------------------------------------
// Pointer / Word Size
// ---------------------------------------------------------

#define ZCORE_32BIT 0
#define ZCORE_64BIT 0

#if defined(__SIZEOF_POINTER__)

#if __SIZEOF_POINTER__ == 8

#undef ZCORE_64BIT
#define ZCORE_64BIT 1

#elif __SIZEOF_POINTER__ == 4

#undef ZCORE_32BIT
#define ZCORE_32BIT 1

#endif

#elif defined(_WIN64)

#undef ZCORE_64BIT
#define ZCORE_64BIT 1

#else

#undef ZCORE_32BIT
#define ZCORE_32BIT 1

#endif

// ---------------------------------------------------------
// Build Language
// ---------------------------------------------------------

#define ZCORE_CPP 1

#ifdef __cplusplus
#define ZCORE_CPLUSPLUS 1
#else
#define ZCORE_CPLUSPLUS 0
#endif

#endif
