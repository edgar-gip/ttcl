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

#ifndef TTCL_CL_WR_DATA_MODEL_W_HXX
#define TTCL_CL_WR_DATA_MODEL_W_HXX

/** @file
    Clustering - Data model wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/soft_clustering.hxx>
#include <ttcl/dt/wr/data_w.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/wr/interface_wrap.hxx>
#include <ttcl/wr/shared_referee.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Wrappers Namespace
    namespace wr {

      /// Data model interface
      template <typename Choices>
      class _data_model_interface :
        public ttcl::wr::shared_referee {
      private:
        /// Hard clustering container
        typedef TTCL_TU_GET_CHOICE(Choices, hard_clustering_container)
          hard_clustering_container_type;

      public:
        /// Hard clustering type
        typedef hard_clustering<hard_clustering_container_type>
          hard_clustering_type;

      private:
        /// Soft clustering container
        typedef TTCL_TU_GET_CHOICE(Choices, soft_clustering_container)
          soft_clustering_container_type;

      public:
        /// Soft clustering type
        typedef soft_clustering<soft_clustering_container_type>
          soft_clustering_type;

        /// Constructor
        _data_model_interface(bool _owned = true,
                              uint _references = 0) :
          ttcl::wr::shared_referee(_owned, _references) {
        }

        /// Perform the hard clustering
        virtual void
        hard_cluster_on(hard_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const = 0;

        /// Perform the hard clustering
        virtual hard_clustering_type
        hard_cluster(const dt::wr::data_wrap& _data) const = 0;

        /// Perform the soft clustering
        virtual void
        soft_cluster_on(soft_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const = 0;

        /// Perform the soft clustering
        virtual soft_clustering_type
        soft_cluster(const dt::wr::data_wrap& _data) const = 0;
      };

      /// Data model referee
      template <typename T,
                typename Interface>
      class _data_model_referee :
        public ttcl::wr::typed_shared_referee<T, Interface> {
      private:
        // Data type
        TTCL_IMPORT_TYPE(T, data_type);

        /// Hard clustering type
        TTCL_IMPORT_TYPE(Interface, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(Interface, soft_clustering_type);

      public:
        /// Constructor
        _data_model_referee(T* _ptr = 0, bool _owned = true) :
          ttcl::wr::typed_shared_referee<T, Interface>(_ptr, _owned) {
        }

        /// Perform the hard clustering
        virtual void
        hard_cluster_on(hard_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          this->ptr_->hard_cluster_on(_clustering, *data);
        }

        /// Perform the hard clustering
        virtual hard_clustering_type
        hard_cluster(const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          return this->ptr_->hard_cluster(*data);
        }

        /// Perform the soft clustering
        virtual void
        soft_cluster_on(soft_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          this->ptr_->soft_cluster_on(_clustering, *data);
        }

        /// Perform the soft clustering
        virtual soft_clustering_type
        soft_cluster(const dt::wr::data_wrap& _data) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          return this->ptr_->soft_cluster(*data);
        }
      };

      /// Base data model wrapper
      template <typename Interface>
      class _data_model_w :
        public ttcl::wr::interface_wrap<Interface> {
      public:
        /// Base type
        typedef ttcl::wr::interface_wrap<Interface> base_type;

        /// Hard clustering type
        TTCL_IMPORT_TYPE(Interface, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(Interface, soft_clustering_type);

      protected:
        /// Empty constructor
        _data_model_w() :
          base_type() {
        }

        /// Constructor
        _data_model_w(Interface* _ptr) :
          base_type(_ptr) {
        }

      public:
        /// Perform the hard clustering
        void
        hard_cluster_on(hard_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const {
          // Call
          this->ptr_->hard_cluster_on(_clustering, _data);
        }

        /// Perform the hard clustering
        hard_clustering_type
        hard_cluster(const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->hard_cluster(_data);
        }

        /// Perform the soft clustering
        void
        soft_cluster_on(soft_clustering_type& _clustering,
                        const dt::wr::data_wrap& _data) const {
          // Call
          this->ptr_->soft_cluster_on(_clustering, _data);
        }

        /// Perform the soft clustering
        soft_clustering_type
        soft_cluster(const dt::wr::data_wrap& _data) const {
          // Call
          return this->ptr_->soft_cluster(_data);
        }
      };

      /// Data model wrapper
      template <typename Choices = tu::default_choices>
      class data_model_w :
        public _data_model_w<_data_model_interface<Choices> > {
      private:
        /// Interface
        typedef _data_model_interface<Choices> interface;

        /// Base type
        typedef _data_model_w<interface> base_type;

      public:
        /// Empty Constructor
        data_model_w() :
          base_type() {
        }

        /// Constructor
        template <typename T>
        data_model_w(T* _value, bool _owned = true) :
          base_type(new _data_model_referee<T, interface>(_value,
                                                          _owned)) {
        }

        /// Constructor
        template <typename T>
        data_model_w(T& _value, bool _owned = false) :
          base_type(new _data_model_referee<T, interface>(&_value,
                                                          _owned)) {
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
