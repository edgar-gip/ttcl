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

#ifndef TTCL_CO_DEFAULT_PAIR_HXX
#define TTCL_CO_DEFAULT_PAIR_HXX

/** @file
    Containers - Default Pair
    @author Edgar Gonzàlez i Pellicer
*/

#include <utility>

#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Pair with default first element
    template <typename T1, typename T2, int value>
    class default_pair_first :
      public std::pair<T1, T2> {
    public:
      /// Base type
      typedef std::pair<T1, T2> base_type;

      /// First type
      TTCL_IMPORT_TYPE(base_type, first_type);

      /// Second type
      TTCL_IMPORT_TYPE(base_type, second_type);

      /// Default value
      static const first_type default_value = value;

    public:
      /// Constructor
      default_pair_first(const second_type& _second = second_type()) :
        base_type(value, _second) {
      }

      /// Full constructor
      default_pair_first(const first_type& _first,
                         const second_type& _second) :
        base_type(_first, _second) {
      }
    };

    /// Pair with default second element
    template <typename T1, typename T2, int value>
    class default_pair_second :
      public std::pair<T1, T2> {
    public:
      /// Base type
      typedef std::pair<T1, T2> base_type;

      /// First type
      TTCL_IMPORT_TYPE(base_type, first_type);

      /// Second type
      TTCL_IMPORT_TYPE(base_type, second_type);

      /// Default value
      static const second_type default_value = second_type(value);

    public:
      /// Constructor
      default_pair_second(const first_type& _first = first_type(),
                          const second_type& _second = second_type(value)) :
        base_type(_first, _second) {
      }
    };
  }
}

// Static vars
#ifdef TTCL_DEBUG
#define TTCL_CO_DEFAULT_PAIR_STATIC                                     \
  template <typename T1, typename T2, int value>                        \
  const typename std::pair<T1,T2>::first_type                           \
  ttcl::co::default_pair_first<T1,T2,value>::default_value;             \
  template <typename T1, typename T2, int value>                        \
  const typename std::pair<T1,T2>::second_type                          \
  ttcl::co::default_pair_second<T1,T2,value>::default_value
#else
#define TTCL_CO_DEFAULT_PAIR_STATIC
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
