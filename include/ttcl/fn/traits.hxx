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

#ifndef TTCL_FN_TRAITS_HXX
#define TTCL_FN_TRAITS_HXX

/** @file
    Functions - Traits
    @author Edgar Gonzàlez i Pellicer
*/

#include <functional>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {

    /// Is symmetric
    template <typename T>
    struct is_symmetric :
      public boost::false_type {
    };

    /// Is symmetric
    /** Specialization for std::plus
     */
    template <typename T>
    struct is_symmetric< std::plus<T> > :
      public boost::true_type {
    };

    /// Is symmetric
    /** Specialization for std::multiplies
     */
    template <typename T>
    struct is_symmetric< std::multiplies<T> > :
      public boost::true_type {
    };

    /// Is symmetric
    /** Specialization for std::equal_to
     */
    template <typename T>
    struct is_symmetric< std::equal_to<T> > :
      public boost::true_type {
    };

    /// Is symmetric
    /** Specialization for std::not_equal_to
     */
    template <typename T>
    struct is_symmetric< std::not_equal_to<T> > :
      public boost::true_type {
    };

    /// Is symmetric
    /** Specialization for std::logical_and
     */
    template <typename T>
    struct is_symmetric< std::logical_and<T> > :
      public boost::true_type {
    };

    /// Is symmetric
    /** Specialization for std::logical_or
     */
    template <typename T>
    struct is_symmetric< std::logical_or<T> > :
      public boost::true_type {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
