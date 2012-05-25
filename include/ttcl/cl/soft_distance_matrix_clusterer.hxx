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

#ifndef TTCL_CL_SOFT_DISTANCE_MATRIX_CLUSTERER_HXX
#define TTCL_CL_SOFT_DISTANCE_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Soft distance matrix clusterer adapter
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/mpl/apply.hpp>

#include <ttcl/global.hxx>
#include <ttcl/cl/distance_clusterer.hxx>
#include <ttcl/fn/cross_apply.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Soft distance matrix clusterer adapter
    template <typename Data,
              typename Distance,
              typename MatrixClusterer,
              typename Choices = tu::default_choices>
    class soft_distance_matrix_clusterer :
      public boost::mpl::apply<
        soft_distance_clusterer_c, Data, Distance, Choices>::type {
    public:
      /// Base type
      typedef boost::mpl::apply<
        soft_distance_clusterer_c, Data, Distance, Choices>::type base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Distance type
      TTCL_IMPORT_TYPE(base_type, distance_type);

      /// Matrix clusterer type
      typedef MatrixClusterer matrix_clusterer_type;

      /// Distance matrix type
      TTCL_IMPORT_TYPE(matrix_clusterer_type, matrix_type);

    protected:
      /// Base matrix clusterer
      matrix_clusterer_type matrix_clusterer_;

    public:
      /// Constructor
      soft_distance_matrix_clusterer(const distance_type& _distance,
                                     const matrix_clusterer_type&
                                       _matrix_clusterer) :
        base_type(_distance),
        matrix_clusterer_(_matrix_clusterer) {
      }

      /// Perform the clustering
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const data_type& _data,
                      const uint _n_clusters = 1) const {
        // Create a distance matrix
        matrix_type distances =
          fn::cross_apply(_data, this->distance_);

        // Call
        matrix_clusterer_.soft_cluster_on(_soft_clustering,
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
