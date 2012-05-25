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

#ifndef TTCL_CO_BOOST_MATRIX_HXX
#define TTCL_CO_BOOST_MATRIX_HXX

/** @file
    Containers - Matrix adapter for boost::multi_array
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <iterator>
#include <memory>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/multi_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <ttcl/global.hxx>
#include <ttcl/co/_dense_forwarder.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Matrix adapter for boost::multi_array
    template <typename T,
              typename Alloc = std::allocator<T> >
    class boost_matrix :
      public _dense_forwarder< T, boost::multi_array<T, 2, Alloc> > {
    public:
      /// Base type
      typedef _dense_forwarder< T, boost::multi_array<T, 2, Alloc> >
        base_type;

      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// @name Data sequence types
      /// @{

      /// Base data iterator
      template <typename Value>
      class _data_iterator :
        public boost::iterator_adaptor<
        _data_iterator<Value>, Value*, boost::use_default,
        std::random_access_iterator_tag> {
      private:
        struct enabler {};

      public:
        _data_iterator() :
          _data_iterator::iterator_adaptor_(0) {
        }

        explicit _data_iterator(Value* _p) :
          _data_iterator::iterator_adaptor_(_p) {
        }

        template <class OtherValue>
        _data_iterator(const _data_iterator<OtherValue>& _other,
                       typename boost::enable_if<
                         boost::is_convertible<OtherValue*, Value*>, enabler
                       >::type /* _dummy */ = enabler()) :
          _data_iterator::iterator_adaptor_(_other.base()) {
        }

      private:
        friend class boost::iterator_core_access;
      };

      /// Data iterator
      typedef _data_iterator<value_type> data_iterator;

      /// Const data iterator
      typedef _data_iterator<const value_type> const_data_iterator;

      /// Reverse data iterator
      typedef std::reverse_iterator<data_iterator> reverse_data_iterator;

      /// Const reverse data iterator
      typedef std::reverse_iterator<const_data_iterator>
        const_reverse_data_iterator;

      /// @}

      /// Storage order type
      TTCL_IMPORT_TYPE(base_type::container_type, storage_order_type);

    public:
      /// Constructor
      /** @param _rows  Rows
          @param _cols  Cols
          @param _store Storage order
      */
      boost_matrix(const size_type _rows,
                   const size_type _cols,
                   const storage_order_type& _store);

      /// Constructor
      /** @param _rows Rows
          @param _cols Cols
          @param _value Value
          @param _store Storage order
      */
      boost_matrix(const size_type _rows,
                   const size_type _cols,
                   const value_type& _value,
                   const storage_order_type& _store);

      /// Constructor
      /** @param _store Storage order
      */
      boost_matrix(const storage_order_type& _store);

      /// Columns
      size_type
      columns() const {
        return this->data_.shape()[1];
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
             const size_type _cols) {
        this->data_.resize(boost::extents[_rows][_cols]);
      }

      /// Resize
      /** @param _rows  Rows
          @param _cols  Cols
          @param _value Value
      */
      void
      resize(const size_type _rows,
             const size_type _cols,
             const value_type& _value) {
        // Remember previous size
        size_type prev_size = this->rows() * columns();

        // Resize
        this->data_.resize(boost::extents[_rows][_cols]);

        // Larger?
        size_type new_size = _rows * _cols;
        if (new_size > prev_size) {
          std::fill(this->data_.data() + prev_size,
                    this->data_.data() + new_size,
                    _value);
        }
      }

      /// Fill
      void
      fill(const value_type& _value = value_type()) {
        std::fill(this->data_begin(), this->data_end(), _value);
      }

      /// @name Data sequence methods
      /// @{

      /// Data begin
      /** Non-const version
       */
      data_iterator
      data_begin() {
        return data_iterator(this->data_.data());
      }

      /// Data begin
      /** const version
       */
      const_data_iterator
      data_begin() const {
        return const_data_iterator(this->data_.data());
      }

      /// Data end
      /** Non-const version
       */
      data_iterator
      data_end() {
        return data_iterator(this->data_.data() + data_size());
      }

      /// Data end
      /** const version
       */
      const_data_iterator
      data_end() const {
        return const_data_iterator(this->data_.data() + data_size());
      }

      /// Data reverse begin
      /** Non-const version
       */
      reverse_data_iterator
      data_rbegin() {
        return reverse_data_iterator(data_begin());
      }

      /// Data reverse begin
      /** const version
       */
      const_reverse_data_iterator
      data_rbegin() const {
        return const_reverse_data_iterator(data_begin());
      }

      /// Data reverse end
      /** Non-const version
       */
      reverse_data_iterator
      data_rend() {
        return reverse_data_iterator(data_end());
      }

      /// Data reverse end
      /** const version
       */
      const_reverse_data_iterator
      data_rend() const {
        return const_reverse_data_iterator(data_end());
      }

      /// @}
    };

    /// Constructor
    template <typename T, typename Alloc>
    boost_matrix<T, Alloc>::
    boost_matrix(const boost_matrix<T, Alloc>::size_type _rows,
                 const boost_matrix<T, Alloc>::size_type _cols,
                 const boost_matrix<T, Alloc>::storage_order_type& _store) :
      base_type(boost::extents[_rows][_cols], _store) {
    }

    /// Constructor
    template <typename T, typename Alloc>
    boost_matrix<T, Alloc>::
    boost_matrix(const boost_matrix<T, Alloc>::size_type _rows,
                 const boost_matrix<T, Alloc>::size_type _cols,
                 const boost_matrix<T, Alloc>::value_type& _value,
                 const boost_matrix<T, Alloc>::storage_order_type& _store) :
      base_type(boost::extents[_rows][_cols], _store) {
      fill(_value);
    }

    /// Constructor
    /** @param _store Storage order
    */
    template <typename T, typename Alloc>
    boost_matrix<T, Alloc>::
    boost_matrix(const boost_matrix<T, Alloc>::storage_order_type& _store) :
      base_type(boost::extents[0][0], _store) {
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
