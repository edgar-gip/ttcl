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

#include <ttcl_mulisp/sexp/sexp_pair.hxx>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

// Pair

/// Constructor
sexp_pair::
sexp_pair(sexp_ptr _car, sexp_ptr _cdr) :
  car_(_car), cdr_(_cdr) {
}

/// Is pair?
bool sexp_pair::
is_pair() const {
  return true;
}

/// Car
sexp_ptr sexp_pair::
car() const {
  return car_;
}

/// Cdr
sexp_ptr sexp_pair::
cdr() const {
  return cdr_;
}

/// Representation
string sexp_pair::
repr() const {
  // Is cdr null?
  if (cdr_->is_null()) {
    // Single-element list
    return "(" + car_->repr() + ")";
  }
  // Is cdr another pair?
  else if (cdr_->is_pair()) {
    // Try to represent as a list
    bool is_list = false;
    std::string cdr_repr =
      static_cast<sexp_pair*>(cdr_.get())->list_repr(is_list);
    if (is_list)
      return "(" + car_->repr() + " " + cdr_repr + ")";
    else
      return "(" + car_->repr() + " . " + cdr_repr + ")";
  }
  // Just another pair
  else {
    return "(" + car_->repr() + " . " + cdr_->repr() + ")";
  }
}

/// Visit
void sexp_pair::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp_pair::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

/// List representation
string sexp_pair::
list_repr(bool& _is_list) {
  // Is cdr null?
  if (cdr_->is_null()) {
    // Single-element list
    _is_list = true;
    return car_->repr();
  }
  // Is cdr another pair?
  else if (cdr_->is_pair()) {
    // Try to represent as a list
    bool cdr_list = false;
    std::string cdr_repr =
      static_cast<sexp_pair*>(cdr_.get())->list_repr(cdr_list);
    if (cdr_list) {
      _is_list = true;
      return car_->repr() + " " + cdr_repr;
    }
    else {
      _is_list = false;
      return "(" + car_->repr() + " . " + cdr_repr + ")";
    }
  }
  // Just another pair
  else {
    _is_list = false;
    return "( " + car_->repr() + " . " + cdr_->repr() + " )";
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
