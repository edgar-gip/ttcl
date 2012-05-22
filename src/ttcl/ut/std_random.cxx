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

#include <ttcl/ut/std_random.hxx>

#include <cstdlib>

using namespace std;
using namespace ttcl;
using namespace ttcl::ut;

/// Set the seed
void std_random_factory::
set_seed(const std_random_factory::seed_type _seed) {
  srand(_seed);
}

/// Generate
int std_random_factory::
generate() {
  return rand();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
