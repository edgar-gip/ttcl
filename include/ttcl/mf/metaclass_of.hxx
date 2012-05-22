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

#ifndef TTCL_MF_METACLASS_OF_HXX
#define TTCL_MF_METACLASS_OF_HXX

/** @file
    Meta-functions - Metaclass of
    @author Edgar Gonzalez i Pellicer
*/

#include <boost/mpl/placeholders.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Meta-functions Namespace
  namespace mf {

    /// Metaclass of
    template <typename T>
    struct metaclass_of {
      /// Result type
      typedef T type;
    };

    /// Metaclass of
    /** Specialization for 1-argument templates
     */
    template <template <typename> class T,
              typename T1>
    struct metaclass_of< T<T1> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1> type;
    };

    /// Metaclass of
    /** Specialization for 2-argument templates
     */
    template <template <typename, typename> class T,
              typename T1, typename T2>
    struct metaclass_of< T<T1, T2> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2> type;
    };

    /// Metaclass of
    /** Specialization for 3-argument templates
     */
    template <template <typename, typename, typename> class T,
              typename T1, typename T2, typename T3>
    struct metaclass_of< T<T1, T2, T3> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2,
                boost::mpl::placeholders::_3> type;
    };

    /// Metaclass of
    /** Specialization for 4-argument templates
     */
    template <template <typename, typename, typename, typename> class T,
              typename T1, typename T2, typename T3, typename T4>
    struct metaclass_of< T<T1, T2, T3, T4> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2,
                boost::mpl::placeholders::_3,
                boost::mpl::placeholders::_4> type;
    };

    /// Metaclass of
    /** Specialization for 5-argument templates
     */
    template <template <typename, typename, typename, typename,
                        typename> class T,
              typename T1, typename T2, typename T3, typename T4, typename T5>
    struct metaclass_of< T<T1, T2, T3, T4, T5> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2,
                boost::mpl::placeholders::_3,
                boost::mpl::placeholders::_4,
                boost::mpl::placeholders::_5> type;
    };


    /// Metaclass of
    /** Specialization for 6-argument templates
     */
    template <template <typename, typename, typename, typename,
                        typename, typename> class T,
              typename T1, typename T2, typename T3, typename T4, typename T5,
              typename T6>
    struct metaclass_of< T<T1, T2, T3, T4, T5, T6> > {
      /// Result type
      typedef T<boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2,
                boost::mpl::placeholders::_3,
                boost::mpl::placeholders::_4,
                boost::mpl::placeholders::_5,
                boost::mpl::placeholders::_6> type;
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
