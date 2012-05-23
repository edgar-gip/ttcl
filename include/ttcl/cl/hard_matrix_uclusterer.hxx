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

#ifndef TTCL_CL_HARD_MATRIX_UCLUSTERER_HXX
#define TTCL_CL_HARD_MATRIX_UCLUSTERER_HXX

/** @file
    Clustering - Hard matrix unsupervised clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/hard_matrix_uclusterer.hxx>
#include <ttcl/co/array.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/tu/tuning.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hard matrix unsupervised clusterer
    /** @param Matrix The matrix type
     */
    template <typename Matrix = co::hollow_symmetric_matrix<double>,
              typename Choices = tu::default_choices>
    class hard_matrix_uclusterer :
      public matrix_uclusterer<Matrix, Choices> {
    public:
      /// Base type
      typedef matrix_uclusterer<Data, Choices> base_type;

      /// Matrix type
      TTCL_IMPORT_TYPE(base_type, matrix_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _in_distances Element pair-wise distances
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const matrix_type& _in_distances) const {
        // Assign
        _soft_clustering = this->hard_cluster(_in_distances);
      }

      /// Perform the soft clustering
      /** Convenience functional version
          @param _in_distances Element pair-wise distances
      */
      virtual soft_clustering_type
      soft_cluster(const matrix_type& _in_distances) const {
        // Build and return
        return soft_clustering_type(This->hard_cluster(_in_distances));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
