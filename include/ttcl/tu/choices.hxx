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

#ifndef TTCL_TU_CHOICES_HXX
#define TTCL_TU_CHOICES_HXX

/** @file
    Tuning - Choices
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/mpl/apply.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/void.hpp>
#include <boost/type_traits/is_same.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Tuning Namespace
  namespace tu {

    /// Default choices
    typedef boost::mpl::map0<> default_choices;
  }
}

/// Define a choice
#define TTCL_TU_CHOICE(name, deflt_type) \
  struct name { \
    typedef deflt_type default_type; \
  };

/// Add a choice
#define TTCL_TU_ADD_CHOICE(choices, name, typ) \
  typename boost::mpl::insert<choices, boost::mpl::pair<name, typ> >::type

// Get a type
#define TTCL_TU_GET_CHOICE(choices, name) \
  typename boost::mpl::if_< \
    boost::is_same<typename boost::mpl::at<choices, name>::type, \
                   boost::mpl::void_>, \
    name::default_type, \
    typename boost::mpl::at<choices, name>::type \
  >::type

// Apply a choice
#define TTCL_TU_APPLY_CHOICE(choices, name, ...) \
  typename boost::mpl::apply< \
    TTCL_TU_GET_CHOICE(choices, name), __VA_ARGS__>::type

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
