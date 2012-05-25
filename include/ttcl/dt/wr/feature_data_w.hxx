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

#ifndef TTCL_DT_WR_FEATURE_DATA_W_HXX
#define TTCL_DT_WR_FEATURE_DATA_W_HXX

/** @file
    Data - Feature-based data wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstddef>

#include <ttcl/c++11.hxx>
#include <ttcl/exception.hxx>
#include <ttcl/global.hxx>
#include <ttcl/dt/wr/data_w.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Data Namespace
  namespace dt {

    /// Wrappers Namespace
    namespace wr {

      /// Feature-based data interface
      class _feature_data_interface :
        public _data_interface {
      public:
        /// Size type
        TTCL_IMPORT_TYPE(_data_interface, size_type);

        /// Constructor
        _feature_data_interface(bool _owned = true,
                                uint _references = 0) :
          _data_interface(_owned, _references) {
        }

        /// Features
        virtual size_type
        features() const = 0;
      };

      /// Feature-based data referee
      template <typename T,
                typename Interface>
      class _feature_data_referee :
        public _data_referee<T, Interface> {
      public:
        /// Size type
        TTCL_IMPORT_TYPE(Interface, size_type);

        /// Constructor
        _feature_data_referee(T* _ptr = 0, bool _owned = true) :
          _data_referee<T, Interface>(_ptr, _owned) {
        }

        /// Features
        virtual size_type
        features() const {
          return this->ptr_->features();
        }
      };

      /// Base feature-based data wrapper
      template <typename Interface>
      class _feature_data_w :
        public _data_w<Interface> {
      public:
        /// Base type
        typedef _data_w<Interface> base_type;

        /// Size type
        TTCL_IMPORT_TYPE(Interface, size_type);

      protected:
        /// Empty Constructor
        TTCL_DEFAULT_NONPUBLIC_CONSTRUCTOR(_feature_data_w);

        /// Constructor
        _feature_data_w(Interface* _ptr) :
          base_type(_ptr) {
        }

        /// Copy constructor
        _feature_data_w(const _feature_data_w& _other) :
          base_type(_other) {
        }

      public:
        /// Features
        size_type
        features() const {
          return this->ptr_->features();
        }
      };

      /// Feature-based data wrapper
      class feature_data_w :
        public _feature_data_w<_feature_data_interface> {
      private:
        /// Interface
        typedef _feature_data_interface interface;

        /// Base type
        typedef _feature_data_w<interface> base_type;

      public:
        /// Empty Constructor
        TTCL_DEFAULT_CONSTRUCTOR(feature_data_w);

        /// Constructor
        template <typename T>
        feature_data_w(T* _value, bool _owned = true) :
          base_type(new _feature_data_referee<T, interface>(_value, _owned)) {
        }

        /// Constructor
        template <typename T>
        feature_data_w(T& _value, bool _owned = false) :
          base_type(new _feature_data_referee<T, interface>(&_value, _owned)) {
        }

        /// Copy constructor
        feature_data_w(const feature_data_w& _other) :
          base_type(_other) {
        }

        /// Copy constructor
        feature_data_w(feature_data_w& _other) :
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
