# TTCL: The Template Clustering Library
# Copyright (C) 2012  Edgar Gonzàlez i Pellicer
#
# This file is part of TTCL.
#
# TTCL is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Process this file with autoconf to produce a configure script.

# Initialize
AC_INIT([ttcl], [0.3], [edgar.gip@gmail.com])
AC_CONFIG_AUX_DIR([libltdl/config])
AC_CONFIG_HEADERS([src/config/config.hxx])
AC_CONFIG_MACRO_DIR([libltdl/m4])
AC_CONFIG_SRCDIR([src/ttcl/exception.cxx])
AC_CONFIG_SUBDIRS([libtdl])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

## libtool + libltdl
AC_LIBTOOL_DLOPEN
AC_LIBLTDL_CONVENIENCE
AC_PROG_LIBTOOL
LT_CONFIG_LTDL_DIR([libltdl])
LTDL_INIT
AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)


# C
AC_LANG(C)

# Checks for libraries.

## Readline
AC_ARG_ENABLE([readline],
              AC_HELP_STRING([--enable-readline],
                             [Enable readline support, if readine present.]),
              [AC_CHECK_LIB([readline], [readline],
                            [READLINE_LIBS=-lreadline
                             AC_DEFINE([HAVE_LIBREADLINE], [1],
                                       [Define to 1 if you have the `readline' library (-lreadline).])])])
AC_SUBST(READLINE_LIBS)

## XML-RPC
AC_ARG_ENABLE([xmlrpc],
              AC_HELP_STRING([--enable-xmlrpc],
                             [Enable xmlrpc support, if xmlrpc present.]),
              [AC_CHECK_LIB([xmlrpc], [xmlrpc_env_init],
                            [XMLRPC_LIBS="-lxmlrpc++ -lxmlrpc_client++"
                             AC_DEFINE([HAVE_XMLRPC], [1],
                                       [Define to 1 if you have the `xmlrpc' library (-lxmlrpc).])])])
AC_SUBST(XMLRPC_LIBS)
AM_CONDITIONAL([ENABLE_XMLRPC], [test "$enable_xmlrpc" = yes])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([memory.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([isascii isxdigit])


# Output
AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile
                 src/ttcl/Makefile
                 src/ttcl/tu/Makefile])
AC_OUTPUT

# Local Variables:
# coding: utf-8
# indent-tabs-mode: nil
# End: