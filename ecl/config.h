/*
    config.h.in -- Template configuration file.
*/
/*
    Copyright (c) 1990, Giuseppe Attardi.
    Copyright (c) 2001, Juan Jose Garcia Ripoll.

    ECoLisp is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    See file '../Copyright' for full details.
*/

#define ECL_MS_WINDOWS_HOST

/*
 * If ECL_API has been predefined, that means we are building the core
 * library and, under windows, we must tell the compiler to export
 * extern functions from the shared library.
 * If ECL_API is not defined, we are simply building an application that
 * uses ECL and, under windows, we must tell the compiler that certain
 * will be imported from a DLL.
 */
#if defined(mingw32) || defined(_MSC_VER) || defined(cygwin)
# define ECL_DLLEXPORT __declspec(dllexport)
# ifdef ECL_API
#  undef ECL_API
#  define ECL_API __declspec(dllexport)
# else
#  define ECL_API __declspec(dllimport)
# endif
#else
# define ECL_DLLEXPORT
# ifdef ECL_API
#  undef ECL_API
# endif
# define ECL_API
#endif

/* Decimal number made with the formula yymmvv */
#define ECL_VERSION_NUMBER 121201

/*
 * FEATURES LINKED IN
 */
/* Always use CLOS							*/
#define CLOS

/* Use GNU Multiple Precision library for bignums                       */ 
#define WITH_GMP 1
#include <ecl/gmp.h>

/* Userland threads?							*/
#define ECL_THREADS 1
#if ECL_THREADS
# define GC_WIN32_THREADS
# define GC_THREADS
# define ECL_WINDOWS_THREADS
#else
# undef ECL_THREADS
#endif

/* __thread thread-local variables?                                     */
/* #undef WITH___THREAD */

/* Use Windows's interlocked operations to define compare-and-swap      */
#define AO_ASSUME_WINDOWS98

/* Use Boehm's garbage collector					*/
#define GBC_BOEHM 0
#ifdef GBC_BOEHM
# define GC_WIN32_THREADS	/* For older versions */
# define GC_THREADS             /* For >= 7.2 */
# include <ecl/gc/gc.h>
# define ECL_DYNAMIC_VV
#endif
#define ECL_LIBATOMIC_OPS_H

/* Network streams							*/
#define TCP 1
#if defined(TCP) && (defined(_MSC_VER) || defined(mingw32))
# define ECL_WSOCK
#endif

/* Foreign functions interface						*/
#define ECL_FFI

/* Support for Unicode strings */
#define ECL_UNICODE 21
#if !ECL_UNICODE
# undef ECL_UNICODE
#endif

/* Allow STREAM operations to work on arbitrary objects			*/
#define ECL_CLOS_STREAMS 1

/* Stack grows downwards						*/
#define ECL_DOWN_STACK 1

/* We have libffi and can use it                                        */
/*#undef HAVE_LIBFFI*/

/* We have non-portable implementation of FFI calls			*/
#ifndef _M_X64
# define ECL_DYNAMIC_FFI 1
#endif

/* We use hierarchical package names, like in Allegro CL                */
#define ECL_RELATIVE_PACKAGE_NAMES 1

/* Use mprotect for fast interrupt dispatch				*/
/* #undef ECL_USE_MPROTECT */
#if defined(_MSC_VER) || defined(mingw32)
# define ECL_USE_GUARD_PAGE
#endif

/* Integer types                        				*/
#define ecl_uint8_t unsigned char
#define ecl_int8_t char
#define ecl_uint16_t unsigned short
#define ecl_int16_t short
#define ecl_uint32_t unsigned int
#define ecl_int32_t int
#define ecl_uint64_t unsigned __int64
#define ecl_int64_t __int64
#define ecl_long_long_t long long
#define ecl_ulong_long_t unsigned long long

/*
 * C TYPES AND SYSTEM LIMITS
 */
/*
 * The integer type
 *
 * cl_fixnum must be an integer type, large enough to hold a pointer.
 * Ideally, according to the ISOC99 standard, we should use intptr_t,
 * but the required headers are not present in all systems. Hence we
 * use autoconf to guess the following values.
 */
#ifdef _M_X64
#define ECL_INT_BITS		64
#define ECL_LONG_BITS		32
#define FIXNUM_BITS		64
#define MOST_POSITIVE_FIXNUM	((cl_fixnum)2305843009213693951LL)
#define MOST_NEGATIVE_FIXNUM	((cl_fixnum)-2305843009213693952LL)
typedef long long cl_fixnum;
typedef unsigned long long cl_index;
typedef unsigned long long cl_hashkey;
#else
#define ECL_INT_BITS		32
#define ECL_LONG_BITS		32
#define FIXNUM_BITS		32
#define MOST_POSITIVE_FIXNUM	((cl_fixnum)536870911)
#define MOST_NEGATIVE_FIXNUM	((cl_fixnum)-536870912)
typedef int cl_fixnum;
typedef unsigned int cl_index;
typedef unsigned int cl_hashkey;
#endif

/*
 * The character type
 */
#ifdef ECL_UNICODE
#define	ECL_CHAR_CODE_LIMIT	1114112	/*  unicode character code limit  */
#else
#define	ECL_CHAR_CODE_LIMIT	256	/*  unicode character code limit  */
#endif
typedef int ecl_character;
typedef unsigned char ecl_base_char;

/*
 * Array limits
 */
#define	ECL_ARRAY_RANK_LIMIT 64
#ifdef GBC_BOEHM
#define	ECL_ARRAY_DIMENSION_LIMIT 536870911
#else
#define ECL_ARRAY_DIMENSION_LIMIT 16*1024*1024
#endif
#define ECL_ARRAY_TOTAL_LIMIT ECL_ARRAY_DIMENSION_LIMIT

/*
 * Function limits.
 *
 * In general, any of these limits must fit in a "signed int".
 */
/*	Maximum number of function arguments 				*/
#define ECL_CALL_ARGUMENTS_LIMIT 65536

/*	Maximum number of required arguments				*/
#define ECL_LAMBDA_PARAMETERS_LIMIT ECL_CALL_ARGUMENTS_LIMIT

/*	Numb. of args. which can be passed using the C stack		*/
/*	See cmplam.lsp if you change this value				*/
#define ECL_C_ARGUMENTS_LIMIT 64

/*	Maximum number of output arguments				*/
#define ECL_MULTIPLE_VALUES_LIMIT 64

/* A setjmp that does not save signals					*/
#define ecl_setjmp	setjmp
#define ecl_longjmp	longjmp

/*
 * Structure/Instance limits. The index to a slot must fit in the
 * "int" type. We also require ECL_SLOTS_LIMIT <= CALL_ARGUMENTS_LIMIT
 * because constructors typically require as many arguments as slots,
 * or more.
 */
#define ECL_SLOTS_LIMIT	32768

/* compiler understands long double                                     */
/* #undef ECL_LONG_FLOAT */
/* compiler understands complex                                         */
/* #undef HAVE_DOUBLE_COMPLEX */
/* #undef HAVE_FLOAT_COMPLEX */

/* Missing integer types */
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/* We can use small, two-words conses, without type information		*/
/* #undef ECL_SMALL_CONS */

#define ECL_INLINE
#define ecl_likely(form) (form)
#define ecl_unlikely(form) (form)
#define ecl_attr_noreturn

#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#define ECL_SSE2 0
#if !ECL_SSE2
#undef ECL_SSE2
#endif
#endif


