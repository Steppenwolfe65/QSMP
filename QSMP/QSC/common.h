/*
* 2022 John G. Underhill
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of John G. Underhill.
* The intellectual and technical concepts contained
* herein are proprietary to John G. Underhill
* and his suppliers and may be covered by U.S. and Foreign Patents,
* patents in process, and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Digital Freedom Defense Incorporated.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This library was published publicly in hopes that it would aid in prototyping
* post-quantum secure primitives for educational purposes only.
* All and any commercial uses of this library are exclusively reserved by the author
* John G. Underhill.
* Any use of this library in a commercial context must be approved by the author
* in writing.
* All rights for commercial and/or non-educational purposes, are fully reserved
* by the author.
*/

#ifndef QSC_COMMON_H
#define QSC_COMMON_H

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

/**
* \file common.h
* \brief This file contains common definitions
* \endcode
*/

/* Quantum Secure Cryptographic library in C (QSC) */

/**
* \file common.h
* \brief global definitions and includes.
*/

/*!
\def QSC_SYSTEM_COMPILER_XXX
* \brief The identified compiler
*/
#if defined(_MSC_VER)
#	define QSC_SYSTEM_COMPILER_MSC
#elif defined(__MINGW32__)
#	define QSC_SYSTEM_COMPILER_MINGW
#	define QSC_SYSTEM_COMPILER_GCC
#elif defined(__CC_ARM)
#	define QSC_SYSTEM_COMPILER_ARM
#elif defined(__BORLANDC__)
#	define QSC_SYSTEM_COMPILER_BORLAND
#elif defined(__GNUC__)
#	define QSC_SYSTEM_COMPILER_GCC
#elif defined(__clang__)
#	define QSC_SYSTEM_COMPILER_CLANG
#elif defined(__IBMC__) || defined(__IBMCPP__)
#	define QSC_SYSTEM_COMPILER_IBM
#elif defined(__INTEL_COMPILER) || defined(__ICL)
#	define QSC_SYSTEM_COMPILER_INTEL
#elif defined(__MWERKS__)
#	define QSC_SYSTEM_COMPILER_MWERKS
#elif defined(__OPEN64__)
#	define QSC_SYSTEM_COMPILER_OPEN64
#elif defined(__SUNPRO_C)
#	define QSC_SYSTEM_COMPILER_SUNPRO
#elif defined(__TURBOC__)
#	define QSC_SYSTEM_COMPILER_TURBO
#endif

/*!
\def QSC_SYSTEM_OS_XXX
* \brief The identified operating system
*/
#if defined(_WIN64) || defined(_WIN32) || defined(__WIN64__) || defined(__WIN32__)
#	if !defined(QSC_SYSTEM_OS_WINDOWS)
#		define QSC_SYSTEM_OS_WINDOWS
#	endif
#	if defined(_WIN64)
#		define QSC_SYSTEM_ISWIN64
#	elif defined(_WIN32)
#		define QSC_SYSTEM_ISWIN32
#	endif
#elif defined(__ANDROID__)
#	define QSC_SYSTEM_OS_ANDROID
#elif defined(__APPLE__) || defined(__MACH__)
#	include "TargetConditionals.h"
#	define QSC_SYSTEM_OS_APPLE
#	define QSC_SYSTEM_OS_BSD
#	if defined(TARGET_OS_IPHONE) && defined(TARGET_IPHONE_SIMULATOR)
#		define QSC_SYSTEM_ISIPHONESIM
#	elif TARGET_OS_IPHONE
#		define QSC_SYSTEM_ISIPHONE
#	else
#		define QSC_SYSTEM_ISOSX
#	endif
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(QSC_SYSTEM_ISOSX)
#	define QSC_SYSTEM_OS_BSD
#elif defined(__linux) || defined(__linux__) || defined(__gnu_linux__ )
#	define QSC_SYSTEM_OS_LINUX
    typedef int errno_t;
#elif defined(__unix) || defined(__unix__)
#	define QSC_SYSTEM_OS_UNIX
#	if defined(__hpux) || defined(hpux)
#		define QSC_SYSTEM_OS_HPUX
#	endif
#	if defined(__sun__) || defined(__sun) || defined(sun)
#		define QSC_SYSTEM_OS_SUNUX
#	endif
#endif

