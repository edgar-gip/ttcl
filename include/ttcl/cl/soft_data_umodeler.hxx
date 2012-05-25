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

#ifndef TTCL_CL_SOFT_DATA_UMODELER_HXX
#define TTCL_CL_SOFT_DATA_UMODELER_HXX

/** @file
    Clustering - Soft data unsupervised modeler
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/data_umodeler.hxx>
#include <ttcl/cl/soft_data_model.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Soft data unsupervised modeler
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class soft_data_umodeler :
      public data_umodeler<Data, Choices> {
    public:
      /// Base type
      typedef data_umodeler<Data, Choices> base_type;

      /// Data type
      TTCL_IMPORT_TYPE(base_type, data_type);

      /// Hard clustering type
      TTCL_IMPORT_TYPE(base_type, hard_clustering_type);

      /// Soft clustering type
      TTCL_IMPORT_TYPE(base_type, soft_clustering_type);

      /// Model type
      typedef soft_data_model<data_type, Choices> model_type;

      /// Create a model
      virtual model_type*
      create_model(const data_type& _data) const = 0;

      /// Model
      /** @param _hard_clustering Target hard clustering
          @param _data Data
      */
      virtual model_type*
      hard_model_on(hard_clustering_type& _hard_clustering,
                    const data_type& _data) const {
        // Create soft clustering
        soft_clustering_type soft_clustering(_data.size(), 1 /* By default */);

        // Soft model on it
        model_type* mdl = soft_model_on(soft_clustering, _data);

        // Assign clustering
        _hard_clustering = soft_clustering;

        // Return the model
        return mdl;
      }

      /// Model
      /** @param _soft_clustering Target soft clustering
          @param _data Data
      */
      virtual model_type*
      soft_model_on(soft_clustering_type& _soft_clustering,
                    const data_type& _data) const = 0;

      /// Model
      /** @param _data Data
      */
      virtual model_type*
      model(const data_type& _data) const {
        // Cluster and return
        soft_clustering_type soft_clustering(_data.size(), 1 /* By default */);
        return soft_model_on(soft_clustering, _data);
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
