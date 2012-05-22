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

#ifndef TTCL_MF_COALESCE_HXX
#define TTCL_MF_COALESCE_HXX

/** @file
    Meta-functions - Coalesce
    @author Edgar Gonzalez i Pellicer
*/

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/void.hpp>
#include <boost/type_traits/is_same.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Meta-functions Namespace
  namespace mf {

    // Use placeholders
    using boost::mpl::placeholders::_1;

    /// Coalesce implementation
    template <typename Sequence>
    struct _coalesce_impl {
    private:
      // Find it
      typedef typename boost::mpl::find_if<
        Sequence,
        boost::mpl::not_<boost::is_same<_1, boost::mpl::void_> > >::type it;

    public:
      // Deref
      typedef typename boost::mpl::eval_if<
        boost::is_same<it, typename boost::mpl::end<Sequence>::type>,
        boost::mpl::identity<boost::mpl::void_>,
        boost::mpl::deref<it> >::type type;
    };

    /// Coalesce
    template <typename T1,
              typename T2,
              typename T3  = boost::mpl::void_,
              typename T4  = boost::mpl::void_,
              typename T5  = boost::mpl::void_,
              typename T6  = boost::mpl::void_,
              typename T7  = boost::mpl::void_,
              typename T8  = boost::mpl::void_,
              typename T9  = boost::mpl::void_,
              typename T10 = boost::mpl::void_>
    struct coalesce :
      public _coalesce_impl< boost::mpl::vector10<T1, T2, T3, T4, T5,
                                                  T6, T7, T8, T9, T10> > {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