#if defined(__posix) || defined(__posix__) || defined(__USE_POSIX) || defined(_POSIX_VERSION) || defined(QSC_SYSTEM_OS_APPLE)
    /*!
    \def QSC_SYSTEM_OS_POSIX
    * \brief The operating system is posix compliant
    */
#	define QSC_SYSTEM_OS_POSIX
#endif

#if defined(QSC_SYSTEM_OS_WINDOWS) && defined(QSC_SYSTEM_COMPILER_MSC)
    /*!
    \def QSC_WINDOWS_VSTUDIO_BUILD
    * \brief The build is MSVC windows
    */
#   define QSC_WINDOWS_VSTUDIO_BUILD
#endif

#if defined(_OPENMP)
#	define QSC_SYSTEM_OPENMP
#endif

#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG__) || (defined(__GNUC__) && !defined(__OPTIMIZE__))
    /*!
	\def QSC_DEBUG_MODE
	* \brief The build is in bedug mode
	*/
#	define QSC_DEBUG_MODE
#endif

/*!
\def QSC_SYSTEM_ARCH_XXX
* \brief The CPU architecture
*/
#if defined(QSC_SYSTEM_COMPILER_MSC)
#	if defined(_M_X64) || defined(_M_AMD64)
#		define QSC_SYSTEM_ARCH_IX86_64
#		define QSC_SYSTEM_ARCH_IX86
#		if defined(_M_AMD64)
#			define QSC_SYSTEM_ARCH_AMD64
#		endif
#	elif defined(_M_IX86) || defined(_X86_)
#		define QSC_SYSTEM_ARCH_IX86_32
#		define QSC_SYSTEM_ARCH_IX86
#	elif defined(_M_ARM)
#		define QSC_SYSTEM_ARCH_ARM
#		if defined(_M_ARM_ARMV7VE)
#			define QSC_SYSTEM_ARCH_ARMV7VE
#		elif defined(_M_ARM_FP)
#			define QSC_SYSTEM_ARCH_ARMFP
#		elif defined(_M_ARM64)
#			define QSC_SYSTEM_ARCH_ARM64
#		endif
#	elif defined(_M_IA64)
#		define QSC_SYSTEM_ARCH_IA64
#	endif
#elif defined(QSC_SYSTEM_COMPILER_GCC)
#	if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#		define QSC_SYSTEM_ARCH_IX86_64
#		define QSC_SYSTEM_ARCH_IX86
#		if defined(_M_AMD64)
#			define QSC_SYSTEM_ARCH_AMD64
#		endif
#	elif defined(i386) || defined(__i386) || defined(__i386__)
#		define QSC_SYSTEM_ARCH_IX86_32
#		define QSC_SYSTEM_ARCH_IX86
#	elif defined(__arm__)
#		define QSC_SYSTEM_ARCH_ARM
#		if defined(__aarch64__)
#			define QSC_SYSTEM_ARCH_ARM64
#		endif
#	elif defined(__ia64) || defined(__ia64__) || defined(__itanium__)
#		define QSC_SYSTEM_ARCH_IA64
#	elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(__64BIT__) || defined(_LP64) || defined(__LP64__)
#		define QSC_SYSTEM_ARCH_PPC
#	elif defined(__sparc) || defined(__sparc__)
#		define QSC_SYSTEM_ARCH_SPARC
#		if defined(__sparc64__)
#			define QSC_SYSTEM_ARCH_SPARC64
#		endif
#	endif
#endif

/*!
\def QSC_SYSTEM_SOCKETS_XXX
* \brief The network sockets architecture
*/
#if defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN__)
#	define QSC_SYSTEM_SOCKETS_WINDOWS
#else
#	define QSC_SYSTEM_SOCKETS_BERKELY
#endif

/*!
\def __attribute__
* \brief Assign an attribute
*/
#if !defined(__clang__) && !defined(__GNUC__)
#	ifdef __attribute__
#		undef __attribute__
#	endif
#	define __attribute__(a)
#endif

