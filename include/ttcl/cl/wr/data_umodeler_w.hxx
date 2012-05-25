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

#ifndef TTCL_CL_WR_DATA_UMODELER_W_HXX
#define TTCL_CL_WR_DATA_UMODELER_W_HXX

/** @file
    Clustering - Data unsupervised modeler wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/wr/data_model_w.hxx>
#include <ttcl/cl/wr/data_uclusterer_w.hxx>
#include <ttcl/dt/wr/data_w.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Wrappers Namespace
    namespace wr {

      /// Data unsupervised modeler interface
      template <typename Choices>
      class _data_umodeler_interface :
        public _data_uclusterer_interface<Choices> {
      public:
        /// Base type
        typedef _data_uclusterer_interface<Choices> base_type;

        /// Hard clustering type
        TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

        /// Model type
        typedef data_model_w<Choices> model_wrap_type;

        /// Constructor
        _data_umodeler_interface(bool _owned = true,
                                 uint _references = 0) :
          base_type(_owned, _references) {
        }

        /// Create a model
        virtual model_wrap_type
        create_model(const dt::wr::data_wrap& _data) const = 0;

        /// Model
        virtual model_wrap_type
        hard_model_on(hard_clustering_type& _hard_clustering,
                      const dt::wr::data_wrap& _data) const = 0;

        /// Model
        virtual model_wrap_type
        soft_model_on(soft_clustering_type& _hard_clustering,
                      const dt::wr::data_wrap& _data) const = 0;

        /// Model
        virtual model_wrap_type
        model(const dt::wr::data_wrap& _data) const = 0;
      };

      /// Data unsupervised modeler referee
      template <typename T,
                typename Interface>
      class _data_umodeler_referee :
        public _data_uclusterer_referee<T, Interface> {
      private:
        // Data type
        TTCL_IMPORT_TYPE(T, data_type);

        // Model type
        TTCL_IMPORT_TYPE(T, model_type);

        /// Hard clustering type
        TTCL_IMPORT_TYPE(Interface, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(Interface, soft_clustering_type);

        /// Model wrap type
        TTCL_IMPORT_TYPE(Interface, model_wrap_type);

      public:
        /// Constructor
        _data_umodeler_referee(T* _ptr = 0, bool _owned = true) :
          _data_uclusterer_referee<T, Interface>(_ptr, _owned) {
        }

        /// Create a model
        virtual model_wrap_type
        create_model(const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call and return
          return model_wrap_type
            (this->ptr_->create_model(*data));
        }

        /// Model
        virtual model_wrap_type
        hard_model_on(hard_clustering_type& _hard_clustering,
                      const dt::wr::data_wrap& _data) const {
          // Convert data type
          const data_type* data = _data .get<data_type> ();

          // Call and return
          return model_wrap_type
            (this->ptr_->hard_model_on(_hard_clustering, *data));
        }

        /// Model
        virtual model_wrap_type
        soft_model_on(soft_clustering_type& _soft_clustering,
                      const dt::wr::data_wrap& _data) const {
          // Convert data type
          const data_type* data = _data .get<data_type> ();

          // Call and return
          return model_wrap_type
            (this->ptr_->soft_model_on(_soft_clustering, *data));
        }

        /// Model
        virtual model_wrap_type
        model(const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call and return
          return model_wrap_type(this->ptr_->model(*data));
        }
      };

      /// Base data unsupervised modeler wrapper
      template <typename Interface>
      class _data_umodeler_w :
        public _data_uclusterer_w<Interface> {
      public:
        /// Base type
        typedef _data_uclusterer_w<Interface> base_type;

        /// Hard clustering type
        TTCL_IMPORT_TYPE(Interface, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(Interface, soft_clustering_type);

        /// Model wrap type
        TTCL_IMPORT_TYPE(Interface, model_wrap_type);

      protected:
        /// Empty constructor
        _data_umodeler_w() :
          base_type() {
        }

        /// Constructor
        _data_umodeler_w(Interface* _ptr) :
          base_type(_ptr) {
        }

      public:
        /// Create a model
        virtual model_wrap_type
        create_model(const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->create_model(_data);
        }

        /// Model
        virtual model_wrap_type
        hard_model_on(hard_clustering_type& _hard_clustering,
                      const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->hard_model_on(_hard_clustering, _data);
        }

        /// Model
        virtual model_wrap_type
        soft_model_on(soft_clustering_type& _soft_clustering,
                      const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->soft_model_on(_soft_clustering, _data);
        }

        /// Model
        virtual model_wrap_type
        model(const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->model(_data);
        }
      };

      /// Data unsupervised modeler wrapper
      template <typename Choices = tu::default_choices>
      class data_umodeler_w :
        public _data_umodeler_w<
          _data_umodeler_interface<Choices> > {
      private:
        /// Interface
        typedef _data_umodeler_interface<Choices> interface;

        /// Base type
        typedef _data_umodeler_w<interface> base_type;

      public:
        /// Empty Constructor
        data_umodeler_w() :
          base_type() {
        }

        /// Constructor
        template <typename T>
        data_umodeler_w(T* _value, bool _owned = true) :
          base_type(new _data_umodeler_referee<T, interface>(_value, _owned)) {
        }

        /// Constructor
        template <typename T>
        data_umodeler_w(T& _value, bool _owned = false) :
          base_type(new _data_umodeler_referee<T, interface>(&_value, _owned)) {
        }
      };
    }
  }
};

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
