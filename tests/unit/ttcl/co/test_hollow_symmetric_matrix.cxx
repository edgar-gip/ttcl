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

#include <tap++/tap++.h>

#include <ttcl/types.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>

// Number of elements
const ttcl::uint nelems = 3;

// Data
const int hollow_data[nelems][nelems] =
  { { 0, 1, 2 },
    { 1, 0, 3 },
    { 2, 3, 0 } };

// Test
int
main() {
  // Matrix
  typedef ttcl::co::hollow_symmetric_matrix<int> matrix_type;

  // Plan
  TAP::plan(57);

  // First matrix
  matrix_type m1(nelems, nelems);

  // Size is OK
  TAP::is(m1.rows(),      nelems);
  TAP::is(m1.columns(),   nelems);
  TAP::is(m1.data_size(), nelems * (nelems - 1) / 2 + 1);

  // Fill it
  {
    int i = 0;
    for (matrix_type::data_iterator it = m1.data_begin();
         it != m1.data_end(); ++it)
      *it = ++i;
  }

  // Ensure it is OK
  for (matrix_type::size_type r = 0; r < nelems; ++r) {
    for (matrix_type::size_type c = 0; c < nelems; ++c) {
      if (r != c) {
        TAP::is(m1(r, c), hollow_data[r][c]);
        TAP::is(m1[r][c], hollow_data[r][c]);
      }
    }
  }

  // Iterate
  {
    matrix_type::size_type r = 0;
    for (matrix_type::const_row_iterator r_it = m1.row_begin();
         r_it != m1.row_end(); ++r_it, ++r) {
      TAP::is(r_it->size(), nelems);
      matrix_type::size_type c = 0;
      for (matrix_type::row_type::const_iterator c_it = r_it->begin();
           c_it != r_it->end(); ++c_it, ++c) {
        if (r != c)
          TAP::is(*c_it, hollow_data[r][c]);
      }
    }
  }

  // Reverse iterate
  {
    matrix_type::size_type r = nelems;
    for (matrix_type::const_reverse_row_iterator r_it = m1.row_rbegin();
         r_it != m1.row_rend(); ++r_it, --r) {
      TAP::is(r_it->size(), nelems);
      matrix_type::size_type c = nelems;
      for (matrix_type::row_type::const_reverse_iterator c_it =
             r_it->rbegin(); c_it != r_it->rend(); ++c_it, --c) {
        if (r != c)
          TAP::is(*c_it, hollow_data[r - 1][c - 1]);
      }
    }
  }

  // Copy
  matrix_type m2 = m1;
  TAP::ok(    m1 == m2 );
  TAP::ok(not(m1 != m2));
  TAP::ok(not(m1 <  m2));
  TAP::ok(    m1 <= m2 );
  TAP::ok(not(m1 >  m2));
  TAP::ok(    m1 >= m2 );

  // Equal
  for (int r = 0; r < nelems; ++r) {
    TAP::ok(     m1[r] == m2[r] );
    TAP::ok(not (m1[r] != m2[r]));
    TAP::ok(not (m1[r] <  m2[r]));
    TAP::ok(     m1[r] <= m2[r] );
    TAP::ok(not (m1[r] >  m2[r]));
    TAP::ok(     m1[r] >= m2[r] );
  }

  // Return
  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
