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

#ifndef TTCL_DT_WR_DATA_W_HXX
#define TTCL_DT_WR_DATA_W_HXX

/** @file
    Data - Data wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstddef>

#include <ttcl/c++11.hxx>
#include <ttcl/exception.hxx>
#include <ttcl/wr/interface_wrap.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Data Namespace
  namespace dt {

    /// Wrappers Namespace
    namespace wr {

      /// Data interface
      class _data_interface :
        public ttcl::wr::shared_referee {
      public:
        /// Size type
        typedef size_t size_type;

        /// Constructor
        _data_interface(bool _owned = true,
                        uint _references = 0) :
          ttcl::wr::shared_referee(_owned, _references) {
        }

        /// Samples
        virtual size_type
        samples() const = 0;
      };

      /// Data referee
      template <typename T,
                typename Interface>
      class _data_referee :
        public ttcl::wr::typed_shared_referee<T, Interface> {
      public:
        /// Size type
        TTCL_IMPORT_TYPE(Interface, size_type);

        /// Constructor
        _data_referee(T* _ptr = 0, bool _owned = true) :
          ttcl::wr::typed_shared_referee<T, Interface>(_ptr, _owned) {
        }

        /// Get
        T*
        get() const {
          return this->ptr_;
        }

        /// Samples
        virtual size_type
        samples() const {
          return this->ptr_->samples();
        }
      };

      /// Base data wrapper
      template <typename Interface>
      class _data_w :
        public ttcl::wr::interface_wrap<Interface> {
      public:
        /// Base type
        typedef ttcl::wr::interface_wrap<Interface> base_type;

        /// Size type
        TTCL_IMPORT_TYPE(Interface, size_type);

      protected:
        /// Empty Constructor
        TTCL_DEFAULT_NONPUBLIC_CONSTRUCTOR(_data_w);

        /// Constructor
        _data_w(Interface* _ptr) :
          base_type(_ptr) {
        }

        /// Copy constructor
        _data_w(const _data_w& _other) :
          base_type(_other) {
        }

      public:
        /// Is?
        template <typename T>
        bool
        is() const {
          return dynamic_cast<
            const _data_referee<T, Interface>*>(this->ptr_.ptr()) != NULL;
        }

        /// Get!
        template <typename T>
        T*
        get() const {
          const _data_referee<T, Interface>* tptr =
            dynamic_cast<const _data_referee<T, Interface>*>(this->ptr_.ptr());
          if (not tptr)
            TTCL_FIRE("Bad cast");
          return tptr->get();
        }

        /// Samples
        size_type
        samples() const {
          return this->ptr_->samples();
        }
      };

      /// Data wrapper
      class data_w :
        public _data_w<_data_interface> {
      private:
        /// Interface type
        typedef _data_interface interface;

        /// Base type
        typedef _data_w<interface> base_type;

      public:
        /// Empty Constructor
        TTCL_DEFAULT_CONSTRUCTOR(data_w);

        /// Constructor
        template <typename T>
        data_w(T* _value, bool _owned = true) :
          base_type(new _data_referee<T, interface>(_value, _owned)) {
        }

        /// Constructor
        template <typename T>
        data_w(T& _value, bool _owned = false) :
          base_type(new _data_referee<T, interface>(&_value, _owned)) {
        }

        /// Copy constructor
        data_w(const data_w& _other) :
          base_type(_other) {
        }

        /// Copy constructor
        data_w(data_w& _other) :
          base_type(_other) {
        }
      };
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
