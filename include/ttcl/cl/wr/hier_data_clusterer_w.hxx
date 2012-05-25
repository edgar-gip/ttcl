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

#ifndef TTCL_CL_WR_HIER_DATA_CLUSTERER_W_HXX
#define TTCL_CL_WR_HIER_DATA_CLUSTERER_W_HXX

/** @file
    Clustering - Hierarchical data clusterer wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/wr/data_w.hxx>
#include <ttcl/cl/wr/data_clusterer_w.hxx>
#include <ttcl/hj/options.hxx>
#include <ttcl/hj/hier_data_clusterer.hxx>
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

      /// Hierarchical data clusterer interface
      template <typename Choices>
      class _hier_data_clusterer_interface :
        public cl::wr::_data_clusterer_interface<Choices> {
      public:
        /// Value type
        typedef TTCL_TU_GET_CHOICE(Choices, dendrogram_value) value_type;

        /// Dendrogram type
        typedef dendrogram<value_type> dendrogram_type;

        /// Constructor
        _hier_data_clusterer_interface(bool _owned = true,
                                       uint _references = 0) :
          cl::wr::_data_clusterer_interface<Choices>(_owned, _references) {
        }

        /// Perform the clustering
        /** @param _dendrogram Target dendrogram
            @param _data Data
            @param _n_clusters Number of clusters
        */
        virtual void
        hier_cluster_on(dendrogram_type& _dendrogram,
                        const cl::wr::data_w& _data,
                        const uint _n_clusters = 1) const = 0;

        /// Perform the clustering
        /** Functional convenience version
            @param _data Data
            @param _n_clusters Number of clusters
        */
        virtual dendrogram_type
        hier_cluster(const cl::wr::data_w& _data,
                     const uint _n_clusters = 1) const = 0;
      };

      /// Hierarchical data clusterer referee
      template <typename T,
                typename Interface>
      class _hier_data_clusterer_referee :
        public cl::wr::_data_clusterer_referee<T, Interface> {
      private:
        // Data type
        TTCL_IMPORT_TYPE(T, data_type);

        /// Dendrogram type
        TTCL_IMPORT_TYPE(Interface, dendrogram_type);

      public:
        /// Constructor
        _hier_data_clusterer_referee(T* _ptr = 0, bool _owned = true) :
          cl::wr::_data_clusterer_referee<T, Interface>(_ptr, _owned) {
        }

        /// Perform the hier clustering
        virtual void
        hier_cluster_on(dendrogram_type& _dendrogram,
                        const cl::wr::data_w& _data,
                        const uint _n_clusters = 1) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          this->ptr_->hier_cluster_on(_dendrogram, *data, _n_clusters);
        }

        /// Perform the clustering
        virtual dendrogram_type
        hier_cluster(const cl::wr::data_w& _data,
                     const uint _n_clusters = 1) const {
          // Convert to data type
          const data_type* data = _data.get<data_type>();

          // Call
          return this->ptr_->hier_cluster(*data, _n_clusters);
        }
      };

      /// Base hierarchical data clusterer wrapper
      template <typename Interface>
      class _hier_data_clusterer_w :
        public cl::wr::_data_clusterer_w<Interface> {
      public:
        /// Dendrogram type
        TTCL_IMPORT_TYPE(Interface, dendrogram_type);

      protected:
        /// Empty constructor
        _hier_data_clusterer_w() :
          cl::wr::_data_clusterer_w<Interface>() {
        }

        /// Constructor
        _hier_data_clusterer_w(Interface* _ptr) :
          cl::wr::_data_clusterer_w<Interface>(_ptr) {
        }

      public:
        /// Perform the hier clustering
        void
        hier_cluster_on(dendrogram_type& _dendrogram,
                        const cl::wr::data_w& _data,
                        const uint _n_clusters = 1) const {
          // Call
          this->ptr_->hier_cluster_on(_dendrogram, _data, _n_clusters);
        }

        /// Perform the clustering
        dendrogram_type
        hier_cluster(const cl::wr::data_w& _data,
                     const uint _n_clusters = 1) const {
          // Call
          return this->ptr_->hier_cluster(_data, _n_clusters);
        }
      };

      /// Hierarchical data clusterer wrapper
      template <typename Choices = tu::default_choices>
      class hier_data_clusterer_w :
        public _hier_data_clusterer_w
          < _hier_data_clusterer_interface<Choices> > {
      private:
        /// Interface
        typedef _hier_data_clusterer_interface<Choices> interface;

        /// Base type
        typedef _hier_data_clusterer_w<interface> base_type;

      public:
        /// Empty Constructor
        hier_data_clusterer_w() :
          base_type() {
        }

        /// Constructor
        template <typename T>
        hier_data_clusterer_w(T* _value, bool _owned = true) :
          base_type(new _hier_data_clusterer_referee<T, interface>(_value,
                                                                   _owned)) {
        }

        /// Constructor
        template <typename T>
        hier_data_clusterer_w(T& _value, bool _owned = false) :
          base_type(new _hier_data_clusterer_referee<T, interface>(&_value,
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