/*!
\def QSC_DLL_API
* \brief Enables the dll api exports
*/
#if defined(_DLL)
#	define QSC_DLL_API
#endif
/*!
\def QSC_EXPORT_API
* \brief The api export prefix
*/
#if defined(QSC_DLL_API)
#	if defined(QSC_SYSTEM_COMPILER_MSC)
#		if defined(QSC_DLL_IMPORT)
#			define QSC_EXPORT_API __declspec(dllimport)
#		else
#			define QSC_EXPORT_API __declspec(dllexport)
#		endif
#	elif defined(QSC_SYSTEM_COMPILER_GCC)
#		if defined(QSC_DLL_IMPORT)
#		define QSC_EXPORT_API __attribute__((dllimport))
#		else
#		define QSC_EXPORT_API __attribute__((dllexport))
#		endif
#	else
#		if defined(__SUNPRO_C)
#			if !defined(__GNU_C__)
#				define QSC_EXPORT_API __attribute__ (visibility(__global))
#			else
#				define QSC_EXPORT_API __attribute__ __global
#			endif
#		elif defined(_MSG_VER)
#			define QSC_EXPORT_API extern __declspec(dllexport)
#		else
#			define QSC_EXPORT_API __attribute__ ((visibility ("default")))
#		endif
#	endif
#else
#	define QSC_EXPORT_API
#endif

/*!
\def QSC_CACHE_ALIGNED
* \brief The cache alignment
*/
#if defined(__GNUC__)
#	define QSC_CACHE_ALIGNED __attribute__((aligned(64)))
#elif defined(_MSC_VER)
#	define QSC_CACHE_ALIGNED __declspec(align(64))
#endif

#if defined(QSC_SYSTEM_ARCH_IX86_64) || defined(QSC_SYSTEM_ARCH_ARM64) || defined(QSC_SYSTEM_ARCH_IA64) || defined(QSC_SYSTEM_ARCH_AMD64) || defined(QSC_SYSTEM_ARCH_ARM64) || defined(QSC_SYSTEM_ARCH_SPARC64)
/*!
\def QSC_SYSTEM_IS_X64
* \brief The system is X64
*/
#	define QSC_SYSTEM_IS_X64
#else
/*!
\def QSC_SYSTEM_IS_X86
* \brief The system is X86
*/
#	define QSC_SYSTEM_IS_X86
#endif

/*!
\def QSC_SIZE_MAX
* \brief The maximum system integer size
*/
#if defined(QSC_SYSTEM_IS_X64)
#	define QSC_SIZE_MAX UINT64_MAX
#else
#	define QSC_SIZE_MAX UINT32_MAX
#endif

/*!
\def QSC_SYSTEM_IS_LITTLE_ENDIAN
* \brief The system is little endian
*/
#define QSC_SYSTEM_IS_LITTLE_ENDIAN (((union { uint32_t x; uint8_t c; }){1}).c)

#if (!defined(QSC_SYSTEM_IS_LITTLE_ENDIAN))
#	if defined(__sparc) || defined(__sparc__) || defined(__hppa__) || defined(__PPC__) || defined(__mips__) || defined(__MWERKS__) && (!defined(__INTEL__))
		/*!
		\def QSC_SYSTEM_IS_BIG_ENDIAN
		* \brief The system is big endian
		*/
#		define QSC_SYSTEM_IS_BIG_ENDIAN
#	else
		/*!
		\def QSC_SYSTEM_IS_LITTLE_ENDIAN
		* \brief The system is little endian
		*/
#		define QSC_SYSTEM_IS_LITTLE_ENDIAN
#	endif
#endif

/*!
\def QSC_ALIGN
* \brief Align an integer
*/
#if !defined(QSC_ALIGN)
#	if defined(__GNUC__) || defined(__clang__)
#		define QSC_ALIGN(x)  __attribute__((aligned(x)))
#	elif defined(_MSC_VER)
#		define QSC_ALIGN(x)  __declspec(align(x))
#	else
#		define QSC_ALIGN(x)
#	endif
#endif

