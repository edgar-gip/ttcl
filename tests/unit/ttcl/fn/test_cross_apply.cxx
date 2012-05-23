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

#include <functional>
#include <utility>
#include <vector>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include <tap++/tap++.h>

#include <ttcl/types.hxx>
#include <ttcl/co/matrix.hxx>
#include <ttcl/co/full_symmetric_matrix.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/co/traits.hxx>
#include <ttcl/fn/cross_apply.hxx>

using boost::mpl::_1;

// Number of data
const ttcl::uint n_data = 4;

// Data
const double data[n_data] = { 1, 2, 3, 4 };

// Sum of data
const double data_plus[n_data][n_data] =
  { { 2, 3, 4, 5 },
    { 3, 4, 5, 6 },
    { 4, 5, 6, 7 },
    { 5, 6, 7, 8 } };

// Difference of data
const double data_minus[n_data][n_data] =
  { { 0, -1, -2, -3 },
    { 1,  0, -1, -2 },
    { 2,  1,  0, -1 },
    { 3,  2,  1,  0 } };

// Product of data
const double data_multiplies[n_data][n_data] =
  { { 1, 2,  3,  4 },
    { 2, 4,  6,  8 },
    { 3, 6,  9, 12 },
    { 4, 8, 12, 16 } };

// Equality of data
const bool data_equal_to[n_data][n_data] =
  { {  true, false, false, false },
    { false,  true, false, false },
    { false, false,  true, false },
    { false, false, false,  true } };

// Test matrix and function
template <typename Matrix, typename Function, typename Truth>
void
test_matrix_function(const std::vector<double>& _data,
                     const Truth _truth) {
  // Hollow?
  const bool is_hollow =
    boost::is_same<Matrix, ttcl::co::hollow_symmetric_matrix<_1> >::value;

  // Apply the function
  typename boost::mpl::apply<Matrix, typename Function::result_type>::type
    m = ttcl::fn::cross_apply(_data, Function());

  // Check
  bool c1 = TAP::is(m.rows(),    _data.size());
  bool c2 = TAP::is(m.columns(), _data.size());

  // Check
  if (c1 && c2) {
    for (uint i = 0; i < m.rows(); ++i) {
      for (uint j = 0; j < m.columns(); ++j) {
	if (i != j or not is_hollow) {
	  TAP::is(m[i][j], _truth[i][j]);
	}
      }
    }
  }
  else if (is_hollow) {
    TAP::skip(n_data * (n_data - 1));
  }
  else {
    TAP::skip(n_data * n_data);
  }
}

// Test matrix
/* Specialization for non-symmetric matrices */
template <typename Matrix>
void
test_matrix(const std::vector<double>& _data,
            typename boost::disable_if<
              ttcl::co::is_symmetric_matrix<Matrix>
            >::type* /* _dummy */ = 0) {
  test_matrix_function<Matrix, std::plus    <double>   >(_data, data_plus);
  test_matrix_function<Matrix, std::minus   <double>   >(_data, data_minus);
  test_matrix_function<Matrix, std::multiplies<double> >(_data,
                                                         data_multiplies);
  test_matrix_function<Matrix, std::equal_to<double>   >(_data, data_equal_to);
}

// Test matrix
/* Specialization for symmetric matrices */
template <typename Matrix>
void
test_matrix(const std::vector<double>& _data,
            typename boost::enable_if<
              ttcl::co::is_symmetric_matrix<Matrix>
            >::type* /* _dummy */ = 0) {
  test_matrix_function<Matrix, std::plus    <double>   >(_data, data_plus);
  test_matrix_function<Matrix, std::multiplies<double> >(_data,
                                                         data_multiplies);
  test_matrix_function<Matrix, std::equal_to<double>   >(_data, data_equal_to);
}

// Test data
template <typename Data>
void
test_data(const Data& _data) {
  test_matrix< ttcl::co::matrix                 <_1> >(_data);
  test_matrix< ttcl::co::full_symmetric_matrix  <_1> >(_data);
  test_matrix< ttcl::co::hollow_symmetric_matrix<_1> >(_data);
}

// Main
int
main() {
  TAP::plan(164);

  std::vector<double> d_data(data, data + n_data);
  test_data(d_data);

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
