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

#ifndef TTCL_CO__SQUARE_MATRIX_ROW_ITERATOR_HXX
#define TTCL_CO__SQUARE_MATRIX_ROW_ITERATOR_HXX

#ifndef TTCL_CO__SQUARE_MATRIX_ROW_REF_HXX
#error "Cannot include <ttcl/co/_square_matrix_row_iterator.hxx> directly"
#endif

/** @file
    Containers - Square matrix row iterator
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstddef>
#include <iterator>

#include <boost/type_traits/remove_const.hpp>

#include <ttcl/assert.hxx>
#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    // Pre-declarations
    template <typename Matrix, typename Value>
    class _square_matrix_row_iterator;

    template <typename Matrix, typename Value>
    inline bool
    operator==(const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b);

    template <typename Matrix, typename Value>
    inline bool
    operator< (const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b);


    /// Square matrix row iterator
    /** A model of Random Access Iterator
     */
    template <typename Matrix, typename Value>
    class _square_matrix_row_iterator {
    public:
      /// Iterator category
      typedef std::random_access_iterator_tag iterator_category;

      /// Value type
      typedef typename boost::remove_const<Value>::type value_type;

      /// Difference type
      typedef std::ptrdiff_t difference_type;

      /// Pointer
      typedef Value* pointer;

      /// Reference
      typedef Value& reference;

    private:
      /// Matrix type
      typedef Matrix matrix_type;

      /// Size type
      TTCL_IMPORT_TYPE(matrix_type, size_type);

      /// Matrix
      matrix_type* matrix_;

      /// Row
      size_type row_;

      /// Column
      size_type col_;

    public:
      /// Constructor
      _square_matrix_row_iterator(matrix_type* _matrix = 0,
                                  size_type _row = 0, size_type _col = 0) :
        matrix_(_matrix), row_(_row), col_(_col) {
      }

      /// Iterator conversion
      template <typename MatrixO, typename ValueO>
      _square_matrix_row_iterator
        (const _square_matrix_row_iterator<MatrixO, ValueO>& _other) :
        matrix_(_other.matrix_), row_(_other.row_), col_(_other.col_) {
      }

      /// @name Forward iterator requirements
      /// @{

      /// Indirection
      reference
      operator*() const {
        return (*matrix_)(row_, col_);
      }

      /// Indirection
      pointer
      operator->() const {
        return &((*matrix_)(row_, col_));
      }

      /// Preincrement
      _square_matrix_row_iterator&
      operator++() {
        ++col_;
        return *this;
      }


      /// Postincrement
      _square_matrix_row_iterator
      operator++(int) {
        _square_matrix_row_iterator ret(*this);
        ++col_;
        return ret;
      }

      /// @}

      /// @name Bidirectional iterator requirements
      /// @{

      /// Predecrement
      _square_matrix_row_iterator&
      operator--() {
        --col_;
        return *this;
      }


      /// Postdecrement
      _square_matrix_row_iterator
      operator--(int) {
        _square_matrix_row_iterator ret(*this);
        --col_;
        return ret;
      }

      /// @}

      /// @name Random access iterator requirements
      /// @{

      /// Access
      reference
      operator[](const difference_type& _n) const {
        return (*matrix_)(row_, col_ + _n);
      }

      /// Increment
      _square_matrix_row_iterator&
      operator+=(const difference_type& _n) {
        col_ += _n;
        return *this;
      }

      /// Addition
      _square_matrix_row_iterator
      operator+(const difference_type& _n) const {
        return _square_matrix_row_iterator(matrix_, row_, col_ + _n);
      }

      /// Decrement
      _square_matrix_row_iterator&
      operator-=(const difference_type& _n) {
        col_ -= _n;
        return *this;
      }

      /// Subtraction
      _square_matrix_row_iterator
      operator-(const difference_type& _n) const {
        return _square_matrix_row_iterator(matrix_, row_, col_ - _n);
      }

      /// Difference
      difference_type
      operator-(const _square_matrix_row_iterator& _other) const {
        TTCL_ASSERT(matrix_ == _other.matrix_ and
                    row_    == _other.row_);
        return col_ - _other.col_;
      }

      /// @}

      // Friends
      friend
      bool operator== <Matrix, Value>
        (const _square_matrix_row_iterator<Matrix, Value>& _a,
         const _square_matrix_row_iterator<Matrix, Value>& _b);

      template <typename MatrixA, typename ValueA,
                typename MatrixB, typename ValueB>
      friend
      bool operator==
        (const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
         const _square_matrix_row_iterator<MatrixB, ValueB>& _b);

      friend
      bool operator<  <Matrix, Value>
        (const _square_matrix_row_iterator<Matrix, Value>& _a,
         const _square_matrix_row_iterator<Matrix, Value>& _b);

      template <typename MatrixA, typename ValueA,
                typename MatrixB, typename ValueB>
      friend
      bool operator<
        (const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
         const _square_matrix_row_iterator<MatrixB, ValueB>& _b);

      template <typename MatrixO, typename ValueO>
      friend class _square_matrix_row_iterator;
    };

    /// Equality comparison
    template <typename Matrix, typename Value>
    inline bool
    operator==(const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      return _a.matrix_ == _b.matrix_ and
             _a.row_    == _b.row_    and
             _a.col_    == _b.col_;
    }

    /// Equality comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator==(const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      return _a.matrix_ == _b.matrix_ and
             _a.row_    == _b.row_    and
             _a.col_    == _b.col_;
    }

    /// Inequality comparison
    template <typename Matrix, typename Value>
    inline bool
    operator!=(const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      return not (_a == _b);
    }

    /// Inequality comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator!=(const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      return not (_a == _b);
    }

    /// Less than comparison
    template <typename Matrix, typename Value>
    inline bool
    operator< (const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      TTCL_ASSERT(_a.matrix_ == _b.matrix_ and _a.row_ == _b.row_);
      return _a.col_ < _b.col_;
    }

    /// Less than comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator< (const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      TTCL_ASSERT(_a.matrix_ == _b.matrix_ and _a.row_ == _b.row_);
      return _a.col_ < _b.col_;
    }

    /// Less than or equal comparison
    template <typename Matrix, typename Value>
    inline bool
    operator<=(const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      return not (_b < _a);
    }

    /// Less than or equal comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator<=(const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      return not (_b < _a);
    }

    /// Greater than comparison
    template <typename Matrix, typename Value>
    inline bool
    operator> (const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      return _b < _a;
    }

    /// Greater than comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator> (const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      return _b < _a;
    }

    /// Greater than or equal comparison
    template <typename Matrix, typename Value>
    inline bool
    operator>=(const _square_matrix_row_iterator<Matrix, Value>& _a,
               const _square_matrix_row_iterator<Matrix, Value>& _b) {
      return not (_a < _b);
    }

    /// Greater than or equal comparison
    /** Among different types
     */
    template <typename MatrixA, typename ValueA,
              typename MatrixB, typename ValueB>
    inline bool
    operator>=(const _square_matrix_row_iterator<MatrixA, ValueA>& _a,
               const _square_matrix_row_iterator<MatrixB, ValueB>& _b) {
      return not (_a < _b);
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