/*!
\def uint128_t
* \brief 128-bit uint32_t integer support
*/
#if defined(__SIZEOF_INT128__) && defined(QSC_SYSTEM_IS_X64) && !defined(__xlc__) && ! defined(uint128_t)
#	define QSC_SYSTEM_NATIVE_UINT128
	/* Prefer TI mode over __int128 as GCC rejects the latter in pedantic mode */
#	if defined(__GNUC__) /* was __GNUG__? */
		typedef uint32_t uint128_t __attribute__((mode(TI)));
#	else
		typedef __int128 uint128_t;
#	endif
#endif

/*!
\def QSC_SYSTEM_FAST_64X64_MUL
* \brief Fast 64-bit integer multiplication
*/
#if defined(QSC_SYSTEM_NATIVE_UINT128)
#	define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)			\
	do {													\
      const uint128_t r = (uint128_t)(X) * Y;	\
      *High = (r >> 64) & 0xFFFFFFFFFFFFFFFFULL;			\
      *Low = (r) & 0xFFFFFFFFFFFFFFFFULL;					\
	} while(0)

#elif defined(QSC_SYSTEM_COMPILER_MSC) && defined(QSC_SYSTEM_IS_X64)
#	include <intrin.h>
#	pragma intrinsic(_umul128)
#	define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)			\
	do {													\
		*Low = _umul128(X, Y, High);						\
	} while(0)

#elif defined(QSC_SYSTEM_COMPILER_GCC)
#	if defined(QSC_SYSTEM_ARCH_IX86)
#		define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)							\
		do {																	\
		asm("mulq %3" : "=d" (*High), "=X" (*Low) : "X" (X), "rm" (Y) : "cc");	\
		} while(0)
#	elif defined(QSC_SYSTEM_ARCH_ALPHA)
#		define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)							\
		do {																	\
		asm("umulh %1,%2,%0" : "=r" (*High) : "r" (X), "r" (Y));				\
		*Low = X * Y;															\
		} while(0)
#	elif defined(QSC_SYSTEM_ARCH_IA64)
#		define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)							\
		do {																	\
		asm("xmpy.hu %0=%1,%2" : "=f" (*High) : "f" (X), "f" (Y));				\
		*Low = X * Y;															\
		} while(0)
#	elif defined(QSC_SYSTEM_ARCH_PPC)
#		define QSC_SYSTEM_FAST_64X64_MUL(X,Y,Low,High)							\
		do {																	\
		asm("mulhdu %0,%1,%2" : "=r" (*High) : "r" (X), "r" (Y) : "cc");		\
		*Low = X * Y;															\
		} while(0)
#	endif
#endif

/*!
\def QSC_SYSTEM_MAX_PATH
* \brief The maximum path length
*/
#define QSC_SYSTEM_MAX_PATH 260

/*!
\def QSC_SYSTEM_SECMEMALLOC_DEFAULT
* \brief The secure memory default buffer allocation
*/
#define QSC_SYSTEM_SECMEMALLOC_DEFAULT 4096

/*!
\def QSC_SYSTEM_SECMEMALLOC_MIN
* \brief The minimum secure memory allocation
*/
#define QSC_SYSTEM_SECMEMALLOC_MIN 16

/*!
\def QSC_SYSTEM_SECMEMALLOC_MAX
* \brief The maximum secure memory allocation
*/
#define QSC_SYSTEM_SECMEMALLOC_MAX 128

/*!
\def QSC_SYSTEM_SECMEMALLOC_MAXKB
* \brief The secure memory maximum allocation in kilobytes
*/
#define QSC_SYSTEM_SECMEMALLOC_MAXKB 512

#if defined(_WIN32)
	/*!
	\def QSC_SYSTEM_VIRTUAL_LOCK
	* \brief The system has virtual memory allocation
	*/
#	define QSC_SYSTEM_VIRTUAL_LOCK

	/*!
	\def QSC_RTL_SECURE_MEMORY
	* \brief The system has secure memory allocation
	*/
#	define QSC_RTL_SECURE_MEMORY
#endif

#if defined(_POSIX_MEMLOCK_RANGE)
	/*!
	\def QSC_SYSTEM_POSIX_MLOCK
	* \brief The memory has posix lock
	*/
#	define QSC_SYSTEM_POSIX_MLOCK
#endif

