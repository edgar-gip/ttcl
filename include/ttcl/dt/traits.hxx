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

#ifndef TTCL_DT_TRAITS_HXX
#define TTCL_DT_TRAITS_HXX

/** @file
    Data - Traits
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/type_traits/integral_constant.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Data Namespace
  namespace dt {

    /// Is dense data
    template <typename T>
    struct is_dense_data :
      public boost::false_type {
    };

    /// Is sparse data
    template <typename T>
    struct is_sparse_data :
      public boost::false_type {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
