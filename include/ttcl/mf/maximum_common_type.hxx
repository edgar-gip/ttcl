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

#ifndef TTCL_MF_MAXIMUM_COMMON_TYPE_HXX
#define TTCL_MF_MAXIMUM_COMMON_TYPE_HXX

/** @file
    Meta-functions - Maximum common type
    @author Edgar Gonzalez i Pellicer
*/

#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/promote.hpp>
#include <boost/utility/enable_if.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Meta-functions Namespace
  namespace mf {

    /// Maximum common type
    template <typename First,
              typename Second,
              typename Enable = void>
    struct maximum_common_type;


    /// Maximum common type
    /** Specialization for a single type
     */
    template <typename T>
    struct maximum_common_type<T, T> :
      public boost::mpl::identity<T> {
    };


    /// Maximum common type
    /** Specialization for promotable types
     */
    template <typename T1, typename T2>
    struct maximum_common_type<
      T1, T2,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::mpl::not_<boost::is_same<T1, T2> >,
          boost::is_same<
            typename boost::promote<T1>::type,
            typename boost::promote<T2>::type> > >::type> :
      public boost::mpl::identity<typename boost::promote<T1>::type> {
    };


    /// Maximum common type
    /** Specialization for a integer/floating_point conversions
     */
    template <typename T1, typename T2>
    struct maximum_common_type<
      T1, T2,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::mpl::not_<boost::is_same<T1, T2> >,
          boost::is_integral<T1>,
          boost::is_floating_point<T2> > >::type> :
      public boost::mpl::identity<T2> {
    };


    /// Maximum common type
    /** Specialization for a integer/floating_point conversions
     */
    template <typename T1, typename T2>
    struct maximum_common_type<
      T1, T2,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::mpl::not_<boost::is_same<T1, T2> >,
          boost::is_floating_point<T1>,
          boost::is_integral<T2> > >::type> :
      public boost::mpl::identity<T1> {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
