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

#ifndef TTCL_CO__SQUARE_MATRIX_HXX
#define TTCL_CO__SQUARE_MATRIX_HXX

#if !defined(TTCL_CO_FULL_SYMMETRIC_MATRIX_HXX) && \
    !defined(TTCL_CO_HOLLOW_SYMMETRIC_MATRIX_HXX)
#error "Cannot include <ttcl/co/_square_matrix.hxx> directly"
#endif

/** @file
    Containers - Square matrix adapter
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include <ttcl/c++11.hxx>
#include <ttcl/global.hxx>
#include <ttcl/co/_square_matrix_iterator.hxx>
#include <ttcl/co/_square_matrix_reverse_iterator.hxx>
#include <ttcl/co/_square_matrix_row_ref.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// A square matrix adapter
    /** Uses the Curiously Recurring Template Pattern
     */
    template <typename Child,
              typename T,
              typename Alloc>
    class _square_matrix {
    private:
      /// Child type
      typedef Child child_type;

    public:
      /// Container type
      typedef std::vector<T, Alloc> container_type;

      /// Value type
      TTCL_IMPORT_TYPE(container_type, value_type);

      /// Reference
      TTCL_IMPORT_TYPE(container_type, reference);

      /// Const reference
      TTCL_IMPORT_TYPE(container_type, const_reference);

      /// Pointer
      TTCL_IMPORT_TYPE(container_type, pointer);

      /// Difference type
      TTCL_IMPORT_TYPE(container_type, difference_type);

      /// Size type
      TTCL_IMPORT_TYPE(container_type, size_type);

      /// @name Data sequence types
      /// @{

      /// Data iterator
      TTCL_IMPORT_R_TYPE(container_type, iterator, data_iterator);

      /// Const data iterator
      TTCL_IMPORT_R_TYPE(container_type, const_iterator, const_data_iterator);

      /// Reverse data iterator
      TTCL_IMPORT_R_TYPE(container_type, reverse_iterator,
                         reverse_data_iterator);

      /// Const reverse data iterator
      TTCL_IMPORT_R_TYPE(container_type, const_reverse_iterator,
                         const_reverse_data_iterator);

      /// @}

      /// @name Row sequence types
      /// @{

      /// Row type
      typedef _square_matrix_row_ref<child_type> row_type;

      /// Row reference
      typedef _square_matrix_row_ref<child_type> row_reference;

      /// Const row reference
      typedef const _square_matrix_row_ref<const child_type>
        const_row_reference;

      /// Row iterator
      typedef _square_matrix_iterator<child_type, row_reference> row_iterator;

      /// Const row iterator
      typedef _square_matrix_iterator<const child_type, const_row_reference>
        const_row_iterator;

      /// Reverse row iterator
      typedef _square_matrix_reverse_iterator<child_type, row_reference>
        reverse_row_iterator;

      /// Const reverse row iterator
      typedef _square_matrix_reverse_iterator<
        const child_type, const_row_reference> const_reverse_row_iterator;

      /// @}

    protected:
      /// Data
      container_type data_;

      /// Size
      size_type size_;

      /// Empty constructor
      _square_matrix() :
        data_(), size_(0) {
      }

      /// Constructor
      /** @param _size      Rows/Cols
          @param _data_size Undelying data size
          @param _value     Default value
       */
      _square_matrix(size_type _size,
                     size_type _data_size,
                     const value_type& _value) :
        data_(_data_size, _value), size_(_size) {
      }

#ifdef TTCL_CXX11_NONPUBLIC_DEFAULT_FUNCTIONS
      /// Copy constructor
      _square_matrix(const _square_matrix& _other) = default;

      /// Assignment operator
      _square_matrix&
      operator=(const _square_matrix& _other) = default;
#else

      /// Copy constructor
      _square_matrix(const _square_matrix& _other) :
        data_(_other.data_), size_(_other.size_) {
      }

      /// Assignment operator
      _square_matrix&
      operator=(const _square_matrix& _other) {
        if (&_other != this) {
          data_ = _other.data_;
          size_ = _other.size_;
        }

        return *this;
      }
#endif

    public:
      /// Empty
      bool
      empty() const {
        return size_ == 0;
      }

      /// Rows
      size_type
      rows() const {
        return size_;
      }

      /// Columns
      size_type
      columns() const {
        return size_;
      }

      /// Data size
      size_type
      data_size() const {
        return data_.size();
      }

    protected:
      /// Resize
      void
      resize(size_type _size,
             size_type _data_size,
             const value_type& _value = value_type()) {
        data_.resize(_data_size, _value);
        size_ = _size;
      }

      /// Fill
      void
      fill(const value_type& _value = value_type()) {
        std::fill(data_.begin(), data_.end(), _value);
      }

    public:
      /// @name Data sequence methods
      /// @{

      /// Data begin
      /** Non-const version
       */
      data_iterator
      data_begin() {
        return data_.begin();
      }

      /// Data begin
      /** const version
       */
      const_data_iterator
      data_begin() const {
        return data_.begin();
      }

      /// Data end
      /** Non-const version
       */
      data_iterator
      data_end() {
        return data_.end();
      }

      /// Data end
      /** const version
       */
      const_data_iterator
      data_end() const {
        return data_.end();
      }

      /// Data reverse begin
      /** Non-const version
       */
      reverse_data_iterator
      data_rbegin() {
        return data_.rbegin();
      }

      /// Data reverse begin
      /** const version
       */
      const_reverse_data_iterator
      data_rbegin() const {
        return data_.rbegin();
      }

      /// Data reverse end
      /** Non-const version
       */
      reverse_data_iterator
      data_rend() {
        return data_.rend();
      }

      /// Data reverse end
      /** const version
       */
      const_reverse_data_iterator
      data_rend() const {
        return data_.rend();
      }

      /// @}

      /// @name Row sequence methods
      /// @{

      /// Row access
      /** Non-const version
       */
      row_reference
      operator[](size_type _row) {
        return row_reference(static_cast<child_type*>(this), _row);
      }

      /// Row access
      /** const version
       */
      const_row_reference
      operator[](size_type _row) const {
        return const_row_reference(static_cast<const child_type*>(this), _row);
      }

      /// Row begin
      /** Non-const version
       */
      row_iterator
      row_begin() {
        return row_iterator(static_cast<child_type*>(this), 0);
      }

      /// Row begin
      /** const version
       */
      const_row_iterator
      row_begin() const {
        return const_row_iterator(static_cast<const child_type*>(this), 0);
      }

      /// Row end
      /** Non-const version
       */
      row_iterator
      row_end() {
        return row_iterator(static_cast<child_type*>(this), size_);
      }

      /// Row end
      /** const version
       */
      const_row_iterator
      row_end() const {
        return const_row_iterator(static_cast<const child_type*>(this), size_);
      }

      /// Row reverse begin
      /** Non-const version
       */
      reverse_row_iterator
      row_rbegin() {
        return reverse_row_iterator(row_end());
      }

      /// Reverse begin
      /** const version
       */
      const_reverse_row_iterator
      row_rbegin() const {
        return const_reverse_row_iterator(row_end());
      }

      /// Reverse end
      /** Non-const version
       */
      reverse_row_iterator
      row_rend() {
        return reverse_row_iterator(row_begin());
      }

      /// Reverse end
      /** const version
       */
      const_reverse_row_iterator
      row_rend() const {
        return const_reverse_row_iterator(row_begin());
      }

      /// @}

      /// Swap
      void
      swap(_square_matrix& _other) {
        std::swap(data_, _other.data_);
        std::swap(size_, _other.size_);
      }
    };

    /// Equality comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator==(const _square_matrix<Child, T, Container>& _m1,
               const _square_matrix<Child, T, Container>& _m2) {
      return (_m1.data_size() == _m2.data_size() and
              std::equal(_m1.data_begin(), _m1.data_end(),
                         _m2.data_begin()));
    }

    /// Inequality comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator!=(const _square_matrix<Child, T, Container>& _m1,
               const _square_matrix<Child, T, Container>& _m2) {
      return not (_m1 == _m2);
    }

    /// Less than comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator<(const _square_matrix<Child, T, Container>& _m1,
              const _square_matrix<Child, T, Container>& _m2) {
      return std::lexicographical_compare(_m1.data_begin(), _m1.data_end(),
                                          _m2.data_begin(), _m2.data_end());
    }

    /// Less than or equal comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator<=(const _square_matrix<Child, T, Container>& _m1,
               const _square_matrix<Child, T, Container>& _m2) {
      return not (_m2 < _m1);
    }

    /// Greater than comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator>(const _square_matrix<Child, T, Container>& _m1,
              const _square_matrix<Child, T, Container>& _m2) {
      return (_m2 < _m1);
    }

    /// Greater than or equal comparison
    template <typename Child, typename T, typename Container>
    inline bool
    operator>=(const _square_matrix<Child, T, Container>& _m1,
               const _square_matrix<Child, T, Container>& _m2) {
      return not (_m1 < _m2);
    }
  }
}

/// Standard namespace
namespace std {

  /// Swap
  /** Specialization
   */
  template <typename Child, typename T, typename Container>
  inline void
  swap(const ttcl::co::_square_matrix<Child, T, Container>& _m1,
       const ttcl::co::_square_matrix<Child, T, Container>& _m2) {
    return _m1.swap(_m2);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
