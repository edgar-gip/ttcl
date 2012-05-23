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

#ifndef TTCL_CO__SQUARE_MATRIX_ITERATOR_HXX
#define TTCL_CO__SQUARE_MATRIX_ITERATOR_HXX

#if !defined(TTCL_CO__SQUARE_MATRIX_HXX) && \
    !defined(TTCL_CO__SQUARE_MATRIX_REVERSE_ITERATOR_HXX)
#error "Cannot include <ttcl/co/_square_matrix_iterator.hxx> directly"
#endif

/** @file
    Containers - Square matrix iterator
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstddef>
#include <iterator>
#include <memory>

#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <ttcl/assert.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    // Pre-declarations
    template <typename Matrix, typename Ref>
    class _square_matrix_iterator;

    template <typename Matrix, typename Ref>
    class _square_matrix_reverse_iterator;

    template <typename Matrix, typename Ref>
    inline bool
    operator==(const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b);

    template <typename Matrix, typename Ref>
    inline bool
    operator< (const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b);


    /// Square matrix iterator
    /** A model of Random Access Iterator
     */
    template <typename Matrix, typename Ref>
    class _square_matrix_iterator {
    private:
      /// Matrix type
      typedef Matrix matrix_type;

      /// Size type
      typedef typename matrix_type::size_type size_type;

    public:
      /// Iterator category
      typedef std::random_access_iterator_tag iterator_category;

      /// Value type
      typedef Ref value_type;

      /// Difference type
      typedef typename boost::make_signed<size_type>::type difference_type;

      /// Pointer
      typedef std::auto_ptr<Ref> pointer;

      /// Reference
      typedef Ref reference;

    private:
      /// Matrix
      matrix_type* matrix_;

      /// Row
      size_type row_;

    public:
      /// Constructor
      _square_matrix_iterator(matrix_type* _matrix = 0,
                              size_type _row = 0) :
        matrix_(_matrix), row_(_row) {
      }

      /// Iterator conversion
      template <typename MatrixO, typename RefO>
      _square_matrix_iterator
        (const _square_matrix_iterator<MatrixO, RefO>& _other) :
        matrix_(_other.matrix_), row_(_other.row_) {
      }

      /// @name Forward iterator requirements
      /// @{

      /// Indirection
      reference
      operator*() const {
        return reference(matrix_, row_);
      }

      /// Indirection
      pointer
      operator->() const {
        return pointer(new reference(matrix_, row_));
      }

      /// Preincrement
      _square_matrix_iterator&
      operator++() {
        ++row_;
        return *this;
      }

      /// Postincrement
      _square_matrix_iterator
      operator++(int) {
        _square_matrix_iterator ret(*this);
        ++row_;
        return ret;
      }

      /// @}

      /// @name Bidirectional iterator requirements
      /// @{

      /// Predecrement
      _square_matrix_iterator&
      operator--() {
        --row_;
        return *this;
      }


      /// Postdecrement
      _square_matrix_iterator
      operator--(int) {
        _square_matrix_iterator ret(*this);
        --row_;
        return ret;
      }

      /// @}

      /// @name Random access iterator requirements
      /// @{

      /// Access
      reference
      operator[](const difference_type& _n) const {
        return (*matrix_)[row_ + _n];
      }

      /// Increment
      _square_matrix_iterator&
      operator+=(const difference_type& _n) {
        row_ += _n;
        return *this;
      }

      /// Addition
      _square_matrix_iterator
      operator+(const difference_type& _n) const {
        return _square_matrix_iterator(matrix_, row_ + _n);
      }

      /// Decrement
      _square_matrix_iterator&
      operator-=(const difference_type& _n) {
        row_ -= _n;
        return *this;
      }

      /// Subtraction
      _square_matrix_iterator
      operator-(const difference_type& _n) const {
        return _square_matrix_iterator(matrix_, row_ - _n);
      }

      /// Difference
      difference_type
      operator-(const _square_matrix_iterator& _other) const {
        TTCL_ASSERT(matrix_ == _other.matrix_);
        return row_ - _other.row_;
      }

      /// @}

      // Friends
      friend
      bool operator== <Matrix, Ref>
        (const _square_matrix_iterator<Matrix, Ref>& _a,
         const _square_matrix_iterator<Matrix, Ref>& _b);

      template <typename MatrixA, typename RefA,
                typename MatrixB, typename RefB>
      friend
      bool operator==
        (const _square_matrix_iterator<MatrixA, RefA>& _a,
         const _square_matrix_iterator<MatrixB, RefB>& _b);

      friend
      bool operator<  <Matrix, Ref>
        (const _square_matrix_iterator<Matrix, Ref>& _a,
         const _square_matrix_iterator<Matrix, Ref>& _b);

      template <typename MatrixA, typename RefA,
                typename MatrixB, typename RefB>
      friend
      bool operator<
        (const _square_matrix_iterator<MatrixA, RefA>& _a,
         const _square_matrix_iterator<MatrixB, RefB>& _b);

      template <typename MatrixO, typename RefO>
      friend class _square_matrix_iterator;

      friend class _square_matrix_reverse_iterator<Matrix, Ref>;
    };

    /// Equality comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator==(const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      return _a.matrix_ == _b.matrix_ and
             _a.row_    == _b.row_;
    }

    /// Equality comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator==(const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      return _a.matrix_ == _b.matrix_ and
             _a.row_    == _b.row_;
    }

    /// Inequality comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator!=(const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      return not (_a == _b);
    }

    /// Inequality comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator!=(const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      return not (_a == _b);
    }

    /// Less than comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator< (const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      TTCL_ASSERT(_a.matrix_ == _b.matrix_);
      return _a.row_ < _b.row_;
    }

    /// Less than comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator< (const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      TTCL_ASSERT(_a.matrix_ == _b.matrix_);
      return _a.row_ < _b.row_;
    }

    /// Less than or equal comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator<=(const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      return not (_b < _a);
    }

    /// Less than or equal comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator<=(const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      return not (_b < _a);
    }

    /// Greater than comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator> (const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      return _b < _a;
    }

    /// Greater than comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator> (const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      return _b < _a;
    }

    /// Greater than or equal comparison
    template <typename Matrix, typename Ref>
    inline bool
    operator>=(const _square_matrix_iterator<Matrix, Ref>& _a,
               const _square_matrix_iterator<Matrix, Ref>& _b) {
      return not (_a < _b);
    }

    /// Greater than or equal comparison
    /** Among different types
     */
    template <typename MatrixA, typename RefA,
              typename MatrixB, typename RefB>
    inline bool
    operator>=(const _square_matrix_iterator<MatrixA, RefA>& _a,
               const _square_matrix_iterator<MatrixB, RefB>& _b) {
      return not (_a < _b);
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
