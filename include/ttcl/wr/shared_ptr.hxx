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

#ifndef TTCL_WR_SHARED_PTR_HXX
#define TTCL_WR_SHARED_PTR_HXX

/** @file
    Wrappers - A shared pointer
    @author Edgar Gonzalez i Pellicer
*/

#include <cstdlib>

#include <ttcl/wr/shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Wrapper Namespace
  namespace wr {

    /// A shared pointer
    template <typename T = shared_referee>
    class shared_ptr {
    public:
      /// Element type
      typedef T element_type;

    private:
      /// Pointer to referee
      element_type* ptr_;

    public:
      /// Constructor
      shared_ptr(element_type* _ptr = NULL);

      /// Copy constructor
      shared_ptr(const shared_ptr& _other);

      /// Destructor
      ~shared_ptr();

      /// Assignment operator
      shared_ptr&
      operator=(const shared_ptr& _other);

      /// Indirection
      element_type&
      operator*() const;

      /// Indirection
      element_type*
      operator->() const;

      /// Pointer
      element_type*
      ptr() const;
    };

    /// Constructor
    template <typename T>
    shared_ptr<T>::
    shared_ptr(element_type* _ptr) :
      ptr_(_ptr) {
      // Add a reference
      if (ptr_)
        ptr_->add_reference();
    }

    /// Copy constructor
    template <typename T>
    shared_ptr<T>::
    shared_ptr(const shared_ptr<T>& _other) :
      ptr_(_other.ptr_) {
      // Add a reference
      if (ptr_)
        ptr_->add_reference();
    }

    /// Destructor
    template <typename T>
    shared_ptr<T>::
    ~shared_ptr() {
      // Remove a reference
      if (ptr_)
        ptr_->del_reference();
    }

    /// Assignment operator
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::
    operator=(const shared_ptr<T>& _other) {
      // Add a reference
      if (_other.ptr_)
        _other.ptr_->add_reference();

      // Remove a reference
      if (ptr_)
        ptr_->del_reference();

      // Assign
      ptr_ = _other.ptr_;

      // Return this
      return *this;
    }

    /// Indirection
    template <typename T>
    typename shared_ptr<T>::element_type& shared_ptr<T>::
    operator*() const {
      return *ptr_;
    }

    /// Indirection
    template <typename T>
    typename shared_ptr<T>::element_type* shared_ptr<T>::
    operator->() const {
      return ptr_;
    }

    /// Pointer
    template <typename T>
    typename shared_ptr<T>::element_type* shared_ptr<T>::
    ptr() const {
      return ptr_;
    }

    /// Equality comparison
    template <typename T>
    bool
    operator==(const shared_ptr<T>& _a,
               const shared_ptr<T>& _b) {
      return _a.ptr() == _b.ptr();
    }

    /// Equality comparison
    /** @overload
     */
    template <typename T>
    bool
    operator==(const shared_ptr<T>& _a, T* _b) {
      return _a.ptr() == _b;
    }

    /// Equality comparison
    /** @overload
     */
    template <typename T>
    bool
    operator==(T* _a, const shared_ptr<T>& _b) {
      return _a == _b.ptr();
    }

    /// Inequality comparison
    template <typename T>
    bool
    operator!=(const shared_ptr<T>& _a,
               const shared_ptr<T>& _b) {
      return _a.ptr() != _b.ptr();
    }

    /// Inequality comparison
    /** @overload
     */
    template <typename T>
    bool
    operator!=(const shared_ptr<T>& _a, T* _b) {
      return _a.ptr() != _b;
    }

    /// Inequality comparison
    /** @overload
     */
    template <typename T>
    bool
    operator!=(T* _a, const shared_ptr<T>& _b) {
      return _a != _b.ptr();
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
