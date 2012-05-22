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

#ifndef TTCL_CO_WR_MATRIX_WRAP_HXX
#define TTCL_CO_WR_MATRIX_WRAP_HXX

/** @file
    Containers - Matrix wrapper
    @author Edgar Gonzalez i Pellicer
*/

#include <cstddef>

#include <ttcl/c++0x.hxx>
#include <ttcl/exception.hxx>
#include <ttcl/global.hxx>
#include <ttcl/wr/interface_wrap.hxx>
#include <ttcl/wr/shared_referee.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Wrappers Namespace
    namespace wr {

      /// Matrix interface
      class _matrix_interface :
	public ttcl::wr::shared_referee {
      public:
	/// Size type
	typedef size_t size_type;

	/// Constructor
	_matrix_interface(bool _owned = true,
			  uint _references = 0) :
	  ttcl::wr::shared_referee(_owned, _references) {
	}

	/// Size
	virtual size_type
	size() const = 0;

	/// Rows
	virtual size_type
	rows() const = 0;

	/// Columns
	virtual size_type
	columns() const = 0;
      };

      /// Matrix referee
      template <typename T,
		typename Interface>
      class _matrix_referee :
	public ttcl::wr::typed_shared_referee<T, Interface> {
      public:
	/// Size type
	TTCL_IMPORT_TYPE(Interface, size_type);

	/// Constructor
	_matrix_referee(T* _ptr = 0, bool _owned = true) :
	  ttcl::wr::typed_shared_referee<T, Interface>(_ptr, _owned) {
	}

	/// Get
	T*
	get() const {
	  return this->ptr_;
	}

	/// Size
	virtual size_type
	size() const {
	  return this->ptr_->size();
	}

	/// Rows
	virtual size_type
	rows() const {
	  return this->ptr_->rows();
	}

	/// Columns
	virtual size_type
	columns() const {
	  return this->ptr_->columns();
	}
      };

      /// Base matrix wrapper
      template <typename Interface>
      class _matrix_wrap :
	public ttcl::wr::interface_wrap<Interface> {
      public:
	/// Base type
	typedef ttcl::wr::interface_wrap<Interface> base_type;

	/// Size type
	TTCL_IMPORT_TYPE(Interface, size_type);

      protected:
	/// Empty Constructor
	TTCL_DEFAULT_NONPUBLIC_CONSTRUCTOR(_matrix_wrap);

	/// Constructor
	_matrix_wrap(Interface* _ptr) :
	  base_type(_ptr) {
	}

      public:
	/// Get!
	template <typename T>
	T*
	get() const {
	  const _matrix_referee<T, Interface>* tptr =
	    dynamic_cast<
	      const _matrix_referee<T, Interface>*>(this->ptr_.ptr());
	  if (not tptr)
	    TTCL_FIRE("Bad cast");
	  return tptr->get();
	}

	/// Size
	size_type
	size() const {
	  return this->ptr_->size();
	}

	/// Rows
	size_type
	rows() const {
	  return this->ptr_->rows();
	}

	/// Columns
	size_type
	columns() const {
	  return this->ptr_->columns();
	}
      };

      /// Matrix wrapper
      class matrix_wrap :
	public _matrix_wrap<_matrix_interface> {
      public:
	/// Base type
	typedef _matrix_wrap<_matrix_interface> base_type;

	/// Empty Constructor
	TTCL_DEFAULT_CONSTRUCTOR(matrix_wrap);

	/// Constructor
	template <typename T>
	matrix_wrap(T* _value, bool _owned = true) :
	  base_type(new _matrix_referee<
		      T, _matrix_interface>(_value, _owned)) {
	}

	/// Constructor
	template <typename T>
	matrix_wrap(T& _value, bool _owned = false) :
	  base_type(new _matrix_referee<
		      T, _matrix_interface>(&_value, _owned)) {
	}
      };
    }
  }
}

#endif
