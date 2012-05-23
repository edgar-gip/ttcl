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

#ifndef TTCL_CL_HARD_MATRIX_CLUSTERER_HXX
#define TTCL_CL_HARD_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Hard matrix clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/matrix_clusterer.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hard matrix clusterer
    /** @param Value The matrix value type
     */
    template <typename Matrix = co::hollow_symmetric_matrix<double>,
              typename Choices = tu::default_choices>
    class hard_matrix_clusterer :
      public matrix_clusterer<Matrix, Choices> {
    public:
      /// Base type
      typedef matrix_clusterer<Matrix, Choices> base_type;

      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Distance matrix type
      TTCL_IMPORT_TYPE(base_type, matrix_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const matrix_type& _in_distances,
                      const uint _n_clusters) const {
        // Assign
        _soft_clustering = this->hard_cluster(_in_distances, _n_clusters);
      }

      /// Perform the soft clustering
      /** Functional convenience version
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual soft_clustering_type
      soft_cluster(const matrix_type& _in_distances,
                   const uint _n_clusters) const {
        // Build and return
        return soft_clustering_type(this->hard_cluster(_in_distances,
                                                       _n_clusters));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
