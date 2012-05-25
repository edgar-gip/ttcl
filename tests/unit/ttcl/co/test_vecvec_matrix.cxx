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

#include <boost/version.hpp>

#include <ttcl/types.hxx>
#include <ttcl/co/vecvec_matrix.hxx>

// Number of rows and columns
const ttcl::uint n_rows = 4;
const ttcl::uint n_cols = 3;

// Data
const int data[n_rows][n_cols] =
  { {  1,  2,  3 },
    {  4,  5,  6 },
    {  7,  8,  9 },
    { 10, 11, 12 } };

// Test
int
main() {
  // Matrix
  typedef ttcl::co::vecvec_matrix<int> matrix_type;

  // Plan
  TAP::plan(89);

  // First matrix
  matrix_type m1(n_rows, n_cols);

  // Size is OK
  TAP::is(m1.rows(),      n_rows);
  TAP::is(m1.columns(),   n_cols);
  TAP::is(m1.data_size(), n_rows * n_cols);

  // Fill it
  for (matrix_type::size_type r = 0; r < n_rows; ++r) {
    for (matrix_type::size_type c = 0; c < n_cols; ++c) {
      m1(r, c) = data[r][c];
    }
  }

  // Ensure it is OK
  for (matrix_type::size_type r = 0; r < n_rows; ++r) {
    for (matrix_type::size_type c = 0; c < n_cols; ++c) {
      TAP::is(m1(r, c), data[r][c]);
      TAP::is(m1[r][c], data[r][c]);
    }
  }

  // Iterate
  {
    matrix_type::size_type r = 0;
    for (matrix_type::const_row_iterator r_it = m1.row_begin();
         r_it != m1.row_end(); ++r_it, ++r) {
      TAP::is(r_it->size(), n_cols);
      matrix_type::size_type c = 0;
      for (matrix_type::row_type::const_iterator c_it = r_it->begin();
           c_it != r_it->end(); ++c_it, ++c) {
        TAP::is(*c_it, data[r][c]);
      }
    }
  }

  // Reverse iterate
  {
    matrix_type::size_type r = n_rows;
    for (matrix_type::const_reverse_row_iterator r_it = m1.row_rbegin();
         r_it != m1.row_rend(); ++r_it, --r) {
      TAP::is(r_it->size(), n_cols);
      matrix_type::size_type c = n_cols;
      for (matrix_type::row_type::const_reverse_iterator c_it =
             r_it->rbegin(); c_it != r_it->rend(); ++c_it, --c) {
        TAP::is(*c_it, data[r - 1][c - 1]);
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
  for (int r = 0; r < n_rows; ++r) {
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
