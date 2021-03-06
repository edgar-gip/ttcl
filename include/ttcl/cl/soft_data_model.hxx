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

#ifndef TTCL_CL_SOFT_DATA_MODEL_HXX
#define TTCL_CL_SOFT_DATA_MODEL_HXX

/** @file
    Clustering - Soft data model
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/data_model.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Soft data model
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class soft_data_model :
      public data_model<Data, Choices> {
    public:
      /// Base type
      typedef data_model<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

    public:
      /// Constructor
      soft_data_model(const uint _clusters = 0) :
        base_type(_clusters) {
      }

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data) const {
        // Cluster, assign
        soft_clustering_type soft_clustering(_data.size(), this->clusters_);
        this->soft_cluster_on(soft_clustering, _data);
        _hard_clustering = soft_clustering;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
