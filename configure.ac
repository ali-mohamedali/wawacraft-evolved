#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([wawacraft-evolved], [0.3.11], [someguyshutup5@gmail.com])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([GLFW], [glfw3], [], [AC_MSG_ERROR([GLFW3 not installed.])])

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdint.h])

AC_SUBST([GLFW_CFLAGS])
AC_SUBST([GLFW_LIBS])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset pow sqrt strstr strtol])

AC_CONFIG_FILES([Makefile archive/Makefile archive/screenshots/Makefile shaders/Makefile textures/Makefile path.cpp])
AC_OUTPUT
