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

#include <ttcl/mf/coalesce.hxx>

// Main
int main() {
  TAP::plan(12);

  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        int>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<int,
                                        boost::mpl::void_>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<int,
                                        double>::type,
                                        int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<double,
                                        int>::type,
                     double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        boost::mpl::void_>::type,
                     boost::mpl::void_>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        boost::mpl::void_,
                                        int>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        int,
                                        boost::mpl::void_>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        int,
                                        double>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<boost::mpl::void_,
                                        double,
                                        int>::type,
                     double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<int,
                                        boost::mpl::void_,
                                        double>::type,
                     int>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<double,
                                        boost::mpl::void_,
                                        int>::type,
                     double>::value));
  TAP::ok
    ((boost::is_same<ttcl::mf::coalesce<double,
                                        boost::mpl::void_,
                                        int,
                                        boost::mpl::void_>::type,
                     double>::value));

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
