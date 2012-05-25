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

#ifndef TTCL_CL_DATA_MODELER_HXX
#define TTCL_CL_DATA_MODELER_HXX

/** @file
    Clustering - Data modeler
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/data_clusterer.hxx>
#include <ttcl/cl/data_model.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Data modeler
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class data_modeler :
      public data_clusterer<Data, Choices> {
    public:
      /// Base type
      typedef data_clusterer<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Model type
      typedef data_model<data_type, Choices> model_type;

      /// Create a model
      virtual model_type*
      create_model(const data_type& _data,
                   const uint _n_clusters) const = 0;

      /// Model
      /** @param _hard_clustering Target hard clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual model_type*
      hard_model_on(hard_clustering_type& _hard_clustering,
                    const data_type& _data,
                    const uint _n_clusters) const = 0;

      /// Model
      /** @param _soft_clustering Target soft clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual model_type*
      soft_model_on(soft_clustering_type& _soft_clustering,
                    const data_type& _data,
                    const uint _n_clusters) const = 0;

      /// Model
      /** @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual model_type*
      model(const data_type& _data,
            const uint _n_clusters) const = 0;

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data,
                      const uint _n_clusters) const {
        // Cluster using a model, and ignore it
        model_type* ret = hard_model_on(_hard_clustering, _data, _n_clusters);
        delete ret;
      }

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const data_type& _data,
                      const uint _n_clusters) const {
        // Cluster using a model, and ignore it
        model_type* ret = soft_model_on(_soft_clustering, _data, _n_clusters);
        delete ret;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
