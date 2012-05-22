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

#include <functional>

#include <boost/foreach.hpp>

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_integer.hxx>
#include <ttcl_mulisp/sexp/sexp_number.hxx>
#include <ttcl_mulisp/sexp/sexp_real.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    // Compare
    template <template <typename> class Comparer>
    static sexp_ptr
    compare(const char* _name, const vector<sexp_ptr>& _args) {
      if (_args.size() >= 2) {
        bool seen_real = false;
        BOOST_FOREACH(sexp_ptr arg, _args) {
          if (not arg->is_number())
            TTCL_FIRE("(%s): Bad argument type: number expected", _name);

          sexp_number_ptr num_arg = sexp_cast<sexp_number>(arg);
          if (num_arg->is_real())
            seen_real = true;
        }

        if (seen_real) {
          Comparer<double> comparison;

          double prev;
          if (_args[0]->is_real())
            prev = sexp_cast<sexp_real>(_args[0])->value();
          else
            prev = sexp_cast<sexp_integer>(_args[0])->value();

          for (int i = 1; i < _args.size(); ++i) {
            double cur;
            if (_args[i]->is_real())
              cur = sexp_cast<sexp_real>(_args[i])->value();
            else
              cur = sexp_cast<sexp_integer>(_args[i])->value();

            if (not comparison(prev, cur))
              return sexp_bool::FALSE;
            prev = cur;
          }
        }
        else {
          Comparer<int> comparison;

          int prev = sexp_cast<sexp_integer>(_args[0])->value();
          for (int i = 1; i < _args.size(); ++i) {
            int cur = sexp_cast<sexp_integer>(_args[i])->value();
            if (not comparison(prev, cur))
              return sexp_bool::FALSE;
            prev = cur;
          }
        }
      }

      return sexp_bool::TRUE;
    }

    /// (= expr ...)
    sexp_ptr
    number_equal_to_procedure(const vector<sexp_ptr>& _args,
                              interpreter& /* _interpreter */) {
      return compare<equal_to>("=", _args);
    }

    /// (< expr ...)
    sexp_ptr
    number_less_procedure(const vector<sexp_ptr>& _args,
                          interpreter& /* _interpreter */) {
      return compare<less>("<", _args);
    }

    /// (<= expr ...)
    sexp_ptr
    number_less_equal_procedure(const vector<sexp_ptr>& _args,
                                interpreter& /* _interpreter */) {
      return compare<less_equal>("<=", _args);
    }

    /// (> expr ...)
    sexp_ptr
    number_greater_procedure(const vector<sexp_ptr>& _args,
                             interpreter& /* _interpreter */) {
      return compare<greater>(">", _args);
    }

    /// (>= expr ...)
    sexp_ptr
    number_greater_equal_procedure(const vector<sexp_ptr>& _args,
                                   interpreter& /* _interpreter */) {
      return compare<greater_equal>(">=", _args);
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
