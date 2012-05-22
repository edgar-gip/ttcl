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

#include <vector>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>

#include <tap++/tap++.h>

#include <ttcl/tu/choices.hxx>

using boost::mpl::placeholders::_1;

using ttcl::tu::default_choices;

// Types
struct type_a { char id() { return 'a'; } };
struct type_b { char id() { return 'b'; } };
struct type_c { char id() { return 'c'; } };

// Templates
template <typename T> struct tem_a { char id() { return 'a'; } };
template <typename T> struct tem_b { char id() { return 'b'; } };
template <typename T> struct tem_c { char id() { return 'c'; } };

// Test type choice
TTCL_TU_CHOICE(test_type1, type_a);
TTCL_TU_CHOICE(test_type2, type_c);
TTCL_TU_CHOICE(test_cons1, tem_a< ::_1>);
TTCL_TU_CHOICE(test_cons2, tem_c< ::_1>);

// Choices
typedef TTCL_TU_ADD_CHOICE(default_choices, test_type1, type_b) choices_bcac;
typedef TTCL_TU_ADD_CHOICE(default_choices, test_type2, type_b) choices_abac;
typedef TTCL_TU_ADD_CHOICE(choices_bcac,    test_type1, type_c) choices_ccac;
typedef TTCL_TU_ADD_CHOICE(choices_abac,    test_type2, type_a) choices_aaac;

typedef TTCL_TU_ADD_CHOICE(choices_abac, test_cons1, tem_b< ::_1>) choices_abbc;
typedef TTCL_TU_ADD_CHOICE(choices_abbc, test_cons1, tem_c< ::_1>) choices_abcc;
typedef TTCL_TU_ADD_CHOICE(choices_abcc, test_cons2, tem_b< ::_1>) choices_abcb;

// Test class
template <typename Choices = default_choices>
struct test {
  typedef TTCL_TU_GET_CHOICE(Choices, test_type1) type1;
  typedef TTCL_TU_GET_CHOICE(Choices, test_type2) type2;

  typedef TTCL_TU_APPLY_CHOICE(Choices, test_cons1, int) tem1;
  typedef TTCL_TU_APPLY_CHOICE(Choices, test_cons2, int) tem2;

  char id1()  { type1 v; return v.id(); }
  char id2()  { type2 v; return v.id(); }
  char idt1() { tem1  v; return v.id(); }
  char idt2() { tem2  v; return v.id(); }
};

// Main
int main() {
  TAP::plan(32);

  test<> t_acac;
  TAP::is(t_acac.id1(),  'a');
  TAP::is(t_acac.id2(),  'c');
  TAP::is(t_acac.idt1(), 'a');
  TAP::is(t_acac.idt2(), 'c');

  test<choices_bcac> t_bcac;
  TAP::is(t_bcac.id1(), 'b');
  TAP::is(t_bcac.id2(), 'c');
  TAP::is(t_acac.idt1(), 'a');
  TAP::is(t_acac.idt2(), 'c');

  test<choices_abac> t_abac;
  TAP::is(t_abac.id1(), 'a');
  TAP::is(t_abac.id2(), 'b');
  TAP::is(t_acac.idt1(), 'a');
  TAP::is(t_acac.idt2(), 'c');

  test<choices_ccac> t_ccac;
  TAP::is(t_ccac.id1(), 'c');
  TAP::is(t_ccac.id2(), 'c');
  TAP::is(t_acac.idt1(), 'a');
  TAP::is(t_acac.idt2(), 'c');

  test<choices_aaac> t_aaac;
  TAP::is(t_aaac.id1(), 'a');
  TAP::is(t_aaac.id2(), 'a');
  TAP::is(t_acac.idt1(), 'a');
  TAP::is(t_acac.idt2(), 'c');

  test<choices_abbc> t_abbc;
  TAP::is(t_abbc.id1(), 'a');
  TAP::is(t_abbc.id2(), 'b');
  TAP::is(t_abbc.idt1(), 'b');
  TAP::is(t_abbc.idt2(), 'c');

  test<choices_abcc> t_abcc;
  TAP::is(t_abcc.id1(), 'a');
  TAP::is(t_abcc.id2(), 'b');
  TAP::is(t_abcc.idt1(), 'c');
  TAP::is(t_abcc.idt2(), 'c');

  test<choices_abcb> t_abcb;
  TAP::is(t_abcb.id1(), 'a');
  TAP::is(t_abcb.id2(), 'b');
  TAP::is(t_abcb.idt1(), 'c');
  TAP::is(t_abcb.idt2(), 'b');

  return TAP::exit_status();
};

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
