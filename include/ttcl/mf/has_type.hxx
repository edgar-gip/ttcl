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

#ifndef TTCL_MF_HAS_TYPE_HXX
#define TTCL_MF_HAS_TYPE_HXX

/** @file
    Metafunctions - Type checking trait definition
    @author Edgar Gonzalez i Pellicer
*/

#include <boost/type_traits/integral_constant.hpp>

/// Has type macro
#define TTCL_HAS_TYPE(trait_name, target_type)                  \
  template <typename T, typename Has = typename T::target_type> \
  struct _ ## trait_name {                                      \
    typedef void type;                                          \
  };                                                            \
  template <typename T, typename Has = void>                    \
  struct trait_name : public boost::false_type {                \
  };                                                            \
  template <typename T>                                         \
  struct trait_name<T, typename _ ## trait_name<T>::type> :     \
    public boost::true_type {                                   \
  }

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
