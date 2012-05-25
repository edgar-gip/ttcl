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

#ifndef TTCL_CL_HIER_DATA_CLUSTERER_HXX
#define TTCL_CL_HIER_DATA_CLUSTERER_HXX

/** @file
    Clustering - Hierarchical data clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/hard_data_clusterer.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/dendrogram.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hierarchical data clusterer
    template <typename Data,
              typename Choices = ttcl::tu::default_choices>
    class hier_data_clusterer :
      public cl::hard_data_clusterer<Data, Choices> {
    public:
      /// Base type
      typedef cl::hard_data_clusterer<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Value type
      typedef TTCL_TU_GET_CHOICE(Choices, dendrogram_value) value_type;

      /// Dendrogram type
      typedef dendrogram<value_type> dendrogram_type;

      /// Destructor
      virtual
      ~hier_data_clusterer() {
      }

      /// Perform the clustering
      /** @param _dendrogram Target dendrogram
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      hier_cluster_on(dendrogram_type& _dendrogram,
                      const data_type& _data,
                      const uint _n_clusters = 1) const = 0;

      /// Perform the clustering
      /** Functional convenience version
          @param _data Data
          @param _n_clusters Number of clusters
      */
      dendrogram_type
      hier_cluster(const data_type& _data,
                   const uint _n_clusters = 1) const {
        // Build and return
        dendrogram_type ret (_data.size());
        hier_cluster_on(ret, _data, _n_clusters);
        return ret;
      }

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data,
                      const uint _n_clusters) const {
        // Build the dendrogram
        dendrogram_type dendro (_data.size());
        hier_cluster_on(dendro, _data, _n_clusters);

        // Return it cut
        dendro.cut_on(_hard_clustering, _n_clusters);
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
