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

#include <ttcl/ut/std_clock.hxx>

#include <cstdlib>
#include <ctime>

using namespace std;
using namespace ttcl;
using namespace ttcl::ut;

// Static
TTCL_UT_SINGLETON_STATIC(std_clock);

/// Get the time
time_t std_clock::
time() const {
  return std::time(NULL);
}

/// Conversion to time_t
std_clock::
operator time_t() const {
  return time();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End: