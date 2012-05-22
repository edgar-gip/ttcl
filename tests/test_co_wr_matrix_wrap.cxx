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

#include <ttcl/co/full_symmetric_matrix.hxx>
#include <ttcl/co/hollow_symmetric_matrix.hxx>
#include <ttcl/co/wr/matrix_wrap.hxx>
// Main
int main() {
  TAP::plan(9);

  ttcl::co::wr::matrix_wrap m_w;

  m_w = new ttcl::co::full_symmetric_matrix<int>(3, 3);
  TAP::is(m_w.size(), 3);
  TAP::is(m_w.rows(), 3);
  TAP::is(m_w.columns(), 3);

  m_w = new ttcl::co::hollow_symmetric_matrix<int>(3, 3);
  TAP::is(m_w.size(), 3);
  TAP::is(m_w.rows(), 3);
  TAP::is(m_w.columns(), 3);

  m_w = new ttcl::co::hollow_symmetric_matrix<int>(3, 3);
  TAP::is(m_w.size(), 3);
  TAP::is(m_w.rows(), 3);
  TAP::is(m_w.columns(), 3);

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
