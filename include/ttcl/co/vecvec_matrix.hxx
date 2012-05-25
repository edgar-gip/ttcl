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

#ifndef TTCL_CO_VECVEC_MATRIX_HXX
#define TTCL_CO_VECVEC_MATRIX_HXX

/** @file
    Containers - Matrix adapter for std::vector<std::vector<...>>
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <memory>
#include <vector>

#include <boost/foreach.hpp>

#include <ttcl/c++11.hxx>
#include <ttcl/exception.hxx>
#include <ttcl/global.hxx>
#include <ttcl/co/_dense_forwarder.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Matrix adapter for std::vector< std::vector<...> >
    template <typename T,
              typename Alloc = std::allocator<T> >
    class vecvec_matrix :
      public _dense_forwarder<T, std::vector<
        std::vector<T, Alloc>,
        typename Alloc::template rebind< std::vector<T, Alloc> >::other > > {
    public:
      /// Base type
      typedef _dense_forwarder<T, std::vector<
        std::vector<T, Alloc>,
        typename Alloc::template rebind< std::vector<T, Alloc> >::other > >
        base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Row type
      TTCL_IMPORT_TYPE(base_type, row_type);

      /// Row reference
      TTCL_IMPORT_TYPE(base_type, row_reference);

      /// @todo Data sequence types

    public:
      /// Empty constructor
      TTCL_DEFAULT_CONSTRUCTOR(vecvec_matrix);

      /// Constructor
      /** @param _rows  Rows
          @param _cols  Cols
          @param _value Value
      */
      vecvec_matrix(const size_type _rows,
                    const size_type _cols,
                    const value_type& _value = value_type());

      /// Constructor from container
      vecvec_matrix(const container_type& _container);

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved container
      vecvec_matrix(container_type&& _container);
#endif

      /// Columns
      size_type
      columns() const {
        return this->empty() ? 0 : this->data_.front().size();
      }

      /// Data size
      size_type
      data_size() const {
        return this->rows() * columns();
      }

      /// Resize
      /** @param _rows  Rows
          @param _cols  Cols
      */
      void
      resize(const size_type _rows,
             const size_type _cols,
             const value_type& _value = value_type());

      /// Fill
      void
      fill(const value_type& _value = value_type());

      /// @todo Data sequence methods

#ifdef TTCL_DEBUG
    private:
      /// Check all the rows are equal
      void
      check_all_rows_equal();
#endif
    };

    /// Constructor
    template <typename T, typename Alloc>
    vecvec_matrix<T, Alloc>::
    vecvec_matrix(const vecvec_matrix<T, Alloc>::size_type _rows,
                  const vecvec_matrix<T, Alloc>::size_type _cols,
                  const vecvec_matrix<T, Alloc>::value_type& _value) :
      base_type(_rows, row_type(_cols, _value)) {
    }

    /// Constructor from container
    template <typename T, typename Alloc>
    vecvec_matrix<T, Alloc>::
    vecvec_matrix(const vecvec_matrix<T, Alloc>::container_type& _container) :
      base_type(_container) {
#ifdef TTCL_DEBUG
      check_all_rows_equal();
#endif
    }

#ifdef TTCL_CXX11_RVALUES
    /// Constructor from moved container
    template <typename T, typename Alloc>
    vecvec_matrix<T, Alloc>::
    vecvec_matrix(vecvec_matrix<T, Alloc>::container_type&& _container) :
      base_type(std::move(_container)) {
#ifdef TTCL_DEBUG
      check_all_rows_equal();
#endif
    }
#endif

    /// Resize
    /** @param _rows  Rows
        @param _cols  Cols
    */
    template <typename T, typename Alloc>
    void vecvec_matrix<T, Alloc>::
    resize(const size_type _rows,
           const size_type _cols,
           const value_type& _value) {
      size_type end = std::min(this->rows(), _rows);
      for (size_type r = 0; r < end; ++r) {
        (*this)[r].resize(_cols, _value);
      }

      this->data_.resize(_rows, row_type(_cols, _value));
    }

    /// Fill
    template <typename T, typename Alloc>
    void vecvec_matrix<T, Alloc>::
    fill(const value_type& _value) {
      BOOST_FOREACH (row_reference r, this->data_) {
        std::fill(r.begin(), r.end(), _value);
      }
    }

#ifdef TTCL_DEBUG
    /// Check all the rows are equal
    template <typename T, typename Alloc>
    void vecvec_matrix<T, Alloc>::
    check_all_rows_equal() {
      if (this->data_.empty())
        return;

      size_type columns = this->data_.front().size();
      for (size_type r = 1; r < this->data_.size(); ++r) {
        if (this->data_[r].size() != columns) {
          TTCL_FIRE("Source container is not rectangular");
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
