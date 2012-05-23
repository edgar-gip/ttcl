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

#ifndef TTCL_UT_MATH_HXX
#define TTCL_UT_MATH_HXX

/** @file
    Utilities - Simple mathematical utilities
    @author Edgar Gonzàlez i Pellicer
*/

#include <cmath>
#include <limits>

#include <ttcl/assert.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Safe division
    template <typename T>
    inline T
    safe_div(const T _a, const T _b) {
      return _b != T() ? _a / _b : T();
    }

    /// Harmonic mean
    template <typename T>
    inline T
    harmonic_mean(const T _a, const T _b) {
      return safe_div(2 * _a * _b, _a + _b);
    }

    /// Safe floating division
    /** Adapted from <boost/test/floating_point_comparison.hpp>
     */
    template<typename T>
    inline T
    safe_fpt_div(T _f1, T _f2) {
      // Both _f1 and _f2 are unsigned here
      TTCL_ASSERT(_f1 >= T(0));
      TTCL_ASSERT(_f2 >= T(0));

      // Avoid overflow.
      if (_f2 < T(1) and _f1 > _f2 * std::numeric_limits<T>::max())
        return std::numeric_limits<T>::max();

      // Avoid underflow.
      if (_f1 == T(0) or
          (_f2 > T(1) and _f1 < _f2 * std::numeric_limits<T>::min()))
        return T(0);

      return _f1 / _f2;
    }

    /// Strongly close?
    /** Adapted from <boost/test/floating_point_comparison.hpp>
     */
    template <typename T>
    inline bool
    is_strongly_close(const T _a, const T _b,
                      const T _delta = std::numeric_limits<T>::epsilon()) {
      T diff = std::abs(_a - _b);
      T d1   = safe_fpt_div(diff, std::abs(_b));
      T d2   = safe_fpt_div(diff, std::abs(_a));
      return d1 <= _delta and d2 <= _delta;
    }

    /// Weakly close?
    /** Adapted from <boost/test/floating_point_comparison.hpp>
     */
    template <typename T>
    inline bool
    is_weakly_close(const T _a, const T _b,
                    const T _delta = std::numeric_limits<T>::epsilon()) {
      T diff = std::abs(_a - _b);
      T d1   = safe_fpt_div(diff, std::abs(_b));
      T d2   = safe_fpt_div(diff, std::abs(_a));
      return d1 <= _delta or d2 <= _delta;
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
