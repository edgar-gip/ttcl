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

#ifndef TTCL_CO_MATRIX_HXX
#define TTCL_CO_MATRIX_HXX

/** @file
    Containers - Matrix
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <memory>

#include <boost/multi_array.hpp>

#include <ttcl/global.hxx>
#include <ttcl/co/boost_matrix.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Matrix
    template <typename T,
              typename Alloc = std::allocator<T> >
    class matrix :
      public boost_matrix<T, Alloc> {
    public:
      /// Base type
      typedef boost_matrix<T, Alloc> base_type;

      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Empty constructor
      matrix();

      /// Constructor
      /** @param _rows  Rows
          @param _cols  Cols
      */
      matrix(const size_type _rows,
             const size_type _cols);

      /// Constructor
      /** @param _rows Rows
          @param _cols Cols
          @param _value Value
      */
      matrix(const size_type _rows,
             const size_type _cols,
             const value_type& _value);
    };

    /// Empty constructor
    template <typename T, typename Alloc>
    matrix<T, Alloc>::
    matrix() :
      base_type(boost::c_storage_order()) {
    }

    /// Constructor
    template <typename T, typename Alloc>
    matrix<T, Alloc>::
    matrix(const matrix<T, Alloc>::size_type _rows,
           const matrix<T, Alloc>::size_type _cols) :
      base_type(_rows, _cols, boost::c_storage_order()) {
    }

    /// Constructor
    template <typename T, typename Alloc>
    matrix<T, Alloc>::
    matrix(const matrix<T, Alloc>::size_type _rows,
           const matrix<T, Alloc>::size_type _cols,
           const matrix<T, Alloc>::value_type& _value) :
      base_type(_rows, _cols, _value, boost::c_storage_order()) {
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
