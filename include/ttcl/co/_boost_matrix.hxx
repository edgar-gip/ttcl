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

#ifndef TTCL_CO__BOOST_MATRIX_HXX
#define TTCL_CO__BOOST_MATRIX_HXX

#if !defined(TTCL_CO_FORTRAN_MATRIX_HXX) && \
    !defined(TTCL_CO_MATRIX_HXX)
#error "Cannot include <ttcl/co/_boost_matrix.hxx> directly"
#endif

/** @file
    Containers - Matrix adapter for boost::multi_array
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <memory>

#include <boost/multi_array.hpp>

#include <ttcl/c++0x.hxx>
#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Matrix adapter for boost::multi_array
    template <typename T, typename Alloc = std::allocator<T> >
    class _boost_matrix :
      public boost::multi_array<T, 2, Alloc> {
    public:
      /// Base type
      typedef boost::multi_array<T, 2, Alloc> base_type;

      /// Element type
      TTCL_IMPORT_TYPE(base_type, element);

      /// Row type
      TTCL_IMPORT_R_TYPE(base_type, value_type, row);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Storage order type
      TTCL_IMPORT_TYPE(base_type, storage_order_type);

      /// Element reference
      typedef element& element_reference;

      /// Const element reference
      typedef const element& const_element_reference;

    protected:
      /// Constructor
      /** @param _rows  Rows
          @param _cols  Cols
          @param _store Storage order
      */
      _boost_matrix(const size_type _rows, const size_type _cols,
                    const storage_order_type& _store);

      /// Constructor
      /** @param _rows Rows
          @param _cols Cols
          @param _value Value
          @param _store Storage order
      */
      _boost_matrix(const size_type _rows, const size_type _cols,
                    const element& _value,
                    const storage_order_type& _store);

      /// Constructor
      /** @param _store Storage order
      */
      _boost_matrix(const storage_order_type& _store);

    public:
      /// Resize
      /** @param _rows  Rows
          @param _cols  Cols
      */
      void
      resize(const size_type _rows, const size_type _cols) {
        // Resize
        base_type::resize(boost::extents[_rows][_cols]);
      }

      /// Resize
      /** @param _rows  Rows
          @param _cols  Cols
          @param _value Value
      */
      void
      resize(const size_type _rows, const size_type _cols,
             const element& _value) {
        // Remember previous size
        size_type prev_size = rows() * columns();

        // Resize
        base_type::resize(boost::extents[_rows][_cols]);

        // Larger?
        size_type new_size = _rows * _cols;
        if (new_size > prev_size)
          // Fill with the element
          std::fill(this->data() + prev_size,
                    this->data() + new_size,
                    _value);
      }

      /// Rows
      size_type
      rows() const {
        // Synonym for size
        return this->size();
      }

      /// Columns
      size_type
      columns() const {
        // Last dimension of shape
        return this->shape()[1];
      }

      /// Element access
      /** Non-const version
          @param _row Row
          @param _col Column
      */
      element_reference
      operator()(size_type _row, size_type _col) {
        return (*this)[_row][_col];
      }

      /// Element access
      /** const version
          @param _row Row
          @param _col Column
      */
      const_element_reference
      operator()(size_type _row, size_type _col) const {
        return (*this)[_row][_col];
      }

      /// Clear
      void
      clear(const element& _value = element()) {
        std::fill(this->data(),
                  this->data() + rows() * columns(),
                  _value);
      }
    };

    /// Constructor
    template <typename T, typename Alloc>
    _boost_matrix<T, Alloc>::
    _boost_matrix(const _boost_matrix<T, Alloc>::size_type _rows,
                  const _boost_matrix<T, Alloc>::size_type _cols,
                  const _boost_matrix<T, Alloc>::storage_order_type& _store) :
      base_type(boost::extents[_rows][_cols], _store) {
    }

    /// Constructor
    template <typename T, typename Alloc>
    _boost_matrix<T, Alloc>::
    _boost_matrix(const _boost_matrix<T, Alloc>::size_type _rows,
                  const _boost_matrix<T, Alloc>::size_type _cols,
                  const _boost_matrix<T, Alloc>::element& _value,
                  const _boost_matrix<T, Alloc>::storage_order_type& _store) :
      base_type(boost::extents[_rows][_cols], _store) {
      clear(_value);
    }

    /// Constructor
    /** @param _store Storage order
    */
    template <typename T, typename Alloc>
    _boost_matrix<T, Alloc>::
    _boost_matrix(const storage_order_type& _store) :
      base_type(boost::extents[0][0], _store) {
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
