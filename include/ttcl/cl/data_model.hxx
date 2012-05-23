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

#ifndef TTCL_CL_DATA_MODEL_HXX
#define TTCL_CL_DATA_MODEL_HXX

/** @file
    Clustering - Data model
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/soft_clustering.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Data model
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class data_model {
    public:
      /// Data type
      typedef Data data_type;

    private:
      /// Hard clustering container
      typedef TTCL_TU_GET_CHOICE(Choices, hard_clustering_container)
        hard_clustering_container_type;

    public:
      /// Hard clustering type
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

    protected:
      /// Number of clusters
      uint clusters_;

    public:
      /// Constructor
      data_model(const uint _clusters = 0) :
        clusters_(_clusters) {
      }

      /// Destructor
      virtual
      ~data_model() {
      }

      /// @name Setters/Getters
      /// @{

      /// Number of clusters
      uint
      clusters() const {
        return clusters_;
      }

      /// Set the number of clusters
      void
      set_clusters(const uint _clusters) {
        clusters_ = _clusters;
        resized();
      }

      /// Number of free parameters
      virtual uint
      free_parameters() const = 0;

      /// @}

      /// Perform the hard clustering
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual void
      hard_cluster_on(hard_clustering_type& _hard_clustering,
                      const data_type& _data) const = 0;

      /// Perform the clustering
      /** Functional convenience version
          @param _data Data
      */
      hard_clustering_type
      hard_cluster(const data_type& _data) const {
        // Build and return
        hard_clustering_type ret(_data.size(), clusters_);
        hard_cluster_on(ret, _data);
        return ret;
      }

      /// Perform the soft clustering
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual void
      soft_cluster_on(soft_clustering_type& _soft_clustering,
                      const data_type& _data) const = 0;

      /// Perform the soft clustering
      /** Convenience functional version
          @param _data Data
      */
      soft_clustering_type
      soft_cluster(const data_type& _data) const {
        // Build and return
        soft_clustering_type ret(_data.size(), this->clusters_);
        soft_cluster_on(ret, _data);
        return ret;
      }

    protected:
      /// Resized
      /** Empty in this base class
       */
      virtual void
      resized() {
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
