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
#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (begin expr...)
    sexp_ptr
    begin_procedure(const vector<sexp_ptr>& _args,
                    interpreter& _interpreter) {
      sexp_ptr result = sexp_bool::FALSE;

      BOOST_FOREACH(sexp_ptr arg, _args)
        result = _interpreter.eval(arg);

      return result;
    }

    /// (cond (expr expr...) ...)
    sexp_ptr
    cond_procedure(const vector<sexp_ptr>& _args,
                   interpreter& _interpreter) {
      BOOST_FOREACH(sexp_ptr arg, _args) {
        if (not arg->is_pair())
          TTCL_FIRE("(cond): Arguments must be lists");

        sexp_pair_ptr p_arg = sexp_cast<sexp_pair>(arg);

        sexp_ptr cond = _interpreter.eval(p_arg->car());
        if (cond->is_true()) {
          sexp_ptr result = sexp_bool::FALSE;
          while (arg->is_pair()) {
            p_arg  = sexp_cast<sexp_pair>(arg);
            result = _interpreter.eval(p_arg->car());
            arg    = p_arg->cdr();
          }

          if (not arg->is_null()) {
            TTCL_FIRE("(cond): Arguments must be lists");
          }

          return result;
        }
      }

      return sexp_bool::FALSE;
    }

    /// (error expr...)
    sexp_ptr
    error_procedure(const vector<sexp_ptr>& _args,
                    interpreter& /* _interpreter */) {
      string error;
      BOOST_FOREACH(sexp_ptr arg, _args)
        error += arg->str();

      TTCL_FIRE(error);
    }

    /// (foreach symbol expr expr...)
    sexp_ptr
    foreach_procedure(const vector<sexp_ptr>& _args,
                      interpreter& _interpreter) {
      if (not _args[0]->is_symbol())
        TTCL_FIRE("(foreach): Argument 1 must be a symbol");
      string name = sexp_cast<sexp_symbol>(_args[0])->value();

      sexp_ptr list = _interpreter.eval(_args[1]);

      _interpreter.push_context();
      try {
        sexp_ptr result = sexp_bool::FALSE;
        while (list->is_pair()) {
          sexp_pair_ptr p_list = sexp_cast<sexp_pair>(list);

          _interpreter.set(name, p_list->car());

          for (int i = 2; i < _args.size(); ++i) {
            result = _interpreter.eval(_args[i]);
          }

          list = p_list->cdr();
        }

        if (not list->is_null())
          TTCL_FIRE("(foreach): Argument 2 must be a list");

        _interpreter.pop_context();
        return result;
      }
      catch (...) {
        _interpreter.pop_context();
        throw;
      }
    }

    /// (if expr expr [expr])
    sexp_ptr
    if_procedure(const vector<sexp_ptr>& _args,
                 interpreter& _interpreter) {
      sexp_ptr cond = _interpreter.eval(_args[0]);
      if (cond->is_true()) {
        return _interpreter.eval(_args[1]);
      }
      else if (_args.size() == 3) {
        return _interpreter.eval(_args[2]);
      }
      else {
        return sexp_bool::FALSE;
      }
    }

    /// (while expr expr...)
    sexp_ptr
    while_procedure(const vector<sexp_ptr>& _args,
                    interpreter& _interpreter) {
      sexp_ptr result = sexp_bool::FALSE;
      sexp_ptr cond   = _interpreter.eval(_args[0]);
      while (cond->is_true()) {
        for (int i = 1; i < _args.size(); ++i)
          result = _interpreter.eval(_args[i]);
        cond = _interpreter.eval(_args[0]);
      }
      return result;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
