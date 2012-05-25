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

#ifndef TTCL_OPTIONS_HXX
#define TTCL_OPTIONS_HXX

/** @file
    Global options
    @author Edgar Gonzàlez i Pellicer
*/

#include <memory>

#include <boost/mpl/placeholders.hpp>

#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// @addtogroup Choices
  /// @{

  /// Real type
  TTCL_TU_CHOICE(real_type, double);

  /// Parameter allocator constructor
  /** Choice
   */
  TTCL_TU_CHOICE(allocator_c, std::allocator<boost::mpl::_1>);

  /// @}
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