#if defined(QSC_SYSTEM_VIRTUAL_LOCK) || defined(QSC_SYSTEM_POSIX_MLOCK)
	/*!
	\def QSC_SYSTEM_SECURE_ALLOCATOR
	* \brief The system has a secure memory allocator
	*/
#	define QSC_SYSTEM_SECURE_ALLOCATOR
#endif

/*!
\def QSC_SYSTEM_OPTIMIZE_IGNORE
* \brief Compiler hint to stop optimizing code
*/
#if defined(QSC_SYSTEM_COMPILER_MSC)
#	define QSC_SYSTEM_OPTIMIZE_IGNORE __pragma(optimize("", off))
#elif defined(QSC_SYSTEM_COMPILER_GCC) || defined(QSC_SYSTEM_COMPILER_MINGW)
#if defined(__clang__)
#	define QSC_SYSTEM_OPTIMIZE_IGNORE __attribute__((optnone))
#else
#	define QSC_SYSTEM_OPTIMIZE_IGNORE __attribute__((optimize("O0")))
#endif
#elif defined(QSC_SYSTEM_COMPILER_CLANG)
#	define QSC_SYSTEM_OPTIMIZE_IGNORE __attribute__((optnone))
#elif defined(QSC_SYSTEM_COMPILER_INTEL)
#	define QSC_SYSTEM_OPTIMIZE_IGNORE pragma optimize("", off)
#else
#	define QSC_SYSTEM_OPTIMIZE_IGNORE
#endif

/*!
\def QSC_SYSTEM_OPTIMIZE_IGNORE
* \brief Compiler hint to continue optimizing code
*/
#if defined(QSC_SYSTEM_COMPILER_MSC)
#	define QSC_SYSTEM_OPTIMIZE_RESUME __pragma(optimize("", on))
#elif defined(QSC_SYSTEM_COMPILER_GCC) || defined(QSC_SYSTEM_COMPILER_MINGW)
#if defined(__clang__)
#	define QSC_SYSTEM_OPTIMIZE_RESUME
#else
#	define QSC_SYSTEM_OPTIMIZE_RESUME _Pragma("GCC diagnostic pop")
#endif
#elif defined(CEX_COMPILER_INTEL)
#	define QSC_SYSTEM_OPTIMIZE_RESUME pragma optimize("", on)
#else
#	define QSC_SYSTEM_OPTIMIZE_RESUME
#endif

/*!
\def QSC_SYSTEM_OPTIMIZE_IGNORE
* \brief Compiler hint to ignore a condition in code
*/
#if defined(QSC_SYSTEM_COMPILER_MSC)
#	define QSC_SYSTEM_CONDITION_IGNORE(x) __pragma(warning(disable : x))
#elif defined(QSC_SYSTEM_COMPILER_GCC) || defined(QSC_SYSTEM_COMPILER_MINGW)
#	define QSC_SYSTEM_CONDITION_IGNORE(x) _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
#elif defined(CEX_COMPILER_INTEL)
#	define QSC_SYSTEM_CONDITION_IGNORE(x)
#else
#	define QSC_SYSTEM_CONDITION_IGNORE(x)
#endif

/* intrinsics support level */

#if (_MSC_VER >= 1600)
	/*!
	\def QSC_WMMINTRIN_H
	* \brief The CPU supports SIMD instructions
	*/
#	define QSC_WMMINTRIN_H 1
#endif
#if (_MSC_VER >= 1700) && (defined(_M_X64))
	/*!
	\def QSC_HAVE_AVX2INTRIN_H
	* \brief The CPU supports AVX2
	*/
#	define QSC_HAVE_AVX2INTRIN_H 1
#endif

