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

#ifndef TTCL_CO_TRAITS_HXX
#define TTCL_CO_TRAITS_HXX

// TTCL: The Template Clustering Library

/** @file
    Containers - Traits
    @author Edgar Gonzalez i Pellicer
*/

#include <cstddef>
#include <utility>

#include <boost/mpl/or.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <ttcl/co/full_symmetric_matrix.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Is full symmetric matrix
    template <typename T>
    struct is_full_symmetric_matrix :
      public boost::false_type {
    };

    /// Is full symmetric matrix
    /** Specialization for full_symmetric_matrix
     */
    template <typename T>
    struct is_full_symmetric_matrix< full_symmetric_matrix<T> > :
      public boost::true_type {
    };

    /// Is hollow symmetric matrix
    template <typename T>
    struct is_hollow_symmetric_matrix :
      public boost::false_type {
    };

    /// Is hollow symmetric matrix
    /** Specialization for hollow_symmetric_matrix
     */
    template <typename T>
    struct is_hollow_symmetric_matrix< hollow_symmetric_matrix<T> > :
      public boost::true_type {
    };

    /// Is symmetric matrix
    template <typename T>
    struct is_symmetric_matrix :
      public boost::mpl::or_<is_full_symmetric_matrix<T>,
                             is_hollow_symmetric_matrix<T> > {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
