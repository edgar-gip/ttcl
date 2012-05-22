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

#include <ttcl_mulisp/sexp/sexp_symbol.hxx>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

// Symbol

/// Constructor
sexp_symbol::
sexp_symbol(const string& _value) :
  value_(_value) {
}

/// Is symbol?
bool sexp_symbol::
is_symbol() const {
  return true;
}

/// Value
const string& sexp_symbol::
value() const {
  return value_;
}

/// Cast
sexp_symbol::
operator string() const {
  return value_;
}

/// Representation
string sexp_symbol::
repr() const {
  return value_;
}

/// Visit
void sexp_symbol::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp_symbol::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
