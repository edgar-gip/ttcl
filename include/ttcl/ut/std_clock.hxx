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

#ifndef TTCL_UT_STD_CLOCK_HXX
#define TTCL_UT_STD_CLOCK_HXX

/** @file
    Utility - Standard Random Number Generator
    @author Edgar Gonzàlez i Pellicer
*/

#include <ctime>

#include <ttcl/ut/singleton.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    // Standard clock
    struct std_clock :
      public singleton<std_clock> {
    protected:
      /// Constructor
      std_clock() :
        singleton<std_clock>() {
      }

    public:
      /// Get the time
      std::time_t
      time() const;

      /// Conversion to time_t
      operator std::time_t() const;

      // Friend declarations
      friend class singleton<std_clock>;
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
