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

#ifndef TTCL_CO_FAKE_PAIR_HXX
#define TTCL_CO_FAKE_PAIR_HXX

/** @file
    Containers - Fake Pair
    @author Edgar Gonzàlez i Pellicer
*/

#include <utility>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Fake pair with fixed first element
    template <typename T1, typename T2, int value>
    class fake_pair_first {
    public:
      /// First type
      typedef T1 first_type;

      /// Second type
      typedef T2 second_type;

      /// First value
      static const first_type first = value;

      /// Second value
      second_type second;

    public:
      /// Constructor
      fake_pair_first(const second_type& _second = second_type()) :
        second(_second) {
      }

#ifdef TTCL_CO_FAKE_PAIR_CONVERSION
      /// Conversion to second
      operator second_type() const {
        return second;
      }
#endif
    };

    /// Fake pair with fixed second element
    template <typename T1, typename T2, int value>
    class fake_pair_second {
    public:
      /// First type
      typedef T1 first_type;

      /// Second type
      typedef T2 second_type;

      /// First value
      first_type first;

      /// Second value
      static const second_type second = value;

    public:
      /// Constructor
      fake_pair_second(const first_type& _first = first_type()) :
        first(_first) {
      }

#ifdef TTCL_CO_FAKE_PAIR_CONVERSION
      /// Conversion to first
      operator first_type() const {
        return first;
      }
#endif
    };

    /// Comparison between two fake_pair_first
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator==(const fake_pair_first<T1, T2, value_a>& _a,
               const fake_pair_first<T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between two fake_pair_second
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator==(const fake_pair_second<T1, T2, value_a>& _a,
               const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a fake_pair_first and a fake_pair_second
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator==(const fake_pair_first <T1, T2, value_a>& _a,
               const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a fake_pair_second and a fake_pair_first
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator==(const fake_pair_second<T1, T2, value_a>& _a,
               const fake_pair_first <T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a fake_pair_first and a std::pair
    template <typename T1, typename T2, int value_a>
    bool
    operator==(const fake_pair_first<T1, T2, value_a>& _a,
               const std::pair<T1, T2>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a std::pair and a fake_pair_first
    template <typename T1, typename T2, int value_b>
    bool
    operator==(const std::pair<T1, T2>& _a,
               const fake_pair_first<T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a fake_pair_second and a std::pair
    template <typename T1, typename T2, int value_a>
    bool
    operator==(const fake_pair_second<T1, T2, value_a>& _a,
               const std::pair<T1, T2>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }

    /// Comparison between a std::pair and a fake_pair_second
    template <typename T1, typename T2, int value_b>
    bool
    operator==(const std::pair<T1, T2>& _a,
               const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first == _b.first and _a.second == _b.second;
    }


    /// Comparison between two fake_pair_first
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator<(const fake_pair_first<T1, T2, value_a>& _a,
              const fake_pair_first<T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between two fake_pair_second
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator<(const fake_pair_second<T1, T2, value_a>& _a,
              const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between a fake_pair_first and a fake_pair_second
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator<(const fake_pair_first <T1, T2, value_a>& _a,
              const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);

    }

    /// Comparison between a fake_pair_second and a fake_pair_first
    template <typename T1, typename T2,
              int value_a, int value_b>
    bool
    operator<(const fake_pair_second<T1, T2, value_a>& _a,
              const fake_pair_first <T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between a fake_pair_first and a std::pair
    template <typename T1, typename T2, int value_a>
    bool
    operator<(const fake_pair_first<T1, T2, value_a>& _a,
              const std::pair<T1, T2>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between a std::pair and a fake_pair_first
    template <typename T1, typename T2, int value_b>
    bool
    operator<(const std::pair<T1, T2>& _a,
              const fake_pair_first<T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between a fake_pair_second and a std::pair
    template <typename T1, typename T2, int value_a>
    bool
    operator<(const fake_pair_second<T1, T2, value_a>& _a,
              const std::pair<T1, T2>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }

    /// Comparison between a std::pair and a fake_pair_second
    template <typename T1, typename T2, int value_b>
    bool
    operator<(const std::pair<T1, T2>& _a,
              const fake_pair_second<T1, T2, value_b>& _b) {
      return _a.first < _b.first or
            (_a.first == _b.first and _a.second < _b.second);
    }
  }
}

// Static vars
#ifdef TTCL_DEBUG
#define TTCL_CO_FAKE_PAIR_STATIC                                \
  template <typename T1, typename T2, int value>                \
  const T1 ttcl::co::fake_pair_first<T1,T2,value>::first;       \
  template <typename T1, typename T2, int value>                \
  const T2 ttcl::co::fake_pair_second<T1,T2,value>::second
#else
#define TTCL_CO_FAKE_PAIR_STATIC
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
