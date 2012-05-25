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

#include <boost/mpl/void.hpp>
#include <boost/type_traits/is_same.hpp>

#include <tap++/tap++.h>

#include <ttcl/dt/matrix_data.hxx>
#include <ttcl/dt/wr/feature_data_w.hxx>

// Main
int
 main() {
  TAP::plan(4);

  ttcl::dt::wr::feature_data_w d_w;

  d_w = new ttcl::dt::matrix_data< ttcl::co::matrix<int> >(10, 3);
  TAP::is(d_w.samples(), 10);
  TAP::is(d_w.features(), 3);

  d_w = new ttcl::dt::matrix_data< ttcl::co::vecvec_matrix<int> >(10, 3);
  TAP::is(d_w.samples(), 10);
  TAP::is(d_w.features(), 3);

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
