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

#include <boost/type_traits/is_same.hpp>

#include <tap++/tap++.h>

#include <ttcl/mf/maximum_common_type.hxx>

// Main
int
main() {
  TAP::plan(11);

  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<int, int>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<int, char>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<char, int>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<short, char>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<char, short>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<double, float>::type,
                    double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<float, double>::type,
                    double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<double, int>::type,
                    double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<int, double>::type,
                    double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<float, int>::type,
                    float>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::maximum_common_type<int, float>::type,
                    float>::value));

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
