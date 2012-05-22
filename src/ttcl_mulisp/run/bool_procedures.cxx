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

#include "procedures.hxx"

#include <boost/foreach.hpp>

#include <ttcl_mulisp/run/interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_bool.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (not expr)
    sexp_ptr
    not_procedure(const vector<sexp_ptr>& _args,
                  interpreter& /* _interpreter */) {
      return _args[0]->is_true() ? sexp_bool::FALSE : sexp_bool::TRUE;
    }

    /// (and expr ...)
    sexp_ptr
    and_procedure(const vector<sexp_ptr>& _args,
                  interpreter& _interpreter) {
      BOOST_FOREACH(sexp_ptr arg, _args) {
        sexp_ptr eval = _interpreter.eval(arg);
        if (not eval->is_true())
          return eval;
      }

      return sexp_bool::TRUE;
    }

    /// (or expr ...)
    sexp_ptr
    or_procedure(const vector<sexp_ptr>& _args,
                 interpreter& _interpreter) {
      BOOST_FOREACH(sexp_ptr arg, _args) {
        sexp_ptr eval = _interpreter.eval(arg);
        if (eval->is_true())
          return eval;
      }

      return sexp_bool::FALSE;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
