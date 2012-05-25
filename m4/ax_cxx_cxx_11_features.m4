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

AC_DEFUN([AX_CXX_STDCXX_11_DEFAULT_FUNCTIONS], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 default functions,
    ax_cv_cxx_cxx11_default_functions,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       struct A {
         A() = default;
       };],,
     ax_cv_cxx_cxx11_default_functions=yes,
     ax_cv_cxx_cxx11_default_functions=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_default_functions" = xyes; then
    AC_DEFINE(STDCXX_11_DEFAULT_FUNCTIONS,,dnl
              [Define if g++ supports C++11 default functions. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_DELETED_FUNCTIONS], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 deleted functions,
    ax_cv_cxx_cxx11_deleted_functions,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       struct A {
         A() = delete;
       };],,
     ax_cv_cxx_cxx11_deleted_functions=yes,
     ax_cv_cxx_cxx11_deleted_functions=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_deleted_functions" = xyes; then
    AC_DEFINE(STDCXX_11_DELETED_FUNCTIONS,,dnl
              [Define if g++ supports C++11 deleted functions. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_LONG_LONG], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 long long,
    ax_cv_cxx_cxx11_long_long,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       long long i;],,
     ax_cv_cxx_cxx11_long_long=yes,
     ax_cv_cxx_cxx11_long_long=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_long_long" = xyes; then
    AC_DEFINE(STDCXX_11_LONG_LONG,,dnl
              [Define if g++ supports C++11 long long. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_NON_PUBLIC_DEFAULT_FUNCTIONS], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 non-public default functions,
    ax_cv_cxx_cxx11_nonpublic_default_functions,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       struct A {
       private:
         A() = default;
       };],,
     ax_cv_cxx_cxx11_nonpublic_default_functions=yes,
     ax_cv_cxx_cxx11_nonpublic_default_functions=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_nonpublic_default_functions" = xyes; then
    AC_DEFINE(STDCXX_11_NONPUBLIC_DEFAULT_FUNCTIONS,,dnl
              [Define if g++ supports C++11 non-public default functions. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_RVALUES], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 rvalues,
    ax_cv_cxx_cxx11_rvalues,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       void f(int&&);],,
     ax_cv_cxx_cxx11_rvalues=yes,
     ax_cv_cxx_cxx11_rvalues=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_rvalues" = xyes; then
    AC_DEFINE(STDCXX_11_RVALUES,,dnl
              [Define if g++ supports C++11 rvalues. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_RVALUE_DEFAULT_FUNCTIONS], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 rvalue default functions,
    ax_cv_cxx_cxx11_rvalue_default_functions,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       struct A {
         A(A&&) = default;
       };],,
     ax_cv_cxx_cxx11_rvalue_default_functions=yes,
     ax_cv_cxx_cxx11_rvalue_default_functions=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_rvalue_default_functions" = xyes; then
    AC_DEFINE(STDCXX_11_RVALUE_DEFAULT_FUNCTIONS,,dnl
              [Define if g++ supports C++11 rvalue default functions. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_TEMPLATE_ALIASES], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 template aliases,
    ax_cv_cxx_cxx11_template_aliases,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       template <typename T, typename TT> struct A {};
       template <typename T> using B = A<T, T>;],,
     ax_cv_cxx_cxx11_template_aliases=yes,
     ax_cv_cxx_cxx11_template_aliases=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_template_aliases" = xyes; then
    AC_DEFINE(STDCXX_11_TEMPLATE_ALIASES,,dnl
              [Define if g++ supports C++11 template aliases. ])
  fi
])

AC_DEFUN([AX_CXX_STDCXX_11_UNIQUE_PTR], [dnl
  AC_CACHE_CHECK(if g++ supports C++11 std::unique_ptr<...>,
    ax_cv_cxx_cxx11_unique_ptr,
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     AC_TRY_COMPILE([
       #include <memory>
       std::unique_ptr<int> ptr;],,
     ax_cv_cxx_cxx11_unique_ptr=yes,
     ax_cv_cxx_cxx11_unique_ptr=no)
     AC_LANG_RESTORE])

  if test x"$ax_cv_cxx_cxx11_unique_ptr" = xyes; then
    AC_DEFINE(STDCXX_11_UNIQUE_PTR,,dnl
              [Define if g++ supports C++11 std::unique_ptr<...>. ])
  fi
])

AC_CONFIG_COMMANDS([_c++11.hxx],[dnl
  outfile=$srcdir/include/ttcl/_c++11.hxx
  tmpfile=$outfile.tmp

  cat > $tmpfile << _EOF_
#ifndef _TTCL__CXX11_HXX
#define _TTCL__CXX11_HXX

_EOF_

  echo '/// Define if g++ supports C++11 default functions.' >> $tmpfile
  if test x"$default_functions" = xyes; then
    echo '#define TTCL_CXX11_DEFAULT_FUNCTIONS' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_DEFAULT_FUNCTIONS */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 deleted functions.' >> $tmpfile
  if test x"$deleted_functions" = xyes; then
    echo '#define TTCL_CXX11_DELETED_FUNCTIONS' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_DELETED_FUNCTIONS */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 long long.' >> $tmpfile
  if test x"$long_long" = xyes; then
    echo '#define TTCL_CXX11_LONG_LONG' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_LONG_LONG */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 non-public default functions.' >> $tmpfile
  if test x"$nonpublic_default_functions" = xyes; then
    echo '#define TTCL_CXX11_NONPUBLIC_DEFAULT_FUNCTIONS' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_NONPUBLIC_DEFAULT_FUNCTIONS */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 rvalues.' >> $tmpfile
  if test x"$rvalues" = xyes; then
    echo '#define TTCL_CXX11_RVALUES' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_RVALUES */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 rvalue default functions.' >> $tmpfile
  if test x"$rvalue_default_functions" = xyes; then
    echo '#define TTCL_CXX11_RVALUE_DEFAULT_FUNCTIONS' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_RVALUE_DEFAULT_FUNCTIONS */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 template aliases.' >> $tmpfile
  if test x"$template_aliases" = xyes; then
    echo '#define TTCL_CXX11_TEMPLATE_ALIASES' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_TEMPLATE_ALIASES */' >> $tmpfile
  fi
  echo >> $tmpfile

  echo '/// Define if g++ supports C++11 std::unique_ptr<...>.' >> $tmpfile
  if test x"$unique_ptr" = xyes; then
    echo '#define TTCL_CXX11_UNIQUE_PTR' >> $tmpfile
  else
    echo '/* #undef TTCL_CXX11_UNIQUE_PTR */' >> $tmpfile
  fi
  echo >> $tmpfile

  cat >> $tmpfile << _EOF_

#endif
_EOF_

  mv "$tmpfile" "$outfile"
],[
  srcdir=$srcdir
  default_functions=$ax_cv_cxx_cxx11_default_functions
  deleted_functions=$ax_cv_cxx_cxx11_deleted_functions
  long_long=$ax_cv_cxx_cxx11_long_long
  nonpublic_default_functions=$ax_cv_cxx_cxx11_nonpublic_default_functions
  rvalues=$ax_cv_cxx_cxx11_rvalues
  rvalue_default_functions=$ax_cv_cxx_cxx11_rvalue_default_functions
  template_aliases=$ax_cv_cxx_cxx11_template_aliases
  unique_ptr=$ax_cv_cxx_cxx11_unique_ptr
])

# Local Variables:
# coding: utf-8
# indent-tabs-mode: nil
# End:
