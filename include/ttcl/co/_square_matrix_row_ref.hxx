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

#ifndef TTCL_CO__SQUARE_MATRIX_ROW_REF_HXX
#define TTCL_CO__SQUARE_MATRIX_ROW_REF_HXX

#if !defined(TTCL_CO__SQUARE_MATRIX_HXX)
#error "Cannot include <ttcl/co/_square_matrix_row_ref.hxx> directly"
#endif

/** @file
    Containers - Square matrix row reference proxy
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <cstddef>
#include <iterator>

#include <boost/utility.hpp>

#include <ttcl/global.hxx>
#include <ttcl/co/_square_matrix_row_iterator.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Square matrix row reference proxy
    /** A model of Random Access Container
     */
    template <typename Matrix>
    class _square_matrix_row_ref {
    private:
      /// Matrix type
      typedef Matrix matrix_type;

    public:
      /// Value type
      TTCL_IMPORT_TYPE(matrix_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(matrix_type, size_type);

      /// Reference type
      TTCL_IMPORT_TYPE(matrix_type, reference);

      /// Const reference type
      TTCL_IMPORT_TYPE(matrix_type, const_reference);

      /// Pointer
      TTCL_IMPORT_TYPE(matrix_type, pointer);

      /// Difference type
      TTCL_IMPORT_TYPE(matrix_type, difference_type);

      /// Iterator
      typedef _square_matrix_row_iterator<matrix_type,
                                          value_type> iterator;

      /// Const iterator
      typedef _square_matrix_row_iterator<const matrix_type,
                                          const value_type> const_iterator;

      /// Reverse iterator
      typedef typename std::reverse_iterator<iterator> reverse_iterator;

      /// Const reverse iterator
      typedef typename std::reverse_iterator<const_iterator>
        const_reverse_iterator;

    private:
      /// Matrix
      matrix_type* matrix_;

      /// Row
      int row_;

    public:
      /// Constructor
      _square_matrix_row_ref(matrix_type* _matrix = 0, int _row = 0) :
        matrix_(_matrix), row_(_row) {
      }

      /// Size
      size_type
      size() const {
        return matrix_->columns();
      }

      /// Maximum size
      size_type
      max_size() const {
        return matrix_->columns();
      }

      /// Empty?
      bool
      empty() const {
        return this->size() == 0;
      }

      /// Element access
      /** Non-const version
       */
      reference
      operator[](size_type _col) {
        return (*matrix_)(row_, _col);
      }

      /// Element access
      /** const version
       */
      const_reference
      operator[](size_type _col) const {
        return (*(const_cast<const matrix_type*>(matrix_)))(row_, _col);
      }

      /// Begin
      /** Non-const version
       */
      iterator
      begin() {
        return iterator(matrix_, row_, 0);
      }

      /// Begin
      /** const version
       */
      const_iterator
      begin() const {
        return const_iterator(matrix_, row_, 0);
      }

      /// End
      /** Non-const version
       */
      iterator
      end() {
        return iterator(matrix_, row_, this->size());
      }

      /// End
      /** const version
       */
      const_iterator
      end() const {
        return const_iterator(matrix_, row_, this->size());
      }

      /// Reverse begin
      /** Non-const version
       */
      reverse_iterator
      rbegin() {
        return reverse_iterator(end());
      }

      /// Reverse begin
      /** const version
       */
      const_reverse_iterator
      rbegin() const {
        return const_reverse_iterator(end());
      }

      /// Reverse end
      /** Non-const version
       */
      reverse_iterator
      rend() {
        return reverse_iterator(begin());
      }

      /// Reverse end
      /** const version
       */
      const_reverse_iterator
      rend() const {
        return const_reverse_iterator(begin());
      }

      /// Swap
      void
      swap(_square_matrix_row_ref& _other) {
        std::swap(matrix_, _other.matrix_);
        std::swap(row_,    _other.row_);
      }
    };

    /// Equality comparison
    template <typename Matrix>
    inline bool
    operator==(const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return (_r1.size() == _r2.size() and
              std::equal(_r1.begin(), _r1.end(),
                         _r2.begin()));
    }

    /// Inequality comparison
    template <typename Matrix>
    inline bool
    operator!=(const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return not (_r1 == _r2);
    }

    /// Less than comparison
    template <typename Matrix>
    inline bool
    operator< (const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return std::lexicographical_compare(_r1.begin(), _r1.end(),
                                          _r2.begin(), _r2.end());
    }

    /// Less than or equal comparison
    template <typename Matrix>
    inline bool
    operator<=(const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return not (_r2 < _r1);
    }

    /// Greater than comparison
    template <typename Matrix>
    inline bool
    operator> (const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return (_r2 < _r1);
    }

    /// Greater than or equal comparison
    template <typename Matrix>
    inline bool
    operator>=(const _square_matrix_row_ref<Matrix>& _r1,
               const _square_matrix_row_ref<Matrix>& _r2) {
      return not (_r1 < _r2);
    }
  }
}

/// Standard namespace
namespace std {

  /// Swap
  /** Specialization
   */
  template <typename Matrix>
  inline void
  swap(const ttcl::co::_square_matrix_row_ref<Matrix>& _r1,
       const ttcl::co::_square_matrix_row_ref<Matrix>& _r2) {
    return _r1.swap(_r2);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
