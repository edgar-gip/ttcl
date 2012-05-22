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

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    // Compare
    template <template <typename> class Comparer>
    static sexp_ptr
    compare(const vector<sexp_ptr>& _args) {
      if (_args.size() >= 2) {
        Comparer<string> comparison;

        string prev = _args[0]->str();
        for (int i = 1; i < _args.size(); ++i) {
          string cur = _args[i]->str();
          if (not comparison(prev, cur))
            return sexp_bool::FALSE;
          prev = cur;
        }
      }

      return sexp_bool::TRUE;
    }

    /// (string= expr ...)
    sexp_ptr
    string_equal_to_procedure(const vector<sexp_ptr>& _args,
                              interpreter& /* _interpreter */) {
      return compare<equal_to>(_args);
    }

    /// (string< expr ...)
    sexp_ptr
    string_less_procedure(const vector<sexp_ptr>& _args,
                          interpreter& /* _interpreter */) {
      return compare<less>( _args);
    }

    /// (string<= expr ...)
    sexp_ptr
    string_less_equal_procedure(const vector<sexp_ptr>& _args,
                                interpreter& /* _interpreter */) {
      return compare<less_equal>(_args);
    }

    /// (string> expr ...)
    sexp_ptr
    string_greater_procedure(const vector<sexp_ptr>& _args,
                             interpreter& /* _interpreter */) {
      return compare<greater>(_args);
    }

    /// (string>= expr ...)
    sexp_ptr
    string_greater_equal_procedure(const vector<sexp_ptr>& _args,
                                   interpreter& /* _interpreter */) {
      return compare<greater_equal>(_args);
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
