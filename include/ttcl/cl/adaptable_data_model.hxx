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

#ifndef TTCL_CL_ADAPTABLE_DATA_MODEL_HXX
#define TTCL_CL_ADAPTABLE_DATA_MODEL_HXX

/** @file
    Clustering - Adaptable data model
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/data_model.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Adaptable data model
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class adaptable_data_model :
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

    protected:
      /// Inner softness
      softness_enum inner_softness_;

    public:
      /// Constructor
      adaptable_data_model(const uint _clusters = 0,
                           const softness_enum _inner_softness =
                             DEFAULT_SOFTNESS) :
        base_type(_clusters), inner_softness_(_inner_softness) {
      }

      /// @name Getters
      /// @{

      /// Inner softness
      softness_enum inner_softness() const {
        return inner_softness_;
      }

      /// @}

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data) const {
        // According to softness
        if (inner_softness_ == SOFTNESS_SOFT) {
          // Create a soft clustering, cluster on it, and convert back
          soft_clustering_type soft(_hard_clustering.size(), this->clusters_);
          _soft_cluster_on(soft, _data);
          _hard_clustering = soft;
        }
        else { // inner_softness_ == SOFTNESS_HARD
          // Cluster on it
          _hard_cluster_on(_hard_clustering, _data);
        }
      }

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const data_type& _data) const {
        // According to softness
        if (inner_softness_ == SOFTNESS_SOFT) {
          // Cluster on it
          _soft_cluster_on(_soft_clustering, _data);
        }
        else { // inner_softness_ == SOFTNESS_HARD
          // Create a hard clustering, cluster on it, and convert back
          hard_clustering_type hard(_soft_clustering.size(), this->clusters_);
          _hard_cluster_on(hard, _data);
          _soft_clustering = hard;
        }
      }

    protected:
      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual void
      _hard_cluster_on(hard_clustering_type& _hard_clustering,
                       const data_type& _data) const = 0;

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual void
      _soft_cluster_on(soft_clustering_type& _soft_clustering,
                       const data_type& _data) const = 0;
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
