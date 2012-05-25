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

#ifndef TTCL_CO__SPARSE_FORWARDER_HXX
#define TTCL_CO__SPARSE_FORWARDER_HXX

#if !defined(TTCL_CO_BINARY_MATRIX_HXX) && \
    !defined(TTCL_CO_SPARSE_MATRIX_HXX)
# error "Cannot include <ttcl/co/_sparse_forwarder.hxx> directly"
#endif

/** @file
    Data - Base sparse data
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <functional>
#include <memory>

#include <boost/foreach.hpp>

#include <ttcl/c++11.hxx>
#include <ttcl/forward.hxx>
#include <ttcl/global.hxx>
#include <ttcl/co/_matrix_forwarder.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Base sparse data
    template <typename T,
              typename Container>
    class _sparse_forwarder :
      public _matrix_forwarder<T, Container> {
    public:
      /// Base type
      typedef _matrix_forwarder<T, Container> base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Const row reference
      TTCL_IMPORT_TYPE(base_type, const_row_reference);

    private:
      /// Columns
      /** Cached value
       */
      mutable size_type columns_;

      /// Is the columns cache valid?
      bool columns_valid_;

    public:
      /// Forwarded constructor
#define TTCL_CO__SPARSE_FORWARDER(z, i, _)                              \
      TTCL_FORWARD_TEMPLATE(i)                                          \
      _sparse_forwarder(TTCL_FORWARD_PARAMETERS(i)) :                   \
        base_type(TTCL_FORWARD_CALL(i)), columns_valid_(false) {        \
      }

      TTCL_FORWARD(TTCL_CO__SPARSE_FORWARDER)
#undef TTCL_CO__SPARSE_FORWARDER

      /// Constructor from data
      _sparse_forwarder(const container_type& _data);

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved data
      _sparse_forwarder(container_type&& _data);
#endif

      /// Columns
      size_type
      columns() const;

      /// Invalidate columns
      void
      invalidate_columns() {
        columns_valid_ = false;
      }

      /// Data size
      size_type
      data_size() const {
        size_type sum = 0;
        BOOST_FOREACH(const_row_reference r, this->data_) {
          sum += r.size();
        }

        return sum;
      }

#ifdef TTCL_DEBUG
    private:
      /// Check all rows sorted
      void
      check_all_rows_sorted();
#endif
    };

    /// Constructor from data
    template <typename T,
              typename Container>
    _sparse_forwarder<T, Container>::
    _sparse_forwarder(const container_type& _data) :
      base_type(_data), columns_valid_(false) {
#ifdef TTCL_DEBUG
      check_all_rows_sorted();
#endif
    }

#ifdef TTCL_CXX11_RVALUES
    /// Constructor from moved data
    template <typename T,
              typename Container>
    _sparse_forwarder<T, Container>::
    _sparse_forwarder(container_type&& _data) :
      base_type(std::move(_data)), columns_valid_(false) {
#ifdef TTCL_DEBUG
      check_all_rows_sorted();
#endif
    }
#endif

    /// Columns
    template <typename T,
              typename Container>
    typename _sparse_forwarder<T, Container>::size_type
    _sparse_forwarder<T, Container>::
    columns() const {
      if (not columns_valid_) {
        columns_ = 0;
        BOOST_FOREACH(const_row_reference r, this->data_) {
          if (not r.empty and r.back().first >= columns_) {
            columns_ = r.back().first + 1;
          }
        }

        columns_valid_ = true;
      }

      return columns_;
    }

#ifdef TTCL_DEBUG
    /// Check all rows are sorted
    template <typename T,
              typename Container>
    void _sparse_forwarder<T, Container>::
    check_all_rows_sorted() const {
      BOOST_FOREACH(const_row_reference r, this->data_) {
        if (not is_sorted(r.begin(), r.end(),
                          std::less_equal<typename row_type::value_type>())) {
          TTCL_FIRE("Rows in source container are not sorted");
        }
      }
    }
#endif
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
