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

#ifndef TTCL_DT_TRAITS_HXX
#define TTCL_DT_TRAITS_HXX

// TTCL: The Template Clustering Library

/** @file
    Data - Traits
    @author Edgar Gonzalez i Pellicer
*/

#include <cstddef>
#include <utility>

#include <boost/mpl/not.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/utility/enable_if.hpp>

#include <ttcl/co/fake_pair.hxx>
#include <ttcl/ut/traits.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Data Namespace
  namespace dt {

    /// Has value type
    TTCL_HAS_TYPE(has_value_type, value_type);


    /// Is sparse item
    template <typename T>
    struct is_sparse_item :
      public boost::false_type {
    };

    /// Is sparse item
    /** Specialization for std::pair
     */
    template <typename T1, typename T2>
    struct is_sparse_item< std::pair<T1, T2> > :
      public boost::true_type {
    };

    /// Is sparse item
    /** Specialization for ttcl::co::fake_pair_second
     */
    template <typename T1, typename T2, int V2>
    struct is_sparse_item< ttcl::co::fake_pair_second<T1, T2, V2> > :
      public boost::true_type {
    };


    /// Is dense item
    template <typename T>
    struct is_dense_item :
      public boost::mpl::not_< is_sparse_item<T> > {
    };


    /// Is sparse sample
    template <typename T, typename Enable = void>
    struct is_sparse_sample :
      public boost::false_type {
    };

    /// Is sparse sample
    /** Specialization for containers of sparse items
     */
    template <typename T>
    struct is_sparse_sample
      <T, typename boost::enable_if< has_value_type<T> >::type> :
      public is_sparse_item<typename T::value_type> {
    };


    /// Is dense sample
    template <typename T>
    struct is_dense_sample :
      public boost::mpl::not_< is_sparse_sample<T> > {
    };


    /// Is sparse container
    template <typename T, typename Enable = void>
    struct is_sparse_container :
      public boost::false_type {
    };

    /// Is sparse container
    /** Specialization for containers of sparse samples
     */
    template <typename T>
    struct is_sparse_container
      <T, typename boost::enable_if< has_value_type<T> >::type> :
      public is_sparse_sample<typename T::value_type> {
    };


    /// Is dense container
    template <typename T>
    struct is_dense_container :
      public boost::mpl::not_< is_sparse_container<T> > {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
