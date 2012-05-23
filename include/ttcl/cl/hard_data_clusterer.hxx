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

#ifndef TTCL_CL_HARD_DATA_CLUSTERER_HXX
#define TTCL_CL_HARD_DATA_CLUSTERER_HXX

/** @file
    Clustering - Hard data clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/data_clusterer.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hard data clusterer
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class hard_data_clusterer :
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

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const data_type& _data,
                      const uint _n_clusters) const {
        // Assign
        _soft_clustering = this->hard_cluster(_data, _n_clusters);
      }

      /// Perform the soft clustering
      /** Convenience functional version
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual soft_clustering_type
      soft_cluster(const data_type& _data,
                   const uint _n_clusters) const {
        // Build and return
        return soft_clustering_type(this->hard_cluster(_data, _n_clusters));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
