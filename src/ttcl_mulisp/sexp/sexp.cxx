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

#include <ttcl_mulisp/sexp/sexp.hxx>

#include <ttcl_mulisp/sexp/sexp_const_visitor.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

using namespace std;
using namespace ttcl_mulisp::sexp;

// S-Expression base class

/// Constructor
sexp::
sexp() :
  referers_(0) {
}

/// Destructor
sexp::
~sexp() {
}

/// Is pair?
bool sexp::
is_pair() const {
  return false;
}

/// Is atom?
bool sexp::
is_atom() const {
  return false;
}

/// Is null?
bool sexp::
is_null() const {
  return false;
}

/// Is boolean?
bool sexp::
is_bool() const {
  return false;
}

/// Is number?
bool sexp::
is_number() const {
  return false;
}

/// Is integer?
bool sexp::
is_integer() const {
  return false;
}

/// Is real?
bool sexp::
is_real() const {
  return false;
}

/// Is native?
bool sexp::
is_native() const {
  return false;
}

/// Is procedure?
bool sexp::
is_procedure() const {
  return false;
}

/// Is symbol?
bool sexp::
is_symbol() const {
  return false;
}

/// Is string?
bool sexp::
is_string() const {
  return false;
}

/// Is true?
bool sexp::
is_true() const {
  return true;
}

/// String value
string sexp::
str() const {
  return repr();
}

/// Visit
void sexp::
visit(sexp_visitor& _visitor) {
  _visitor.visit(*this);
}

/// Visit
void sexp::
visit(sexp_const_visitor& _visitor) const {
  _visitor.visit(*this);
}

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// Add reference through an intrusive pointer
    void
    intrusive_ptr_add_ref(sexp* _ptr) {
      ++_ptr->referers_;
    }

    /// Release reference through an intrusive pointer
    void
    intrusive_ptr_release(sexp* _ptr) {
        if (!--_ptr->referers_)
          delete _ptr;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
