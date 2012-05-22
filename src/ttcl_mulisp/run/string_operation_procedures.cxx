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

#include <ttcl_mulisp/sexp/sexp.hxx>
#include <ttcl_mulisp/sexp/sexp_string.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (string-append expr ...)
    sexp_ptr
    string_append_procedure(const vector<sexp_ptr>& _args,
                            interpreter& /* _interpreter */) {
      string result;
      BOOST_FOREACH(sexp_ptr arg, _args)
        result += arg->str();

      return new sexp_string(result);
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
