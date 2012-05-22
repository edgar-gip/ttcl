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

#ifndef TTCL_UT_RANGE_HXX
#define TTCL_UT_RANGE_HXX

/** @file
    Utilities - Range iterator and generator
    @author Edgar Gonzalez i Pellicer
*/

#include <iterator>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Range iterator
    /** A model of STL Random Access Iterator (Non-mutable)
     */
    template <typename T>
    class range_iterator {
    public:
      /// Iterator category
      typedef std::random_access_iterator_tag iterator_category;

      /// Value type
      typedef T value_type;

      /// Difference type
      typedef T difference_type;

      /// Pointer type
      typedef T* pointer;

      /// Reference type
      typedef T& reference;

      /// Const reference type
      typedef const T& const_reference;

    private:
      /// Value
      value_type value_;

    public:
      /// Constructor
      range_iterator(const value_type& _value = value_type()) :
        value_(_value) {
      }

      /// Constructor
      template <typename T2>
      range_iterator(const range_iterator<T2>& _other) :
        value_(*_other) {
      }

      /// Dereference
      const_reference
      operator*() const {
        return value_;
      }

      /// Preincrement
      range_iterator&
      operator++() {
        ++value_;
        return *this;
      }

      /// Postincrement
      range_iterator
      operator++(int) {
        range_iterator copy = *this;
        ++value_;
        return copy;
      }

      /// Increment
      range_iterator&
      operator+=(const difference_type& _incr) {
        value_ += _incr;
        return *this;
      }

      /// Predecrement
      range_iterator&
      operator--() {
        --value_;
        return *this;
      }

      /// Postdecrement
      range_iterator
      operator--(int) {
        range_iterator copy = *this;
        --value_;
        return copy;
      }

      /// Decrement
      range_iterator&
      operator-=(const difference_type& _decr) {
        value_ -= _decr;
        return *this;
      }

      /// Element operator
      value_type
      operator[](const difference_type& _index) const {
        return value_ + _index;
      }
    };

    /// Equality Comparison
    template <typename T>
    bool
    operator==(const range_iterator<T>& _a, const range_iterator<T>& _b) {
      return *_a == *_b;
    }

    /// Inequality comparison
    template <typename T>
    bool
    operator!=(const range_iterator<T>& _a, const range_iterator<T>& _b) {
      return !(_a == _b);
    }

    /// Difference
    template <typename T>
    typename range_iterator<T>::difference_type
    operator-(const range_iterator<T>& _a, const range_iterator<T>& _b) {
      return *_a - *_b;
    }

    /// Convenience function
    template <typename T>
    range_iterator<T>
    range(const T& _value) {
      return range_iterator<T>(_value);
    }

    /// Range generator
    /** A model of STL Adaptable Generator
     */
    template <typename T>
    class range_generator {
    public:
      /// Result type
      typedef T result_type;

    private:
      /// Value
      result_type value_;

      /// Increment
      result_type incr_;

    public:
      /// Constructor
      range_generator(const result_type& _value = result_type(),
                      const result_type& _incr  = result_type(1)) :
        value_(_value), incr_(_incr) {
      }

      /// Invocation
      result_type
      operator()() {
        result_type result = value_;
        value_ += incr_;
        return result;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
