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

#include <map>

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/run/interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_procedure.hxx>
#include <ttcl_mulisp/sexp/sexp_symbol.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// Get procedure parameter list
    static vector<string>
    procedure_params(const char* _name, sexp_ptr _list) {
      vector<string> parameters;

      while (_list->is_pair()) {
        sexp_pair_ptr p_list = sexp_cast<sexp_pair>(_list);

        if (not p_list->car()->is_symbol())
          TTCL_FIRE("(%s): Argument 1 must be a symbol list",
                    _name);

        parameters.push_back
          (sexp_cast<sexp_symbol>(p_list->car())->value());

        _list = p_list->cdr();
      }

      if (not _list->is_null()) {
        TTCL_FIRE("(%s): Argument 1 must be a symbol list",
                  _name);
      }

      return parameters;
    }

    /// (define (symbol...) expr...)
    sexp_ptr
    define_procedure(const vector<sexp_ptr>& _args,
                     interpreter& _interpreter) {
      if (not _args[0]->is_pair())
        TTCL_FIRE("(define): Argument 1 must be a symbol list");
      sexp_pair_ptr s_list = sexp_cast<sexp_pair>(_args[0]);

      if (not s_list->car()->is_symbol())
        TTCL_FIRE("(define): Argument 1 must be a symbol list");
      string name = sexp_cast<sexp_symbol>(s_list->car())->value();

      vector<string> parameters =
        procedure_params("define", s_list->cdr());

      vector<sexp_ptr> body;
      for (uint i = 1; i < _args.size(); ++i)
        body.push_back(_args[i]);

      sexp_ptr proc =
        new sexp_procedure(name, move(parameters), move(body));
      _interpreter.set(name, proc);
      return proc;
    }

    /// (lambda (symbol...) expr...)
    sexp_ptr
    lambda_procedure(const vector<sexp_ptr>& _args,
                     interpreter& /* _interpreter */) {
      vector<string> parameters =
        procedure_params("lambda", _args[0]);

      vector<sexp_ptr> body;
      for (uint i = 1; i < _args.size(); ++i)
        body.push_back(_args[i]);

      return new sexp_procedure
        ("<anonymous>", move(parameters), move(body));
    }

    /// Process binding list
    static void
    process_binding_list(sexp_ptr _vars, interpreter& _interpreter) {
      vector<string> names;

      while (_vars->is_pair()) {
        sexp_pair_ptr p_vars = sexp_cast<sexp_pair>(_vars);

        sexp_ptr cur = p_vars->car();
        if (not cur->is_pair())
          TTCL_FIRE("(let*): Argument 1 must be a symbol or a binding list");
        sexp_pair_ptr p_cur = sexp_cast<sexp_pair>(cur);

        if (not p_cur->car()->is_symbol())
          TTCL_FIRE("(let*): Argument 1 must be a symbol or a binding list");
        sexp_symbol_ptr sym = sexp_cast<sexp_symbol>(p_cur->car());

        if (not p_cur->cdr()->is_pair())
          TTCL_FIRE("(let*): Argument 1 must be a symbol or a binding list");
        sexp_pair_ptr vlist = sexp_cast<sexp_pair>(p_cur->cdr());

        if (not vlist->cdr()->is_null())
          TTCL_FIRE("(let*): Argument 1 must be a symbol or a binding list");

        sexp_ptr value = _interpreter.eval(vlist->car());
        _interpreter.localize(sym->value());
        _interpreter.set(sym->value(), value);

        _vars = p_vars->cdr();
      }

      if (not _vars->is_null())
        TTCL_FIRE("(let*): Argument 1 must be a symbol or a binding list");
    }

    /// (let* ((symbol expr) ...) body ...)
    sexp_ptr
    let_star_procedure(const vector<sexp_ptr>& _args,
                       interpreter& _interpreter) {
      _interpreter.push_context();

      try {
        process_binding_list(_args[0], _interpreter);

        sexp_ptr result = sexp_bool::FALSE;
        for (int i = 1; i < _args.size(); ++i)
          result = _interpreter.eval(_args[i]);

        _interpreter.pop_context();

        return result;
      }
      catch (...) {
        _interpreter.pop_context();
        throw;
      }
    }

    /// (set symbol expr)
    sexp_ptr
    set_procedure(const vector<sexp_ptr>& _args,
                  interpreter& _interpreter) {
      if (not _args[0]->is_symbol())
        TTCL_FIRE("(set!): Argument 1 must be a symbol");

      string   name  = sexp_cast<sexp_symbol>(_args[0])->value();
      sexp_ptr value = _interpreter.eval(_args[1]);
      _interpreter.set(name, value);

      return value;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