/*
* AVX512 Capabilities Check
* https://software.intel.com/en-us/intel-cplusplus-compiler-16.0-user-and-reference-guide
* https://software.intel.com/en-us/articles/compiling-for-the-intel-xeon-phi-processor-and-the-intel-avx-512-isa
* https://colfaxresearch.com/knl-avx512/
*
* #include <immintrin.h>
* supported is 1: ex. __AVX512CD__ 1
* F		__AVX512F__					Foundation
* CD	__AVX512CD__				Conflict Detection Instructions(CDI)
* ER	__AVX512ER__				Exponential and Reciprocal Instructions(ERI)
* PF	__AVX512PF__				Pre-fetch Instructions(PFI)
* DQ	__AVX512DQ__				Double-word and Quadword Instructions(DQ)
* BW	__AVX512BW__				Byte and Word Instructions(BW)
* VL	__AVX512VL__				Vector Length Extensions(VL)
* IFMA	__AVX512IFMA__				Integer Fused Multiply Add(IFMA)
* VBMI	__AVX512VBMI__				Vector Byte Manipulation Instructions(VBMI)
* VNNIW	__AVX5124VNNIW__			Vector instructions for deep learning enhanced word variable precision
* FMAPS	__AVX5124FMAPS__			Vector instructions for deep learning floating - point single precision
* VPOPCNT	__AVX512VPOPCNTDQ__		?
*
* Note: AVX512 is currently untested, this flag enables support on a compliant system
*/

/* Enable this define to support AVX512 on a compatible system */
/*#define CEX_AVX512_SUPPORTED*/

#if defined(__AVX512F__) && (__AVX512F__ == 1)
		/*!
		\def __AVX512__
		* \brief The system supports AVX512 instructions
		*/
#	include <immintrin.h>
#	if (!defined(__AVX512__))
#		define __AVX512__
#	endif
#endif

#if defined(__SSE2__)
	/*!
	\def QSC_SYSTEM_HAS_SSE2
	* \brief The system supports SSE2 instructions
	*/
#	define QSC_SYSTEM_HAS_SSE2
#endif

#if defined(__SSE3__)
	/*!
	\def QSC_SYSTEM_HAS_SSE3
	* \brief The system supports SSE3 instructions
	*/
#	define QSC_SYSTEM_HAS_SSE3
#endif

#if defined(__SSSE3__)
	/*!
	\def QSC_SYSTEM_HAS_SSSE3
	* \brief The system supports SSSE3 instructions
	*/
#	define QSC_SYSTEM_HAS_SSSE3
#endif

#if defined(__SSE4_1__)
	/*!
	\def QSC_SYSTEM_HAS_SSE41
	* \brief The system supports SSE41 instructions
	*/
#	define QSC_SYSTEM_HAS_SSE41
#endif

#if defined(__SSE4_2__)
	/*!
	\def QSC_SYSTEM_HAS_SSE42
	* \brief The system supports SSE42 instructions
	*/
#	define QSC_SYSTEM_HAS_SSE42
#endif

#if defined(__AVX__)
	/*!
	\def QSC_SYSTEM_HAS_AVX
	* \brief The system supports AVX instructions
	*/
#	define QSC_SYSTEM_HAS_AVX
#endif

#if defined(__AVX2__)
	/*!
	\def QSC_SYSTEM_HAS_AVX2
	* \brief The system supports AVX2 instructions
	*/
#	define QSC_SYSTEM_HAS_AVX2
#endif

#if defined(__AVX512__)
	/*!
	\def QSC_SYSTEM_HAS_AVX512
	* \brief The system supports AVX512 instructions
	*/
#	define QSC_SYSTEM_HAS_AVX512
#endif
#if defined(__XOP__)
#	define QSC_SYSTEM_HAS_XOP
#endif

#if defined(QSC_SYSTEM_HAS_AVX) || defined(QSC_SYSTEM_HAS_AVX2) || defined(QSC_SYSTEM_HAS_AVX512)
	/*!
	\def QSC_SYSTEM_AVX_INTRINSICS
	* \brief The system supports AVX instructions
	*/
#	define QSC_SYSTEM_AVX_INTRINSICS
#endif

/*!
*\def QSC_ASM_ENABLED
* \brief Enables global ASM processing
*/
//#define QSC_ASM_ENABLED

/*!
*\def QSC_GCC_ASM_ENABLED
* \brief Enables GCC ASM processing
*/
#if defined(QSC_SYSTEM_AVX_INTRINSICS) && defined(QSC_SYSTEM_COMPILER_GCC) && defined(QSC_ASM_ENABLED)
/* #	define QSC_GCC_ASM_ENABLED */
#endif

