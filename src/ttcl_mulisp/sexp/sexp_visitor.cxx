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

#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

// S-Expression visitor interface

/// Visit
void sexp_visitor::
visit(sexp& /* _sexp */) {
}

/// Visit
void sexp_visitor::
visit(sexp_atom& _sexp) {
  return visit(static_cast<sexp&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_bool& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_integer& _sexp) {
  return visit(static_cast<sexp_number&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_null& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_number& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_pair& _sexp) {
  return visit(static_cast<sexp&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_real& _sexp) {
  return visit(static_cast<sexp_number&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_native& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_procedure& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_string& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

/// Visit
void sexp_visitor::
visit(sexp_symbol& _sexp) {
  return visit(static_cast<sexp_atom&>(_sexp));
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
