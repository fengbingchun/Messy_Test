dnl Process this file with autoconf to produce a configure script

AC_INIT([GLPK], [4.65], [bug-glpk@gnu.org])

AC_CONFIG_SRCDIR([src/glpk.h])

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

AC_CONFIG_HEADERS([config.h])

AC_ARG_WITH(gmp,
AC_HELP_STRING([--with-gmp],
   [use GNU MP bignum library [[default=no]]]),
   [case $withval in
      yes | no) ;;
      *) AC_MSG_ERROR([invalid value `$withval' for --with-gmp]);;
      esac],
   [with_gmp=no])

AC_ARG_ENABLE(dl,
AC_HELP_STRING([--enable-dl],
   [enable shared library support [[default=no]]]),
   [case $enableval in
      yes | ltdl | dlfcn | no) ;;
      *) AC_MSG_ERROR([invalid value `$enableval' for --enable-dl]);;
      esac],
   [enable_dl=no])

AC_ARG_ENABLE(odbc,
AC_HELP_STRING([--enable-odbc],
   [enable MathProg ODBC support [[default=no]]]),
   [case $enableval in
      yes | unix | no) ;;
      *) AC_MSG_ERROR([invalid value `$enableval' for --enable-odbc]);;
      esac],
   [enable_odbc=no])

AC_ARG_ENABLE(mysql,
AC_HELP_STRING([--enable-mysql],
   [enable MathProg MySQL support [[default=no]]]),
   [case $enableval in
      yes | no) ;;
      *) AC_MSG_ERROR([invalid value `$enableval' for --enable-mysql]);;
      esac],
   [enable_mysql=no])

AC_ARG_ENABLE(reentrant,
AC_HELP_STRING([--enable-reentrant],
   [enable reentrancy support [[default=yes]]]),
   [case $enableval in
      yes | no) ;;
      *) AC_MSG_ERROR(
         [invalid value `$enableval' for --enable-reentrant]);;
      esac],
   [enable_reentrant=yes])

dnl Disable unnecessary libtool tests
define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])
define([AC_LIBTOOL_LANG_GCJ_CONFIG], [:])

dnl Check for programs
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

dnl Check for math library
AC_CHECK_LIB([m], [exp])

dnl Check for <sys/time.h> header
AC_CHECK_HEADER([sys/time.h],
   AC_DEFINE([HAVE_SYS_TIME_H], [1], [N/A]))

dnl Check for gettimeofday function
AC_CHECK_FUNC([gettimeofday],
   AC_DEFINE([HAVE_GETTIMEOFDAY], [1], [N/A]))

dnl Check for <gmp.h> header
if test "$with_gmp" = "yes"; then
   AC_CHECK_HEADER([gmp.h], [],
      [AC_MSG_ERROR([gmp.h header not found])])
fi

AC_MSG_CHECKING([whether to use GNU MP bignum library])
if test "$with_gmp" = "yes"; then
   AC_MSG_RESULT([yes])
   AC_DEFINE([HAVE_GMP], [1], [N/A])
   LIBS="-lgmp $LIBS"
else
   AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING([whether to enable shared library support])
if test "$enable_dl" = "yes"; then
   AC_MSG_RESULT([ltdl])
   AC_DEFINE([HAVE_LTDL], [1], [N/A])
   LIBS="-lltdl $LIBS"
elif test "$enable_dl" = "ltdl"; then
   AC_MSG_RESULT([ltdl])
   AC_DEFINE([HAVE_LTDL], [1], [N/A])
   LIBS="-lltdl $LIBS"
elif test "$enable_dl" = "dlfcn"; then
   AC_MSG_RESULT([dlfcn])
   AC_DEFINE([HAVE_DLFCN], [1], [N/A])
else
   AC_MSG_RESULT([no])
fi

case $host_os in
   darwin* | macosx*)
      LIBIODBC="libiodbc.dylib"
      LIBODBC="libodbc.dylib"
      LIBMYSQL="libmysqlclient.dylib"
      ;;
   *)
      LIBIODBC="libiodbc.so"
      LIBODBC="libodbc.so"
      LIBMYSQL="libmysqlclient.so"
      ;;
esac

AC_MSG_CHECKING([whether to enable MathProg ODBC support])
if test "$enable_odbc" = "yes"; then
   if test "$enable_dl" = "no"; then
      AC_MSG_ERROR([--enable-odbc requires --enable-dl])
   fi
   AC_MSG_RESULT([yes])
   CFLAGS="$(iodbc-config --cflags) $CFLAGS"
   AC_DEFINE_UNQUOTED([ODBC_DLNAME], ["$LIBIODBC"], [N/A])
elif test "$enable_odbc" = "unix"; then
   if test "$enable_dl" = "no"; then
      AC_MSG_ERROR([--enable-odbc requires --enable-dl])
   fi
   AC_MSG_RESULT([unix])
   AC_DEFINE_UNQUOTED([ODBC_DLNAME], ["$LIBODBC"], [N/A])
else
   AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING([whether to enable MathProg MySQL support])
if test "$enable_mysql" = "yes"; then
   if test "$enable_dl" = "no"; then
      AC_MSG_ERROR([--enable-mysql requires --enable-dl])
   fi
   AC_MSG_RESULT([yes])
   CPPFLAGS="-I/usr/include/mysql $CPPFLAGS"
   AC_DEFINE_UNQUOTED([MYSQL_DLNAME], ["$LIBMYSQL"], [N/A])
else
   AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING([whether to enable reentrancy support])
if test "$enable_reentrant" = "yes"; then
   AC_MSG_RESULT([yes])
   AC_MSG_CHECKING([for thread local storage (TLS) class specifier])
   keywords="_Thread_local __thread __declspec(thread)"
   tls=none
   for tls_keyword in $keywords; do
      AC_COMPILE_IFELSE([AC_LANG_SOURCE([
         #include <stdlib.h>
         static void foo(void)
         {  static ] $tls_keyword [ int bar;
            exit(1);
         }])], [tls=$tls_keyword; break], [])
   done
   AC_MSG_RESULT($tls)
   if test "$tls" != "none"; then
      AC_DEFINE_UNQUOTED([TLS], $tls, [N/A])
   else
      AC_MSG_ERROR([Reentrancy needs complier support for TLS])
   fi
else
   AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING(
   [if libtool needs -no-undefined flag to build shared libraries])
case "${host}" in
   *-*-cygwin* | *-*-mingw* | *-*-aix*)
      ## Add in the -no-undefined flag to LDFLAGS for libtool.
      AC_MSG_RESULT([yes])
      NOUNDEFINED=" -no-undefined"
      ;;
   *)
      ## Don't add in anything.
      AC_MSG_RESULT([no])
      ;;
esac
AC_SUBST([NOUNDEFINED])

AC_CONFIG_FILES(
   [src/Makefile examples/Makefile Makefile])
AC_OUTPUT

dnl eof
