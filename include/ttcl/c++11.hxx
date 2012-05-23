// TTCL: The Template Clustering Library
// Copyright (C) 2012  Edgar Gonzàlez i Pellicer
//
// This file is part of TTCL.
//
// TTCL is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef TTCL_CXX11_HXX
#define TTCL_CXX11_HXX

/** @file
    C++11 Support
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/_c++11.hxx>

// Define if g++ supports C++11 default functions.
/* #undef TTCL_CXX11_DEFAULT_FUNCTIONS */

// Define if g++ supports C++11 deleted functions.
/* #undef TTCL_CXX11_DELETED_FUNCTIONS */

// Define if g++ supports C++11 non-public default functions.
/* #undef TTCL_CXX11_NONPUBLIC_DEFAULT_FUNCTIONS */

// Define if g++ supports C++11 rvalues.
/* #undef TTCL_CXX11_RVALUES */

// Define if g++ supports C++11 rvalue default functions.
/* #undef TTCL_CXX11_RVALUE_DEFAULT_FUNCTIONS */

// Define if g++ supports C++11 template aliases.
/* #undef TTCL_CXX11_TEMPLATE_ALIASES */

/// C++0x unique pointers
#if __GNUC__ == 4 && __GNUC_MINOR__ >= 5 && defined(__GXX_EXPERIMENTAL_CXX0X__)
# define TTCL_CXX0X_UNIQUE_PTR
#endif

/// Unique ptr
#ifdef TTCL_CXX0X_UNIQUE_PTR
# define TTCL_AUTO_PTR std::unique_ptr
#else
# define TTCL_AUTO_PTR std::auto_ptr
#endif

/// Default
#ifdef TTCL_CXX11_DEFAULT_FUNCTIONS
# define TTCL_DEFAULT = default
#else
# define TTCL_DEFAULT
#endif

/// Delete
#ifdef TTCL_CXX11_DELETED_FUNCTIONS
# define TTCL_DELETE = delete
#else
# define TTCL_DELETE
#endif

/// Default constructor
#ifdef TTCL_CXX11_DEFAULT_FUNCTIONS
# define TTCL_DEFAULT_CONSTRUCTOR(_class)       \
  _class() = default
#else
# define TTCL_DEFAULT_CONSTRUCTOR(_class)       \
  _class() {}
#endif

/// Default non-public constructor
#ifdef TTCL_CXX11_NONPUBLIC_DEFAULT_FUNCTIONS
# define TTCL_DEFAULT_NONPUBLIC_CONSTRUCTOR(_class)     \
  _class() = default
#else
# define TTCL_DEFAULT_NONPUBLIC_CONSTRUCTOR(_class)     \
  _class() {}
#endif

/// Deleted constructor
#ifdef TTCL_CXX11_DELETED_FUNCTIONS
# define TTCL_DELETED_CONSTRUCTOR(_class)       \
  _class() = delete
#else
# define TTCL_DELETED_CONSTRUCTOR(_class)       \
  _class()
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
