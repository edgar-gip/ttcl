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

#include <ttcl_mulisp/sexp/sexp_bool.hxx>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

// Boolean

/// Constructor
sexp_bool::
sexp_bool(const bool _value) :
  value_(_value) {
}

/// Is bool?
bool sexp_bool::
is_bool() const {
  return true;
}

/// Is true?
bool sexp_bool::
is_true() const {
  return value_;
}

/// Value
bool sexp_bool::
value() const {
  return value_;
}

/// Cast
sexp_bool::
operator bool() const {
  return value_;
}

/// Representation
string sexp_bool::
repr() const {
  return value_ ? "#t" : "#f";
}

/// Visit
void sexp_bool::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp_bool::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

/// Static false value
sexp_bool_ptr sexp_bool::FALSE { new sexp_bool(false) };

/// Static true value
sexp_bool_ptr sexp_bool::TRUE  { new sexp_bool(true) };

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