/*!
\def QSC_SIMD_ALIGN
* \brief Align an array by SIMD instruction width
*/
#if defined(QSC_SYSTEM_HAS_AVX512)
#	define QSC_SIMD_ALIGN QSC_ALIGN(64)
#	define QSC_SIMD_ALIGNMENT 64
#elif defined(QSC_SYSTEM_HAS_AVX2)
#	define QSC_SIMD_ALIGN QSC_ALIGN(32)
#	define QSC_SIMD_ALIGNMENT 32
#elif defined(QSC_SYSTEM_HAS_AVX)
#	define QSC_SIMD_ALIGN QSC_ALIGN(16)
#	define QSC_SIMD_ALIGNMENT 16
#else
#	define QSC_SIMD_ALIGN
#	define QSC_SIMD_ALIGNMENT 8
#endif

#if defined(QSC_SYSTEM_AVX_INTRINSICS)
/*!
* \def QSC_RDRAND_COMPATIBLE
* \brief The system has an RDRAND compatible CPU
*/
#	define QSC_RDRAND_COMPATIBLE
#endif

/*!
\def QSC_STATUS_SUCCESS
* Function return value indicates successful operation
*/
#define QSC_STATUS_SUCCESS 0

/*!
\def QSC_STATUS_FAILURE
* Function return value indicates failed operation
*/
#define QSC_STATUS_FAILURE -1


/* User Modifiable Values
* Modifiable values that determine which parameter sets and options get compiled.
* These values can be tuned by the user to enable/disable features for a specific environment, or hardware configuration.
* This list also includes the asymmetric cipher and signature scheme parameter set options.
*/

/*!
\def QSC_SYSTEM_AESNI_ENABLED
* Enable the use of intrinsics and the AES-NI implementation.
* Just for testing, add the QSC_SYSTEM_AESNI_ENABLED preprocessor definition and enable SIMD and AES-NI.
*/
#if !defined(QSC_SYSTEM_AESNI_ENABLED)
#	if defined(QSC_SYSTEM_AVX_INTRINSICS)
#		define QSC_SYSTEM_AESNI_ENABLED
#	endif
#endif

/*!
* \def QSC_KECCAK_UNROLLED_PERMUTATION
* \brief Define to use the UNROLLED form of the Keccak permutation function
* if undefined, functions use the compact form of the Keccak permutation
*/
/* #define QSC_KECCAK_UNROLLED_PERMUTATION */

/*** Asymmetric Ciphers ***/

/*** ECDH ***/

/*!
\def QSC_ECDH_S1EC25519
* Implement the ECDH S1EC25519 parameter set
*/
#define QSC_ECDH_S1EC25519

/*** Kyber ***/

/*!
\def QSC_KYBER_S1P1632
* Implement the Kyber S1-P1632 parameter set
*/
#define QSC_KYBER_S1P1632

/*!
\def QSC_KYBER_S3P2400
* Implement the Kyber S3-P2400 parameter set
*/
/*#define QSC_KYBER_S3P2400*/

/*!
\def QSC_KYBER_S5P3168
* Implement the Kyber S5-P3168 parameter set
*/
/*#define QSC_KYBER_S5P3168*/

/*!
\def QSC_KYBER_S6P3936
* Implement the Kyber S6-P3936 parameter set
* /warning Experimental, not an official parameter
*/
/*#define QSC_KYBER_S6P3936*/

/*** McEliece ***/

/*!
\def QSC_MCELIECE_S1N3488T64
* Implement the McEliece S1-N3488T64 parameter set
*/
/*#define QSC_MCELIECE_S1N3488T64*/

/*!
\def QSC_MCELIECE_S3N4608T96
* Implement the McEliece S3-N4608T96 parameter set
*/
/*#define QSC_MCELIECE_S3N4608T96*/

/*!
\def QSC_MCELIECE_S5N6688T128
* Implement the McEliece S5-N6688T128 parameter set
*/
/*#define QSC_MCELIECE_S5N6688T128*/

/*!
\def QSC_MCELIECE_S6N6960T119
* Implement the McEliece S6-N6960T119 parameter set
*/
/*#define QSC_MCELIECE_S6N6960T119*/

