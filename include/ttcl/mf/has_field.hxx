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

#ifndef TTCL_MF_HAS_FIELD_HXX
#define TTCL_MF_HAS_FIELD_HXX

/** @file
    Metafunctions - Field checking trait definition
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/type_traits/integral_constant.hpp>

#include <ttcl/mf/voidify.hxx>

/// Check field
#define TTCL_HAS_FIELD(trait_name, field)                       \
  template <typename T,                                         \
            typename Has = void>                                \
  struct trait_name : public boost::false_type {                \
  };                                                            \
  template <typename T>                                         \
  struct trait_name                                             \
    <T, typename ttcl::ut::voidify<typeof(&T::field)>::type> :  \
    public boost::true_type {                                   \
  }

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
