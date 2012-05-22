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

#include <boost/foreach.hpp>

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/run/interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_null.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (append expr...)
    sexp_ptr
    append_procedure(const vector<sexp_ptr>& _args,
                     interpreter& /* _interpreter */) {
      sexp_ptr result;
      if (_args.empty()) {
        result = sexp_null::EOL;
      }
      else {
        if (not (_args.back()->is_pair() or _args.back()->is_null()))
          TTCL_FIRE("(append): Bad argument type: List expected");

        stack<sexp_ptr> elems;
        for (int i = 0; i < _args.size() - 1; ++i) {
          sexp_ptr list = _args[i];
          while (list->is_pair()) {
            sexp_pair_ptr p_list = sexp_cast<sexp_pair>(list);
            elems.push(p_list->car());
            list = p_list->cdr();
          }

          if (not list->is_null())
            TTCL_FIRE("(append): Bad argument type: List expected");
        }

        result = _args.back();
        while (not elems.empty()) {
          result = new sexp_pair(elems.top(), result);
          elems.pop();
        }
      }

      return result;
    }

    /// (cons car cdr)
    sexp_ptr
    cons_procedure(const vector<sexp_ptr>& _args,
                   interpreter& /* _interpreter */) {
      return new sexp_pair(_args[0], _args[1]);
    }

    /// (car pair)
    sexp_ptr
    car_procedure(const vector<sexp_ptr>& _args,
                  interpreter& /* _interpreter */) {
      if (not _args[0]->is_pair())
        TTCL_FIRE("(car): Bad argument type: Pair expected");
      return sexp_cast<sexp_pair>(_args[0])->car();
    }

    /// (cdr pair)
    sexp_ptr
    cdr_procedure(const vector<sexp_ptr>& _args,
                  interpreter& /* _interpreter */) {
      if (not _args[0]->is_pair()) {
        TTCL_FIRE("(cdr): Bad argument type: Pair expected");
      }
      return sexp_cast<sexp_pair>(_args[0])->cdr();
    }

    /// (list expr ...)
    sexp_ptr
    list_procedure(const vector<sexp_ptr>& _args,
                   interpreter& /* _interpreter */) {
      sexp_ptr result = sexp_null::EOL;
      BOOST_REVERSE_FOREACH(sexp_ptr arg, _args) {
        result = new sexp_pair(arg, result);
      }
      return result;
    }

    /// (map expr expr)
    sexp_ptr
    map_procedure(const vector<sexp_ptr>& _args,
                  interpreter& _interpreter) {
      vector<sexp_ptr> results;

      sexp_ptr list = _args[1];
      while (list->is_pair()) {
        sexp_pair_ptr p_list = sexp_cast<sexp_pair>(list);

        vector<sexp_ptr> arguments(1, p_list->car());
        results.push_back(_interpreter.apply(_args[0], arguments));

        list = p_list->cdr();
      }

      sexp_ptr result = sexp_null::EOL;
      BOOST_REVERSE_FOREACH(sexp_ptr res, results) {
        result = new sexp_pair(res, result);
      }

      return result;
    }

    /// (null? expr)
    sexp_ptr
    nullp_procedure(const vector<sexp_ptr>& _args,
                    interpreter& /* _interpreter */) {
      return _args[0]->is_null() ? sexp_bool::TRUE : sexp_bool::FALSE;
    }

    /// (reverse expr)
    sexp_ptr
    reverse_procedure(const vector<sexp_ptr>& _args,
                      interpreter& /* _interpreter */) {
      sexp_ptr result = sexp_null::EOL;

      sexp_ptr list = _args[0];
      while (list->is_pair()) {
        sexp_pair_ptr p_list = sexp_cast<sexp_pair>(list);
        result = new sexp_pair(p_list->car(), result);
        list   = p_list->cdr();
      }

      if (not list->is_null())
        TTCL_FIRE("(reverse): Bad argument type: List expected");

      return result;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
