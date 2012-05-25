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

#include <ttcl_mulisp/sexp/sexp_procedure.hxx>

#include <boost/foreach.hpp>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

/// Constructor
sexp_procedure::
sexp_procedure(const string& _name,
               const vector<string>& _parameters,
               const vector<sexp_ptr>& _body) :
  name_(_name), parameters_(_parameters), body_(_body) {
}

#ifdef TTCL_CXX11_RVALUES
/// Move constructor
sexp_procedure::
sexp_procedure(std::vector<std::string>&& _parameters,
               std::vector<sexp_ptr>&& _body) :
  parameters_(_parameters), body_(_body) {
}
#endif

/// Is procedure?
bool sexp_procedure::
is_procedure() const {
  return true;
}

/// Name
const string& sexp_procedure::
name() const {
  return name_;
}

/// Parameters
const vector<string>& sexp_procedure::
parameters() const {
  return parameters_;
}

/// Body
const vector<sexp_ptr>& sexp_procedure::
body() const {
  return body_;
}

/// Representation
string sexp_procedure::
repr() const {
  string result = "(lambda (";
  if (not parameters_.empty()) {
    result += parameters_[0];
    for (int i = 1; i < parameters_.size(); ++i) {
      result += " ";
      result += parameters_[i];
    }
  }
  result += ")";

  BOOST_FOREACH(sexp_ptr e, body_) {
    result += " ";
    result += e->repr();
  }

  result += ")";

  return result;
}

/// Visit
void sexp_procedure::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp_procedure::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
