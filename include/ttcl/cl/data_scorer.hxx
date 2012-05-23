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

#ifndef TTCL_CL_DATA_SCORER_HXX
#define TTCL_CL_DATA_SCORER_HXX

/** @file
    Clustering - Data scorer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/global.hxx>
#include <ttcl/options.hxx>
#include <ttcl/cl/options.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/cl/soft_clustering.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/tu/tuning.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Data scorer
    /** @param Data The data type
     */
    template <typename Data,
              typename Choices = tu::default_choices>
    class data_scorer {
    public:
      /// Data type
      typedef Data data_type;

      /// Scores type
      typedef TTCL_TU_GET_CHOICE(Choices, score_container)
        scores_type;

      /// Score type
      TTCL_IMPORT_R_TYPE(scores_type, value_type, score_type);

    public:
      /// Destructor
      virtual
      ~data_scorer() {
      }

      /// Tune
      virtual void
      tune(const tu::tuning& /* _tuning */) {
      }

      /// Score
      /** @param _scores Scores
          @param _data   Data
      */
      virtual void
      score_on(scores_type& _scores,
               const data_type& _data) const = 0;

      /// Score
      /** Functional convenience version
          @param _data Data
      */
      virtual scores_type
      score(const data_type& _data) const {
        // Build and return
        scores_type ret(_data.size());
        score_on(ret, _data);
        return ret;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
