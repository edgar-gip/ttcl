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

#ifndef TTCL_CXX0X_HXX
#define TTCL_CXX0X_HXX

/** @file
    C++0x Support
    @author Edgar Gonzàlez i Pellicer
*/

/// C++ 0x default functions
#if __GNUC__ == 4 && __GNUC_MINOR__ >= 4 && defined(__GXX_EXPERIMENTAL_CXX0X__)
# define TTCL_CXX0X_DEFAULTS
#endif

/// C++ 0x move default functions
#if 0 && defined(__GXX_EXPERIMENTAL_CXX0X__)
# define TTCL_CXX0X_MOVE_DEFAULTS
#endif

/// C++ 0x non-public default functions
#if __GNUC__ == 4 && __GNUC_MINOR__ >= 6 && defined(__GXX_EXPERIMENTAL_CXX0X__)
# define TTCL_CXX0X_NONPUBLIC_DEFAULTS
#endif

/// C++ 0x rvalues
#if __GNUC__ == 4 && __GNUC_MINOR__ >= 3 && defined(__GXX_EXPERIMENTAL_CXX0X__)
# define TTCL_CXX0X_RVALUES
#endif

/// C++ 0x unique pointers
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
#ifdef TTCL_CXX0X_DEFAULTS
# define TTCL_DEFAULT = default
#else
# define TTCL_DEFAULT
#endif

/// Delete
#ifdef TTCL_CXX0X_DEFAULTS
# define TTCL_DELETE = delete
#else
# define TTCL_DELETE
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
