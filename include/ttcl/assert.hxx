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

#ifndef TTCL_ASSERT_HXX
#define TTCL_ASSERT_HXX

/** @file
    Assertions
    @author Edgar Gonzàlez i Pellicer
*/

// Conditional includes
#ifdef TTCL_CHECK_ASSERTS
# ifdef TTCL_ASSERT_WARN
#  include <ttcl/lg/logger.hxx>
# else
#  include <ttcl/exception.hxx>
# endif
#endif

/// Failed
#ifdef TTCL_CHECK_ASSERTS
# ifdef TTCL_ASSERT_WARN
#  define TTCL_FAILED(...)                      \
  TTCL_LOGGER().warn(__VA_ARGS__);
# else
#  define TTCL_FAILED(...)                      \
  TTCL_FIRE(__VA_ARGS__);
# endif
#endif

/// General assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT(assertion)                         \
  if (not (assertion))                                  \
    TTCL_FAILED("Assertion '%s' failed", #assertion);
#else
# define TTCL_ASSERT(assertion)
#endif

/// Equal assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_EQ(expression, value)                              \
  if ((expression) != (value))                                          \
    TTCL_FAILED("Assertion '%s == %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_EQ(expression, value)
#endif

/// Not equal assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_NE(expression, value)                              \
  if ((expression) == (value))                                          \
    TTCL_FAILED("Assertion '%s != %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_NE(expression, value)
#endif

/// Less than assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_LT(expression, value)                              \
  if ((expression) >= (value))                                          \
    TTCL_FAILED("Assertion '%s < %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_LT(expression, value)
#endif

/// Less than or equal assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_LE(expression, value)                              \
  if ((expression) > (value))                                           \
    TTCL_FAILED("Assertion '%s <= %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_LE(expression, value)
#endif

/// Greater than assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_GT(expression, value)                              \
  if ((expression) <= (value))                                          \
    TTCL_FAILED("Assertion '%s > %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_GT(expression, value)
#endif

/// Greater than or equal assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_GE(expression, value)                              \
  if ((expression) < (value))                                           \
    TTCL_FAILED("Assertion '%s >= %s' failed", #expression, #value);
#else
# define TTCL_ASSERT_GE(expression, value)
#endif

/// Range assertion
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_RANGE(lower, expression, upper)                    \
  if ((expression) < (lower) or (expression) >= (upper))                \
    TTCL_FAILED("Assertion '%s <= %s < %s' failed",                     \
                #lower, #expression, #upper);
#else
# define TTCL_ASSERT_RANGE(lower, expression, upper)
#endif

/// Assert-only parameter
#ifdef TTCL_CHECK_ASSERTS
# define TTCL_ASSERT_PARAM(_param) _param
#else
# define TTCL_ASSERT_PARAM(_param)
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
