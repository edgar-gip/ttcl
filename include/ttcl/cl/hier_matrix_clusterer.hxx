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

#ifndef TTCL_CL_HIER_MATRIX_CLUSTERER_HXX
#define TTCL_CL_HIER_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Hierarchical matrix clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/dendrogram.hxx>
#include <ttcl/cl/hard_matrix_clusterer.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hierarchical matrix clusterer
    template <typename Matrix = co::hollow_symmetric_matrix<double>,
              typename Choices = tu::default_choices>
    class hier_matrix_clusterer :
      public cl::hard_matrix_clusterer<Matrix, Choices> {
    public:
      /// Base type
      typedef cl::hard_matrix_clusterer<Matrix, Choices> base_type;

      /// Distance matrix type
      TTCL_IMPORT_TYPE(base_type, matrix_type);

      /// Clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Value type
      typedef TTCL_TU_GET_CHOICE(Choices, dendrogram_value) value_type;

      /// Dendrogram type
      typedef dendrogram<value_type> dendrogram_type;

      /// Destructor
      virtual ~hier_matrix_clusterer() {
      }

      /// Perform the clustering
      /** @param _dendrogram Target dendrogram
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      void
      hier_cluster_on(dendrogram_type& _dendrogram,
                      const matrix_type& _in_distances,
                      const uint _n_clusters = 1) const {
        // Make a copy
        matrix_type distances = _in_distances;

        // Call the inplace version
        hier_cluster_inplace_on(_dendrogram, distances, _n_clusters);
      }

      /// Perform the clustering
      /** @param _dendrogram Target dendrogram
          @param _distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual void
      hier_cluster_inplace_on(dendrogram_type& _dendrogram,
                              matrix_type& _distances,
                              const uint _n_clusters = 1) const = 0;

      /// Perform the clustering
      /** Functional convenience version
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      dendrogram_type
      hier_cluster(const matrix_type& _in_distances,
                   const uint _n_clusters = 1) const {
        // Build and return
        dendrogram_type ret;
        hier_cluster_on(ret, _in_distances, _n_clusters);
        return ret;
      }

      /// Perform the clustering
      /** Functional convenience version
          @param _distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      dendrogram_type
      hier_cluster_inplace(matrix_type& _distances,
                           const uint _n_clusters = 1) const {
        // Build and return
        dendrogram_type ret;
        hier_cluster_inplace_on(ret, _distances, _n_clusters);
        return ret;
      }

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const matrix_type& _in_distances,
                      const uint _n_clusters) const {
        // Build the dendrogram
        dendrogram_type dendro;
        hier_cluster_on(dendro, _in_distances, _n_clusters);

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
