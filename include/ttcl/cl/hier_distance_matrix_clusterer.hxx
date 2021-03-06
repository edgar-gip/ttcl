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

#ifndef TTCL_CL_HIER_DISTANCE_MATRIX_CLUSTERER_HXX
#define TTCL_CL_HIER_DISTANCE_MATRIX_CLUSTERER_HXX

/** @file
    Clustering - Hierarchical distance matrix clusterer adapter
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <ttcl/global.hxx>
#include <ttcl/cl/distance_clusterer.hxx>
#include <ttcl/fn/cross_apply.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hiearchical distance matrix clusterer adapter
    template <typename Data,
              typename Dist,
              typename MatrixClusterer,
              typename Choices = tu::default_choices>
    class hier_distance_matrix_clusterer :
      public boost::mpl::apply<
        hier_distance_clusterer_c, Data, Dist, Choices>::type {
    public:
      /// Base type
      typedef boost::mpl::apply<
        hier_distance_clusterer_c, Data, Dist, Choices>::type base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Dendrogram type
      TTCL_IMPORT_TYPE(base_type, dendrogram_type);

      /// Distance type
      TTCL_IMPORT_TYPE(base_type, distance_type);

      /// Matrix clusterer type
      typedef MatrixClusterer matrix_clusterer_type;

      /// Distance matrix type
      TTCL_IMPORT_TYPE(matrix_clusterer_type, matrix_type);

    private:
      // Check
      BOOST_MPL_ASSERT
        (( boost::is_same<dendrogram_type,
                          typename matrix_clusterer_type::dendrogram_type> ));

    protected:
      /// Base matrix clusterer
      matrix_clusterer_type matrix_clusterer_;

    public:
      /// Constructor
      hier_distance_matrix_clusterer(const distance_type& _distance,
                                     const matrix_clusterer_type&
                                       _matrix_clusterer) :
        base_type(_distance), matrix_clusterer_(_matrix_clusterer) {
      }

      /// Perform the clustering
      /** @param _dendrogram Target dendrogram
          @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual void
      hier_cluster_on(dendrogram_type& _dendrogram,
                      const data_type& _data,
                      const uint _n_clusters = 1) const {
        // Create a distance matrix
        matrix_type distances = fn::cross_apply(_data, this->distance_);

        // Call
        matrix_clusterer_.hier_cluster_inplace_on(_dendrogram,
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
