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

#include <iostream>

#include <ttcl_mulisp/sexp/sexp_bool.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// (display expr)
    sexp_ptr
    display_procedure(const vector<sexp_ptr>& _args,
                      interpreter& /* _interpreter */) {
      cout << _args[0]->str() << flush;
      return sexp_bool::TRUE;
    }

    /// (write expr)
    sexp_ptr
    write_procedure(const vector<sexp_ptr>& _args,
                    interpreter& /* _interpreter */) {
      cout << _args[0]->repr() << flush;
      return sexp_bool::TRUE;
    }

    /// (newline)
    sexp_ptr
    newline_procedure(const vector<sexp_ptr>& /* _args */,
                      interpreter& /* _interpreter */) {
      cout << endl;
      return sexp_bool::TRUE;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
