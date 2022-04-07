#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([birb2d], [0.2.1], [git@toasterbirb.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AM_PROG_AR
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_MAKE_SET

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lSDL2':
AC_CHECK_LIB([SDL2], [main])
# FIXME: Replace 'main' with a function in '-lSDL2_gfx':
AC_CHECK_LIB([SDL2_gfx], [main])
# FIXME: Replace 'main' with a function in '-lSDL2_image':
AC_CHECK_LIB([SDL2_image], [main])
# FIXME: Replace 'main' with a function in '-lSDL2_mixer':
AC_CHECK_LIB([SDL2_mixer], [main])
# FIXME: Replace 'main' with a function in '-lSDL2_ttf':
AC_CHECK_LIB([SDL2_ttf], [main])
# FIXME: Replace 'main' with a function in '-lSDL2main':
AC_CHECK_LIB([SDL2main], [main])
# FIXME: Replace 'main' with a function in '-lbirb2d':
AC_CHECK_LIB([birb2d], [main])

# Checks for header files.
AC_CHECK_HEADERS([sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor gettimeofday pow sqrt strrchr strstr])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/tests/Makefile])

LT_INIT

AC_OUTPUT
