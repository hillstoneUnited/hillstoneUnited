#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT(hillstoneUnited/main.cpp)
AM_INIT_AUTOMAKE(hillstoneUnited, 0.5)
AC_CONFIG_SRCDIR([hillstoneUnited/main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# AX_BOOST_BASE([1.34.1])
AX_BOOST_REGEX
AC_PATH_PROGS(OXYGEN_CFG,[oxygen-config],no)
if test $OXYGEN_CFG = "no"; then
   AC_ERROR([need rcssserver3d devel library to compileagentspark-lite])
else
	rcss_prefix=`$OXYGEN_CFG --prefix`
	rcss_cppflags=`$OXYGEN_CFG --cflags`
	CPPFLAGS="$CPPFLAGS $rcss_cppflags"
	#RCSS3D_LDFLAGS="-L${rcss_prefix}/lib/rcssserver3d"
	#RCSS3D_LDFLAGS="-L/usr/lib/simspark"
	RCSS3D_LDFLAGS="-L/usr/local/lib/simspark"
	AC_SUBST(RCSS3D_LDFLAGS)
fi

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h string.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_CHECK_FUNCS([select strerror])

AC_CONFIG_FILES([Makefile
	hillstoneUnited/Makefile])

AC_PROG_RANLIB
AC_OUTPUT