/*!
\def QSC_MCELIECE_S7N8192T128
* Implement the McEliece S5-N8192T128 parameter set
*/
#define QSC_MCELIECE_S7N8192T128

/*** NTRU ***/

/*!
\def QSC_NTRU_S1HPS2048509
* Implement the NTRU S1HPS2048509 parameter set
*/
/*#define QSC_NTRU_S1HPS2048509*/

/*!
\def QSC_NTRU_S3HPS2048677
* Implement the NTRU HPSS32048677 parameter set
*/
/*#define QSC_NTRU_S3HPS2048677*/

/*!
\def QSC_NTRU_S5HPS4096821
* Implement the NTRU S5HPS4096821 parameter set
*/
#define QSC_NTRU_S5HPS4096821

/*!
\def QSC_NTRU_S5HRSS701
* Implement the NTRU S5HRSS701 parameter set
*/
/*#define QSC_NTRU_S5HRSS701*/

/*** Signature Schemes ***/

/*** Dilithium ***/

/*!
\def QSC_DILITHIUM_S1P2544
* Implement the Dilithium S1P2544 parameter set
*/
#define QSC_DILITHIUM_S1P2544

/*!
\def QSC_DILITHIUM_S3P4016
* Implement the Dilithium S3P4016 parameter set
*/
/*#define QSC_DILITHIUM_S3P4016*/

/*!
\def QSC_DILITHIUM_S5P4880
* Implement the Dilithium S5P4880 parameter set
*/
/*#define QSC_DILITHIUM_S5P4880*/

/*** ECDSA ***/

/*!
\def QSC_ECDSA_S1EC25519
* Implement the ECDSA S1EC25519 parameter set
*/
#define QSC_ECDSA_S1EC25519

/*** Falcon ***/

/*!
\def QSC_FALCON_S3SHAKE256F512
* Implement the Falcon S3SHAKE256F512 parameter set
*/
/*#define QSC_FALCON_S3SHAKE256F512*/

/*!
\def QSC_FALCON_S5SHAKE256F1024
* Implement the Falcon S5SHAKE256F1024 parameter set
*/
#define QSC_FALCON_S5SHAKE256F1024

/*** SphincsPlus ***/

/*!
\def QSC_SPHINCSPLUS_S1S128SHAKERF
* Implement the SphincsPlus S1S128SHAKERF robust fast parameter set
*/
/*#define QSC_SPHINCSPLUS_S1S128SHAKERF*/

/*!
\def QSC_SPHINCSPLUS_S1S128SHAKERS
* Implement the SphincsPlus S1S128SHAKERS robust small parameter set
*/
/*#define QSC_SPHINCSPLUS_S1S128SHAKERS*/

/*!
\def QSC_SPHINCSPLUS_S3S192SHAKERF
* Implement the SphincsPlus S3S192SHAKERF robust fast parameter set
*/
/*#define QSC_SPHINCSPLUS_S3S192SHAKERF*/

/*!
\def QSC_SPHINCSPLUS_S3S192SHAKERS
* Implement the SphincsPlus S3S192SHAKERS robust small parameter set
*/
/*#define QSC_SPHINCSPLUS_S3S192SHAKERS*/

/*!
\def QSC_SPHINCSPLUS_S5S256SHAKERF
* Implement the SphincsPlus S5S256SHAKERF robust fast parameter set
*/
#define QSC_SPHINCSPLUS_S5S256SHAKERF

/*!
\def QSC_SPHINCSPLUS_S5S256SHAKERS
* Implement the SphincsPlus S5S256SHAKERS robust small parameter set
*/
/*#define QSC_SPHINCSPLUS_S5S256SHAKERS*/

/*!
\def QSC_SPHINCSPLUS_S6S512SHAKERF
* Implement the SphincsPlus S6S512SHAKERF robust fast parameter set
*/
/*#define QSC_SPHINCSPLUS_S6S512SHAKERF*/

/*!
\def QSC_SPHINCSPLUS_S6S512SHAKERS
* Implement the SphincsPlus S6S512SHAKERS robust small parameter set
*/
/*#define QSC_SPHINCSPLUS_S6S512SHAKERS*/

#endif
