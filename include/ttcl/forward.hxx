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

#ifndef TTCL_FORWARD_HXX
#define TTCL_FORWARD_HXX

/** @file
    Forwarding helpers
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <ttcl/c++11.hxx>

/// Forwarded arguments
#ifndef TTCL_FORWARD_MAX_ARGS
#define TTCL_FORWARD_MAX_ARGS 6
#endif

/// Forwarded template parameter
#define TTCL_FORWARD_TPARAM(z, i, _) \
  BOOST_PP_COMMA_IF(i) typename T ## i

#ifdef TTCL_CXX11_RVALUES

/// Forwarded parameter
#define TTCL_FORWARD_PARAM(z, i, _) \
  BOOST_PP_COMMA_IF(i) T ## i && _p ## i

/// Forwarded argument
#define TTCL_FORWARD_ARG(z, i, _) \
  BOOST_PP_COMMA_IF(i) std::forward<T ## i>(_p ## i)

#else

/// Forwarded parameter
#define TTCL_FORWARD_PARAM(z, i, _) \
  BOOST_PP_COMMA_IF(i) const T ## i & _p ## i

/// Forwarded argument
#define TTCL_FORWARD_ARG(z, i, _) \
  BOOST_PP_COMMA_IF(i) _p ## i

#endif

/// Forwarded template signature
#define _TTCL_FORWARD_TEMPLATE(i) \
  template <BOOST_PP_REPEAT(i, TTCL_FORWARD_TPARAM, _)>
#define _TTCL_FORWARD_TEMPLATE_EMPTY(i)
#define TTCL_FORWARD_TEMPLATE(i)                                        \
  BOOST_PP_IF(i, _TTCL_FORWARD_TEMPLATE, _TTCL_FORWARD_TEMPLATE_EMPTY)(i)

/// Forwarded parameter signature
#define TTCL_FORWARD_PARAMETERS(i) \
  BOOST_PP_REPEAT(i, TTCL_FORWARD_PARAM, _)

/// Forwarded call
#define TTCL_FORWARD_CALL(i) \
  BOOST_PP_REPEAT(i, TTCL_FORWARD_ARG, _)

/// Forward
#define TTCL_FORWARD(macro) \
  BOOST_PP_REPEAT(BOOST_PP_INC(TTCL_FORWARD_MAX_ARGS), macro, _)

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
