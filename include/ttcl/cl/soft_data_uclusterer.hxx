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

#ifndef TTCL_CL_SOFT_DATA_UCLUSTERER_HXX
#define TTCL_CL_SOFT_DATA_UCLUSTERER_HXX

/** @file
    Clustering - Soft data unsupervised clusterer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/data_uclusterer.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Soft data unsupervised clusterer
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class soft_data_uclusterer :
      public data_uclusterer<Data, Choices> {
    public:
      /// Base type
      typedef data_uclusterer<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data) const {
        // Assign
        _hard_clustering = this->soft_cluster(_data);
      }

      /// Perform the hard clustering
      /** Convenience functional version
          @param _data Data
      */
      virtual hard_clustering_type
      hard_cluster(const data_type& _data) const {
        // Build and return
        return hard_clustering_type(this->soft_cluster(_data));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
