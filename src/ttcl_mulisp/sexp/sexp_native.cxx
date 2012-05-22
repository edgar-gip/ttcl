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

#include <ttcl_mulisp/sexp/sexp_native.hxx>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

/// Constructor
sexp_native::
sexp_native(const string& _name, bool _macro, int _min_arity, int _max_arity,
            call_type* _call) :
  name_(_name), macro_(_macro), min_arity_(_min_arity), max_arity_(_max_arity),
  call_(_call) {
}

/// Is native?
bool sexp_native::
is_native() const {
  return true;
}

/// Name
const string& sexp_native::
name() const {
  return name_;
}

/// Is macro?
bool sexp_native::
is_macro() const {
  return macro_;
}

/// Minimum arity
int sexp_native::
min_arity() const {
  return min_arity_;
}

/// Maximum arity
int sexp_native::
max_arity() const {
  return max_arity_;
}

/// Call
sexp_native::call_type* sexp_native::
call() const {
  return call_;
}

/// Representation
string sexp_native::
repr() const {
  return "<native: " + name_ + ">";
}

/// Visit
void sexp_native::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp_native::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
