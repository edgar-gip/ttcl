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

# Local Variables:
# coding: utf-8
# End:
