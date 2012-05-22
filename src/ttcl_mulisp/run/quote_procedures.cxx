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

#include <stack>

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/run/interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_symbol.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// Append
    static sexp_ptr
    append(sexp_ptr _left, sexp_ptr _right) {
      stack<sexp_ptr> cars;
      while (_left->is_pair()) {
        sexp_pair_ptr p_left = sexp_cast<sexp_pair>(_left);
        cars.push(p_left->car());
        _left = p_left->cdr();
      }

      if (not _left->is_null())
        TTCL_FIRE("(unquote-splicing): Bad result type: list expected");

      sexp_ptr result = _right;
      while (not cars.empty()) {
        result = new sexp_pair(cars.top(), result);
        cars.pop();
      }

      return result;
    }

    /// Expand
    static sexp_ptr
    expand(sexp_ptr _expr, bool& _splice, interpreter& _interpreter) {
      if (_expr->is_pair()) {
        sexp_pair_ptr p_expr = sexp_cast<sexp_pair>(_expr);

        sexp_ptr to_unquote;
        if (p_expr->car()->is_symbol()) {
          sexp_symbol_ptr s_car = sexp_cast<sexp_symbol>(p_expr->car());
          if (s_car->value() == "unquote") {
            if (not p_expr->cdr()->is_pair())
              TTCL_FIRE("(unquote): Bad procedure application");

            sexp_pair_ptr p_cdr = sexp_cast<sexp_pair>(p_expr->cdr());
            if (not p_cdr->cdr()->is_null())
              TTCL_FIRE("(unquote): Expected one argument");

            to_unquote = p_cdr->car();
            _splice    = false;
          }
          else if (s_car->value() == "unquote-splicing") {
            if (not p_expr->cdr()->is_pair())
              TTCL_FIRE("(unquote-splicing): Bad procedure application");

            sexp_pair_ptr p_cdr = sexp_cast<sexp_pair>(p_expr->cdr());
            if (not p_cdr->cdr()->is_null())
              TTCL_FIRE("(unquote-splicing): Expected one argument");

            to_unquote = p_cdr->car();
            _splice    = true;
          }
        }

        if (to_unquote) {
          return _interpreter.eval(to_unquote);
        }
        else {
          bool splice_car, splice_cdr;
          sexp_ptr new_car = expand(p_expr->car(), splice_car, _interpreter);
          sexp_ptr new_cdr = expand(p_expr->cdr(), splice_cdr, _interpreter);
          if (splice_cdr)
            TTCL_FIRE("(unquote-splicing): Bad procedure application");

          _splice = false;
          if (splice_car)
            return append(new_car, new_cdr);
          else if (new_car != p_expr->car() or new_cdr != p_expr->cdr())
            return new sexp_pair(new_car, new_cdr);
          else
            return _expr;
        }
      }
      else {
        _splice = false;
        return _expr;
      }
    }

    /// (quote obj)
    sexp_ptr
    quote_procedure(const vector<sexp_ptr>& _args,
                    interpreter& /* _interpreter */) {
      return _args[0];
    }

    /// (quasiquote obj)
    sexp_ptr
    quasiquote_procedure(const vector<sexp_ptr>& _args,
                         interpreter& _interpreter) {
      bool splice;
      return expand(_args[0], splice, _interpreter);
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
