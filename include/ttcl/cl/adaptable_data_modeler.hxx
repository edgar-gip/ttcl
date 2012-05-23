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

#ifndef TTCL_CL_ADAPTABLE_DATA_MODELER_HXX
#define TTCL_CL_ADAPTABLE_DATA_MODELER_HXX

/** @file
    Clustering - Adaptable data modeler
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/data_modeler.hxx>
#include <ttcl/cl/hard_data_model.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Adaptable data modeler
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class adaptable_data_modeler :
      public data_modeler<Data, Choices> {
    public:
      /// Base type
      typedef data_modeler<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Model type
      TTCL_IMPORT_TYPE(base_type, model_type);

    protected:
      /// Inner softness
      softness_enum inner_softness_;

    public:
      /// Constructor
      adaptable_data_modeler() :
        base_type(),
        inner_softness_(DEFAULT_SOFTNESS) {
      }

      /// Tune
      virtual void
      tune(const tu::tuning& _tuning) {
        // Call parent version
        base_type::tune(_tuning);

        // Extract the options
        inner_softness_ = _tuning.get<inner_softness>();
      }

      /// Model
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual model_type*
      hard_model_on(hard_clustering_type& _hard_clustering,
                    const data_type& _data,
                    const uint _n_clusters) const {
        // Return
        model_type* ret;

        // According to softness
        if (inner_softness_ == SOFTNESS_SOFT) {
          // Create a soft clustering, model on it, and convert back
          soft_clustering_type soft(_hard_clustering.size(), _n_clusters);
          ret = _soft_model_on(soft, _data, _n_clusters);
          _hard_clustering = soft;
        }
        else { // inner_softness_ == SOFTNESS_HARD
          // Model on it
          ret = _hard_model_on(_hard_clustering, _data, _n_clusters);
        }

        // Return the result
        return ret;
      }

      /// Model
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual model_type*
      soft_model_on(soft_clustering_type& _soft_clustering,
                    const data_type& _data,
                    const uint _n_clusters) const {
        // Return
        model_type* ret;

        // According to softness
        if (inner_softness_ == SOFTNESS_SOFT) {
          // Model on it
          ret = _soft_model_on(_soft_clustering, _data, _n_clusters);
        }
        else { // inner_softness_ == SOFTNESS_HARD
          // Create a hard clustering, model on it, and convert back
          hard_clustering_type hard(_soft_clustering.size(), _n_clusters);
          ret = _hard_model_on(hard, _data, _n_clusters);
          _soft_clustering = hard;
        }

        // Return the result
        return ret;
      }

      /// Model
      /** @param _data Data
          @param _n_clusters Number of clusters
      */
      virtual model_type*
      model(const data_type& _data,
            const uint _n_clusters) const {
        // Return
        model_type* ret;

        // According to softness
        if (inner_softness_ == SOFTNESS_SOFT) {
          // Create a soft clustering, and model on it
          soft_clustering_type soft(_data.size(), _n_clusters);
          ret = _soft_model_on(soft, _data, _n_clusters);
        }
        else { // inner_softness_ == SOFTNESS_HARD
          // Create a hard clustering, and model on it
          hard_clustering_type hard(_data.size(), _n_clusters);
          ret = _hard_model_on(hard, _data, _n_clusters);
        }

        // Return the result
        return ret;
      }

    protected:
      /// Hard Modelling
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual model_type*
      _hard_model_on(hard_clustering_type& _hard_clustering,
                     const data_type& _data,
                     const uint _n_clusters) const = 0;

      /// Soft Modelling
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual model_type*
      _soft_model_on(soft_clustering_type& _soft_clustering,
                     const data_type& _data,
                     const uint _n_clusters) const = 0;
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
