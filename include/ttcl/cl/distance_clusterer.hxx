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

#ifndef TTCL_CL_DISTANCE_CLUSTERER
#define TTCL_CL_DISTANCE_CLUSTERER

/** @file
    Clustering - Distance clusterer mixin
    @author Edgar Gonzalez i Pellicer
*/

#include <boost/mpl/placeholders.hpp>

#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Distance clusterer mixin
    /** @param Data The data type
        @param Distance The distance type
    */
    template <typename Base,
              typename Distance>
    class distance_clusterer :
      public Base {
    public:
      /// Base type
      typedef Base base_type;

      /// Distance type
      typedef Distance distance_type;

    protected:
      /// Distance
      distance_type distance_;

    public:
      /// Constructor
      distance_clusterer(const distance_type& _distance) :
        base_type(), distance_(_distance) {
      }

      /// Distance
      const distance_type&
      distance() const {
        return distance_;
      }

      /// Set distance
      void
      set_distance(const distance_type& _distance) {
        distance_ = _distance;
      }
    };

    /// Hard distance clusterer constructor
    struct hard_distance_clusterer_c {
      template <typename Data,
                typename Distance,
                typename Choices = ttcl::tu::default_choices>
      struct apply {
        typedef distance_clusterer<hard_data_clusterer<Data, Choices>,
                                   Distance> type;
      };
    };

    /// Soft distance clusterer constructor
    struct soft_distance_clusterer_c {
      template <typename Data,
                typename Distance,
                typename Choices = ttcl::tu::default_choices>
      struct apply {
        typedef distance_clusterer<soft_data_clusterer<Data, Choices>,
                                   Distance> type;
      };
    };

#ifdef TTCL_CXX0X_TEMPLATE_ALIASES
    /// Hard distance clusterer
    template <typename Data, typename Distance,
              typename Choices = ttcl::tu::choices>
    using hard_distance_clusterer =
      distance_clusterer<hard_data_clusterer<Data, Choices>, Distance>;

    /// Soft distance clusterer
    template <typename Data, typename Distance,
              typename Choices = ttcl::tu::choices>
    using soft_distance_clusterer =
      distance_clusterer<soft_data_clusterer<Data, Choices>, Distance>;
#endif
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
