#pragma once

// ---------------------------------------------------------
// Operating System
// ---------------------------------------------------------

#define ZIRSAKHT_OS_WINDOWS 0
#define ZIRSAKHT_OS_LINUX 0
#define ZIRSAKHT_OS_MACOS 0
#define ZIRSAKHT_OS_BSD 0
#define ZIRSAKHT_OS_UNIX 0
#define ZIRSAKHT_OS_UNKNOWN 0

#if defined(_WIN32) || defined(_WIN64)

#undef ZIRSAKHT_OS_WINDOWS
#define ZIRSAKHT_OS_WINDOWS 1

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#elif defined(__APPLE__) && defined(__MACH__)

#undef ZIRSAKHT_OS_MACOS
#define ZIRSAKHT_OS_MACOS 1

#elif defined(__linux__)

#undef ZIRSAKHT_OS_LINUX
#define ZIRSAKHT_OS_LINUX 1

#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)

#undef ZIRSAKHT_OS_BSD
#define ZIRSAKHT_OS_BSD 1

#elif defined(__unix__) || defined(__unix)

#undef ZIRSAKHT_OS_UNIX
#define ZIRSAKHT_OS_UNIX 1

#else

#undef ZIRSAKHT_OS_UNKNOWN
#define ZIRSAKHT_OS_UNKNOWN 1

#endif

// ---------------------------------------------------------
// POSIX
// ---------------------------------------------------------

#define ZIRSAKHT_POSIX 0

#if defined(_POSIX_VERSION) || defined(__unix__) || defined(__unix)

#undef ZIRSAKHT_POSIX
#define ZIRSAKHT_POSIX 1

#endif

// ---------------------------------------------------------
// CPU Architecture
// ---------------------------------------------------------

#define ZIRSAKHT_ARCH_X86 0
#define ZIRSAKHT_ARCH_X86_64 0
#define ZIRSAKHT_ARCH_ARM 0
#define ZIRSAKHT_ARCH_ARM64 0
#define ZIRSAKHT_ARCH_RISCV32 0
#define ZIRSAKHT_ARCH_RISCV64 0
#define ZIRSAKHT_ARCH_WASM32 0
#define ZIRSAKHT_ARCH_WASM64 0
#define ZIRSAKHT_ARCH_UNKNOWN 0

#if defined(__x86_64__) || defined(_M_X64)

#undef ZIRSAKHT_ARCH_X86_64
#define ZIRSAKHT_ARCH_X86_64 1

#elif defined(__i386__) || defined(_M_IX86)

#undef ZIRSAKHT_ARCH_X86
#define ZIRSAKHT_ARCH_X86 1

#elif defined(__aarch64__) || defined(_M_ARM64)

#undef ZIRSAKHT_ARCH_ARM64
#define ZIRSAKHT_ARCH_ARM64 1

#elif defined(__arm__) || defined(_M_ARM)

#undef ZIRSAKHT_ARCH_ARM
#define ZIRSAKHT_ARCH_ARM 1

#elif defined(__riscv) && (__riscv_xlen == 64)

#undef ZIRSAKHT_ARCH_RISCV64
#define ZIRSAKHT_ARCH_RISCV64 1

#elif defined(__riscv) && (__riscv_xlen == 32)

#undef ZIRSAKHT_ARCH_RISCV32
#define ZIRSAKHT_ARCH_RISCV32 1

#elif defined(__wasm64__)

#undef ZIRSAKHT_ARCH_WASM64
#define ZIRSAKHT_ARCH_WASM64 1

#elif defined(__wasm32__)

#undef ZIRSAKHT_ARCH_WASM32
#define ZIRSAKHT_ARCH_WASM32 1

#else

#undef ZIRSAKHT_ARCH_UNKNOWN
#define ZIRSAKHT_ARCH_UNKNOWN 1

#endif

// ---------------------------------------------------------
// Compiler
// ---------------------------------------------------------

#define ZIRSAKHT_COMPILER_CLANG 0
#define ZIRSAKHT_COMPILER_GCC 0
#define ZIRSAKHT_COMPILER_MSVC 0
#define ZIRSAKHT_COMPILER_UNKNOWN 0

#if defined(__clang__)

#undef ZIRSAKHT_COMPILER_CLANG
#define ZIRSAKHT_COMPILER_CLANG 1

#elif defined(_MSC_VER)

#undef ZIRSAKHT_COMPILER_MSVC
#define ZIRSAKHT_COMPILER_MSVC 1

#elif defined(__GNUC__)

#undef ZIRSAKHT_COMPILER_GCC
#define ZIRSAKHT_COMPILER_GCC 1

#else

#undef ZIRSAKHT_COMPILER_UNKNOWN
#define ZIRSAKHT_COMPILER_UNKNOWN 1

#endif

// ---------------------------------------------------------
// Endianness
// ---------------------------------------------------------

#define ZIRSAKHT_LITTLE_ENDIAN 0
#define ZIRSAKHT_BIG_ENDIAN 0

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#undef ZIRSAKHT_LITTLE_ENDIAN
#define ZIRSAKHT_LITTLE_ENDIAN 1

#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#undef ZIRSAKHT_BIG_ENDIAN
#define ZIRSAKHT_BIG_ENDIAN 1

#elif defined(_WIN32)

// Windows targets are little-endian
#undef ZIRSAKHT_LITTLE_ENDIAN
#define ZIRSAKHT_LITTLE_ENDIAN 1

#endif

// ---------------------------------------------------------
// Pointer / Word Size
// ---------------------------------------------------------

#define ZIRSAKHT_32BIT 0
#define ZIRSAKHT_64BIT 0

#if defined(__SIZEOF_POINTER__)

#if __SIZEOF_POINTER__ == 8

#undef ZIRSAKHT_64BIT
#define ZIRSAKHT_64BIT 1

#elif __SIZEOF_POINTER__ == 4

#undef ZIRSAKHT_32BIT
#define ZIRSAKHT_32BIT 1

#endif

#elif defined(_WIN64)

#undef ZIRSAKHT_64BIT
#define ZIRSAKHT_64BIT 1

#else

#undef ZIRSAKHT_32BIT
#define ZIRSAKHT_32BIT 1

#endif

// ---------------------------------------------------------
// Build Language
// ---------------------------------------------------------

#define ZIRSAKHT_CPP 1

#ifdef __cplusplus
#define ZIRSAKHT_CPLUSPLUS 1
#else
#define ZIRSAKHT_CPLUSPLUS 0
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define ZIRSAKHT_NOEXCEPT _NOEXCEPT
#define ZIRSAKHT_CONSTEXPR
#else
#define ZIRSAKHT_NOEXCEPT noexcept
#define ZIRSAKHT_CONSTEXPR constexpr
#endif