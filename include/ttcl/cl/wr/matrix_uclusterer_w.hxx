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

#ifndef TTCL_CL_WR_MATRIX_UCLUSTERER_WRAP_HXX
#define TTCL_CL_WR_MATRIX_UCLUSTERER_WRAP_HXX

/** @file
    Clustering - Matrix unsupervised clusterer wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/soft_clustering.hxx>
#include <ttcl/dt/wr/matrix_w.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/tu/tuning.hxx>
#include <ttcl/wr/interface_wrap.hxx>
#include <ttcl/wr/shared_referee.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Wrappers Namespace
    namespace wr {

      /// Matrix unsupervised clusterer interface
      template <typename Choices>
      class _matrix_uclusterer_interface :
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
        _matrix_uclusterer_interface(bool _owned = true,
                                     uint _references = 0) :
          ttcl::wr::shared_referee(_owned, _references) {
        }

        /// Perform the tuning
        virtual void
        tune(const tu::tuning& _tuning) const = 0;

        /// Perform the hard clustering
        virtual void
        hard_cluster_on(hard_clustering_type& _hard_clustering,
                        const dt::wr::matrix_w& _matrix) const = 0;

        /// Perform the clustering
        virtual hard_clustering_type
        hard_cluster(const dt::wr::matrix_w& _matrix) const = 0;

        /// Perform the soft clustering
        virtual void
        soft_cluster_on(soft_clustering_type& _soft_clustering,
                        const dt::wr::matrix_w& _matrix) const = 0;

        /// Perform the clustering
        virtual soft_clustering_type
        soft_cluster(const dt::wr::matrix_w& _matrix) const = 0;
      };

      /// Matrix unsupervised clusterer referee
      template <typename T,
                typename Interface>
      class _matrix_uclusterer_referee :
        public ttcl::wr::typed_shared_referee<T, Interface> {
      private:
        // Matrix type
        TTCL_IMPORT_TYPE(T, matrix_type);

        /// Hard clustering type
        TTCL_IMPORT_TYPE(Interface, hard_clustering_type);

        /// Soft clustering type
        TTCL_IMPORT_TYPE(Interface, soft_clustering_type);

      public:
        /// Constructor
        _matrix_uclusterer_referee(T* _ptr = 0, bool _owned = true) :
          ttcl::wr::typed_shared_referee<T, Interface>(_ptr, _owned) {
        }

        /// Perform the tuning
        virtual void
        tune(const tu::tuning& _tuning) const {
          // Call
          this->ptr_->tune(_tuning);
        }

        /// Perform the hard clustering
        virtual void
        hard_cluster_on(hard_clustering_type& _hard_clustering,
                        const dt::wr::matrix_w& _matrix) const {
          // Convert to matrix type
          const matrix_type* matrix = _matrix.get<matrix_type>();

          // Call
          this->ptr_->hard_cluster_on(_hard_clustering, *matrix);
        }

        /// Perform the clustering
        virtual hard_clustering_type
        hard_cluster(const dt::wr::matrix_w& _matrix) const {
          // Convert to matrix type
          const matrix_type* matrix = _matrix.get<matrix_type>();

          // Call
          return this->ptr_->hard_cluster(*matrix);
        }

        /// Perform the soft clustering
        virtual void
        soft_cluster_on(soft_clustering_type& _soft_clustering,
                        const dt::wr::matrix_w& _matrix) const {
          // Convert to matrix type
          const matrix_type* matrix = _matrix.get<matrix_type>();

          // Call
          this->ptr_->soft_cluster_on(_soft_clustering, *matrix);
        }

        /// Perform the clustering
        virtual soft_clustering_type
        soft_cluster(const dt::wr::matrix_w& _matrix) const {
          // Convert to matrix type
          const matrix_type* matrix = _matrix.get<matrix_type>();

          // Call
          return this->ptr_->soft_cluster(*matrix);
        }
      };

      /// Base matrix unsupervised clusterer wrapper
      template <typename Interface>
      class _matrix_uclusterer_w :
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
        _matrix_uclusterer_w() :
          base_type() {
        }

        /// Constructor
        _matrix_uclusterer_w(Interface* _ptr) :
          base_type(_ptr) {
        }

      public:
        /// Perform the tuning
        void
        tune(const tu::tuning& _tuning) const {
          // Call
          this->ptr_->tune(_tuning);
        }

        /// Perform the hard clustering
        void
        hard_cluster_on(hard_clustering_type& _hard_clustering,
                        const dt::wr::matrix_w& _matrix) const {
          // Call
          this->ptr_->hard_cluster_on(_hard_clustering, _matrix);
        }

        /// Perform the clustering
        hard_clustering_type
        hard_cluster(const dt::wr::matrix_w& _matrix) const {
          // Call
          return this->ptr_->hard_cluster(_matrix);
        }

        /// Perform the soft clustering
        void
        soft_cluster_on(soft_clustering_type& _soft_clustering,
                        const dt::wr::matrix_w& _matrix) const {
          // Call
          this->ptr_->soft_cluster_on(_soft_clustering, _matrix);
        }

        /// Perform the clustering
        soft_clustering_type
        soft_cluster(const dt::wr::matrix_w& _matrix) const {
          // Call
          return this->ptr_->soft_cluster(_matrix);
        }
      };

      /// Matrix unsupervised clusterer wrapper
      template <typename Choices = tu::default_choices>
      class matrix_uclusterer_w :
        public _matrix_uclusterer_w<
          _matrix_uclusterer_interface<Choices> > {
      private:
        /// Interface
        typedef _matrix_uclusterer_interface<Choices> interface;

        /// Base type
        typedef _matrix_uclusterer_w<interface> base_type;

      public:
        /// Empty Constructor
        matrix_uclusterer_w() :
          base_type() {
        }

        /// Constructor
        template <typename T>
        matrix_uclusterer_w(T* _value, bool _owned = true) :
          base_type(new _matrix_uclusterer_referee<T, interface>(_value,
                                                                 _owned)) {
        }

        /// Constructor
        template <typename T>
        matrix_uclusterer_w(T& _value, bool _owned = false) :
          base_type(new _matrix_uclusterer_referee<T, interface>(&_value,
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
