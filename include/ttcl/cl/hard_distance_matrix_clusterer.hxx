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

#ifndef TTCL_CL_HARD_DISTANCE_MATRIX_CLUSTERER_HXX
#define TTCL_CL_HARD_DISTANCE_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Hard distance matrix clusterer adapter
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/cl/hard_distance_clusterer.hxx>
#include <ttcl/fn/cross_apply.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hard distance matrix clusterer adapter
    template <typename Data,
              typename Distance,
              typename MatrixClusterer,
              typename Choices = tu::default_choices>
    class hard_distance_matrix_clusterer :
      public hard_distance_clusterer<Data, Distance, Choices> {
    public:
      /// Base type
      typedef distance_clusterer<Data, Distance, Choices> base_type;

      /// Data type
      typedef typename base_type::data_type data_type;

      /// Clustering type
      typedef typename base_type::hard_clustering_type hard_clustering_type;

      /// Distance type
      typedef typename base_type::distance_type distance_type;

      /// Matrix clusterer type
      typedef MatrixClusterer matrix_clusterer_type;

      /// Distance matrix type
      typedef typename matrix_clusterer_type::matrix_type matrix_type;

    protected:
      /// Base matrix clusterer
      matrix_clusterer_type matrix_clusterer_;

    public:
      /// Constructor
      hard_distance_matrix_clusterer(const distance_type& _distance,
                                     const matrix_clusterer_type&
                                       _matrix_clusterer) :
        base_type(_distance),
        matrix_clusterer_(_matrix_clusterer) {
      }

      /// Perform the clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data,
                      const uint _n_clusters = 1) const {
        // Create a distance matrix
        matrix_type distances =
          fn::cross_apply(_data, this->distance_);

        // Call
        matrix_clusterer_.hard_cluster_on(_hard_clustering,
                                          distances, _n_clusters);
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
