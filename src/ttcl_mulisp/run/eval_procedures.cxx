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

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/run/interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_string.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (apply expr expr)
    sexp_ptr
    apply_procedure(const vector<sexp_ptr>& _args,
                    interpreter& _interpreter) {
      vector<sexp_ptr> args;
      sexp_ptr list = _args[1];
      while (list->is_pair()) {
        sexp_pair_ptr p_list = sexp_cast<sexp_pair>(list);
        args.push_back(p_list->car());
        list = p_list->cdr();
      }

      if (not list->is_null())
        TTCL_FIRE("(apply): Argument 2 must be a list");

      return _interpreter.apply(_args[0], args);
    }

    /// (eval expr)
    sexp_ptr
    eval_procedure(const vector<sexp_ptr>& _args,
                   interpreter& _interpreter) {
      return _interpreter.eval(_args[0]);
    }

    /// (parse string)
    sexp_ptr
    parse_procedure(const vector<sexp_ptr>& _args,
                    interpreter& _interpreter) {
      if (not _args[0]->is_string()) {
        TTCL_FIRE("(parse): Argument 1 must be a string");
      }

      return _interpreter.parse_one
        (sexp_cast<sexp_string>(_args[0])->value());
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
