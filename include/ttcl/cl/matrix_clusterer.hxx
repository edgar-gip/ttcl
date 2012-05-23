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

#ifndef TTCL_CL_MATRIX_CLUSTERER_HXX
#define TTCL_CL_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Matrix clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/soft_clustering.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/tu/tuning.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Matrix clusterer
    /** @param Value The matrix value type
     */
    template <typename Matrix  = co::hollow_symmetric_matrix<double>,
              typename Choices = tu::default_choices>
    class matrix_clusterer {
    public:
      /// Distance matrix type
      typedef Matrix matrix_type;

      /// Value type
      TTCL_IMPORT_R_TYPE(matrix_type, element, value_type);

    private:
      /// Hard clustering container
      typedef TTCL_TU_GET_CHOICE(Choices, hard_clustering_container)
        hard_clustering_container_type;

    public:
      /// Clustering type
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

      /// Destructor
      virtual
      ~matrix_clusterer() {
      }

      /// Tune
      virtual void
      tune(const tu::tuning& /* _tuning */) {
      }

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const matrix_type& _in_distances,
                      const uint _n_clusters) const = 0;

      /// Perform the hard clustering
      /** Functional convenience version
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual hard_clustering_type
      hard_cluster(const matrix_type& _in_distances,
                   const uint _n_clusters) const {
        // Build and return
        hard_clustering_type ret(_in_distances.size(), _n_clusters);
        hard_cluster_on(ret, _in_distances, _n_clusters);
        return ret;
      }

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const matrix_type& _in_distances,
                      const uint _n_clusters) const = 0;

      /// Perform the soft clustering
      /** Functional convenience version
          @param _in_distances Element pair-wise distances
          @param _n_clusters Number of clusters
      */
      virtual soft_clustering_type
      soft_cluster(const matrix_type& _in_distances,
                   const uint _n_clusters) const {
        // Build and return
        soft_clustering_type ret(_in_distances.size(), _n_clusters);
        soft_cluster_on(ret, _in_distances, _n_clusters);
        return ret;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
