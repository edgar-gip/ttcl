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
    @author Edgar Gonzalez i Pellicer
*/

#include <iterator>
#include <vector>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/make_signed.hpp>

#include <ttcl/c++0x.hxx>
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
              typename Container = std::vector<T> >
    class _square_matrix {
    private:
      // Check
      BOOST_MPL_ASSERT(( boost::is_same<T, typename Container::value_type> ));

    private:
      /// Child type
      typedef Child child_type;

    public:
      /// Container type
      typedef Container container_type;

      /// Element
      /** It is the underlying container value type
       */
      TTCL_IMPORT_R_TYPE(container_type, value_type, element);

      /// Size type
      TTCL_IMPORT_TYPE(container_type, size_type);

      /// Value type
      typedef _square_matrix_row_ref<child_type> value_type;

      /// Reference
      typedef _square_matrix_row_ref<child_type> reference;

      /// Const reference
      typedef const _square_matrix_row_ref<const child_type> const_reference;

      /// Pointer
      typedef std::auto_ptr<reference> pointer;

      /// Const pointer
      typedef std::auto_ptr<const_reference> const_pointer;

      /// Difference type
      typedef typename boost::make_signed<size_type>::type difference_type;

      /// Iterator
      typedef _square_matrix_iterator<child_type, reference> iterator;

      /// Const iterator
      typedef _square_matrix_iterator<const child_type,
                                      const_reference> const_iterator;

      /// Reverse iterator
      typedef _square_matrix_reverse_iterator<child_type, reference>
        reverse_iterator;

      /// Const reverse iterator
      typedef _square_matrix_reverse_iterator<const child_type, const_reference>
        const_reverse_iterator;

      /// Data iterator
      TTCL_IMPORT_R_TYPE(container_type, iterator, data_iterator);

      /// Data const iterator
      TTCL_IMPORT_R_TYPE(container_type, const_iterator, data_const_iterator);

      /// Data reverse iterator
      TTCL_IMPORT_R_TYPE(container_type, reverse_iterator,
                         data_reverse_iterator);

      /// Data const reverse iterator
      TTCL_IMPORT_R_TYPE(container_type, const_reverse_iterator,
                    data_const_reverse_iterator);

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
      /** @param _size      Size
          @param _data_size Undelying data size
          @param _element   Default value
       */
      _square_matrix(size_type _size,
                     size_type _data_size,
                     const element& _element) :
        data_(_data_size, _element), size_(_size) {
      }

#ifdef TTCL_CXX0X_NONPUBLIC_DEFAULTS
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
      /// Size
      size_type
      size() const {
        return size_;
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
        // Synonym for size
        return this->size();
      }

      /// Data size
      size_type
      data_size() const {
        return data_.size();
      }

      /// Empty
      bool
      empty() const {
        return size() == 0;
      }

    protected:
      /// Resize
      void
      resize(size_type _size,
             size_type _data_size,
             const element& _element) {
        data_.resize(_data_size, _element);
        size_ = _size;
      }

    public:
      /// Element access
      /** Non-const version
       */
      reference
      operator[](size_type _row) {
        return reference(static_cast<child_type*>(this), _row);
      }

      /// Element access
      /** const version
       */
      const_reference
      operator[](size_type _row) const {
        return const_reference(static_cast<const child_type*>(this), _row);
      }

      /// Begin
      /** Non-const version
       */
      iterator
      begin() {
        return iterator(static_cast<child_type*>(this), 0);
      }

      /// Begin
      /** const version
       */
      const_iterator
      begin() const {
        return const_iterator(static_cast<const child_type*>(this), 0);
      }

      /// End
      /** Non-const version
       */
      iterator
      end() {
        return iterator(static_cast<child_type*>(this), size());
      }

      /// End
      /** const version
       */
      const_iterator
      end() const {
        return const_iterator(static_cast<const child_type*>(this), size());
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
      data_const_iterator
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
      data_const_iterator
      data_end() const {
        return data_.end();
      }

      /// Data reverse begin
      /** Non-const version
       */
      data_reverse_iterator
      data_rbegin() {
        return data_.rbegin();
      }

      /// Data reverse begin
      /** const version
       */
      data_const_reverse_iterator
      data_rbegin() const {
        return data_.rbegin();
      }

      /// Data reverse end
      /** Non-const version
       */
      data_reverse_iterator
      data_rend() {
        return data_.rend();
      }

      /// Data reverse end
      /** const version
       */
      data_const_reverse_iterator
      data_rend() const {
        return data_.rend();
      }

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
      return (_m1.size() == _m2.size() and
              std::equal(_m1.begin(), _m1.end(),
                         _m2.begin()));
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
      return std::lexicographical_compare(_m1.begin(), _m1.end(),
                                          _m2.begin(), _m2.end());
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
