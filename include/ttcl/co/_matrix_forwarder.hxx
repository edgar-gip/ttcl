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

#ifndef TTCL_CO__MATRIX_FORWARDER_HXX
#define TTCL_CO__MATRIX_FORWARDER_HXX

#if !defined(TTCL_CO__DENSE_FORWARDER_HXX) && \
    !defined(TTCL_CO__SPARSE_FORWARDER_HXX)
#error "Cannot include <ttcl/co/_matrix_forwarder.hxx> directly"
#endif

/** @file
    Containers - Matrix forwarder
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/forward.hxx>
#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Matrix forwarder
    template <typename T,
              typename Container>
    class _matrix_forwarder {
    public:
      /// Container type
      typedef Container container_type;

      /// Value type
      typedef T value_type;

      /// Reference
      typedef value_type& reference;

      /// Const reference
      typedef const value_type& const_reference;

      /// Pointer
      typedef value_type* pointer;

      /// Difference type
      TTCL_IMPORT_TYPE(container_type, difference_type);

      /// Size type
      TTCL_IMPORT_TYPE(container_type, size_type);

      /// @name Row sequence types
      /// @{

      /// Row type
      TTCL_IMPORT_R_TYPE(container_type, value_type, row_type);

      /// Row reference
      TTCL_IMPORT_R_TYPE(container_type, reference, row_reference);

      /// Const row reference
      TTCL_IMPORT_R_TYPE(container_type, const_reference, const_row_reference);

      /// Row iterator
      TTCL_IMPORT_R_TYPE(container_type, iterator, row_iterator);

      /// Const row iterator
      TTCL_IMPORT_R_TYPE(container_type, const_iterator, const_row_iterator);

      /// Reverse row iterator
      TTCL_IMPORT_R_TYPE(container_type, reverse_iterator,
                         reverse_row_iterator);

      /// Const reverse row iterator
      TTCL_IMPORT_R_TYPE(container_type, const_reverse_iterator,
                         const_reverse_row_iterator);

      /// @}

    protected:
      /// Data
      container_type data_;

    public:
      /// Forwarded constructor
#define TTCL_CO__MATRIX_FORWARDER(z, i, _)                              \
      TTCL_FORWARD_TEMPLATE(i)                                          \
      _matrix_forwarder(TTCL_FORWARD_PARAMETERS(i)) :                   \
        data_(TTCL_FORWARD_CALL(i)) {                                   \
      }

      TTCL_FORWARD(TTCL_CO__MATRIX_FORWARDER)
#undef TTCL_CO__MATRIX_FORWARDER

      /// Constructor from data
      _matrix_forwarder(const container_type& _data) :
        data_(_data) {
      }

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved data
      _matrix_forwarder(container_type&& _data) :
        data_(std::move(_data)) {
      }
#endif

      /// Empty
      bool
      empty() const {
        return data_.empty();
      }

      /// Rows
      size_type
      rows() const {
        return data_.size();
      }

      /// @name Row sequence methods
      /// @{

      /// Row access
      /** Non-const version
       */
      row_reference
      operator[](size_type _row) {
        return data_[_row];
      }

      /// Row access
      /** const version
       */
      const_row_reference
      operator[](size_type _row) const {
        return data_[_row];
      }

      /// Row begin
      /** Non-const version
       */
      row_iterator
      row_begin() {
        return data_.begin();
      }

      /// Row begin
      /** const version
       */
      const_row_iterator
      row_begin() const {
        return data_.begin();
      }

      /// Row end
      /** Non-const version
       */
      row_iterator
      row_end() {
        return data_.end();
      }

      /// Row end
      /** const version
       */
      const_row_iterator
      row_end() const {
        return data_.end();
      }

      /// Row reverse begin
      /** Non-const version
       */
      reverse_row_iterator
      row_rbegin() {
        return data_.rbegin();
      }

      /// Reverse begin
      /** const version
       */
      const_reverse_row_iterator
      row_rbegin() const {
        return data_.rbegin();
      }

      /// Reverse end
      /** Non-const version
       */
      reverse_row_iterator
      row_rend() {
        return data_.rend();
      }

      /// Reverse end
      /** const version
       */
      const_reverse_row_iterator
      row_rend() const {
        return data_.rend();
      }

      /// @}

      /// Swap
      void
      swap(_matrix_forwarder& _other) {
        std::swap(data_, _other.data_);
      }

      /// @name Comparisons
      /// @{

      /// Equality comparison
      bool
      operator==(const _matrix_forwarder& _other) {
        return data_ == _other.data_;
      }

      /// Inequality comparison
      bool
      operator!=(const _matrix_forwarder& _other) {
        return data_ != _other.data_;
      }

      /// Less than comparison
      bool
      operator<(const _matrix_forwarder& _other) {
        return data_ < _other.data_;
      }

      /// Less than or equal comparison
      bool
      operator<=(const _matrix_forwarder& _other) {
        return data_ <= _other.data_;
      }

      /// Greater than comparison
      bool
      operator>(const _matrix_forwarder& _other) {
        return data_ > _other.data_;
      }

      /// Greater than or equal comparison
      bool
      operator>=(const _matrix_forwarder& _other) {
        return data_ >= _other.data_;
      }

      /// @}
    };
  }
}

/// Standard namespace
namespace std {

  /// Swap
  /** Specialization
   */
  template <typename T, typename Container>
  inline void
  swap(const ttcl::co::_matrix_forwarder<T, Container>& _m1,
       const ttcl::co::_matrix_forwarder<T, Container>& _m2) {
    return _m1.swap(_m2);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
