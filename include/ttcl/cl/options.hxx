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

#ifndef TTCL_CL_OPTIONS_HXX
#define TTCL_CL_OPTIONS_HXX

/** @file
    Clustering - Options
    @author Edgar Gonzàlez i Pellicer
*/

#include <vector>

#include <boost/mpl/placeholders.hpp>

#include <ttcl/co/matrix.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/tu/choices.hxx>
#include <ttcl/tu/tuning.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Softness
    enum softness_enum { SOFTNESS_HARD, SOFTNESS_SOFT,
                         DEFAULT_SOFTNESS = SOFTNESS_SOFT };

    /// Distance matrix constructor
    /** Choice
     */
    TTCL_TU_CHOICE(distance_matrix_constructor,
                   co::hollow_symmetric_matrix<boost::mpl::_1>);

    /// Hard Clustering Container
    /** Choice
     */
    TTCL_TU_CHOICE(hard_clustering_container, std::vector<int>);

    /// Soft Clustering Container
    /** Choice
     */
    TTCL_TU_CHOICE(soft_clustering_container, co::matrix<double>);

    /// Score container
    /** Choice
     */
    TTCL_TU_CHOICE(score_container, std::vector<double>);

    /// Inner softness
    /** Option
     */
    TTCL_TU_OPTION(softness_enum, inner_softness, DEFAULT_SOFTNESS);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
