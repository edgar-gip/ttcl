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

#include <ttcl_mulisp/run/lisp_interpreter.hxx>

#include <climits>
#include <iostream>

#include <ttcl_mulisp/sexp/sexp_native.hxx>

#include "config.hxx"
#include "procedures.hxx"

using namespace std;
using namespace ttcl_mulisp;
using namespace ttcl_mulisp::run;

/// Constructor
lisp_interpreter::
lisp_interpreter() {
  set("and",           new sexp::sexp_native("and",            true, 0, INT_MAX, and_procedure));
  set("append",        new sexp::sexp_native("append",        false, 0, INT_MAX, append_procedure));
  set("apply",         new sexp::sexp_native("apply",         false, 2,       2, apply_procedure));
  set("begin",         new sexp::sexp_native("begin",          true, 0, INT_MAX, begin_procedure));
  set("car",           new sexp::sexp_native("car",           false, 1,       1, car_procedure));
  set("cdr",           new sexp::sexp_native("cdr",           false, 1,       1, cdr_procedure));
  set("cond",          new sexp::sexp_native("cond",           true, 0, INT_MAX, cond_procedure));
  set("cons",          new sexp::sexp_native("cons",          false, 2,       2, cons_procedure));
  set("copying",       new sexp::sexp_native("copying",       false, 0,       0, copying_procedure));
  set("define",        new sexp::sexp_native("define",         true, 1, INT_MAX, define_procedure));
  set("display",       new sexp::sexp_native("display",       false, 1,       1, display_procedure));
  set("error",         new sexp::sexp_native("error",         false, 1, INT_MAX, error_procedure));
  set("eval",          new sexp::sexp_native("eval",          false, 1,       1, eval_procedure));
  set("foreach",       new sexp::sexp_native("foreach",        true, 2, INT_MAX, foreach_procedure));
  set("if",            new sexp::sexp_native("if",             true, 2,       3, if_procedure));
  set("lambda",        new sexp::sexp_native("lambda",         true, 1, INT_MAX, lambda_procedure));
  set("let*",          new sexp::sexp_native("let*",           true, 1, INT_MAX, let_star_procedure));
  set("list",          new sexp::sexp_native("list",          false, 0, INT_MAX, list_procedure));
  set("map",           new sexp::sexp_native("map",           false, 2,       2, map_procedure));
  set("newline",       new sexp::sexp_native("newline",       false, 0,       0, newline_procedure));
  set("not",           new sexp::sexp_native("not",           false, 1,       1, not_procedure));
  set("null?",         new sexp::sexp_native("null?",         false, 1,       1, nullp_procedure));
  set("/",             new sexp::sexp_native("/",             false, 0, INT_MAX, number_divides_procedure));
  set("=",             new sexp::sexp_native("=",             false, 0, INT_MAX, number_equal_to_procedure));
  set(">",             new sexp::sexp_native(">",             false, 0, INT_MAX, number_greater_procedure));
  set(">=",            new sexp::sexp_native(">=",            false, 0, INT_MAX, number_greater_equal_procedure));
  set("<",             new sexp::sexp_native("<",             false, 0, INT_MAX, number_less_procedure));
  set("<=",            new sexp::sexp_native("<=",            false, 0, INT_MAX, number_less_equal_procedure));
  set("-",             new sexp::sexp_native("-",             false, 0, INT_MAX, number_minus_procedure));
  set("*",             new sexp::sexp_native("*",             false, 0, INT_MAX, number_multiplies_procedure));
  set("+",             new sexp::sexp_native("+",             false, 0, INT_MAX, number_plus_procedure));
  set("or",            new sexp::sexp_native("or",             true, 0, INT_MAX, or_procedure));
  set("parse",         new sexp::sexp_native("parse",         false, 1,       1, parse_procedure));
  set("quasiquote",    new sexp::sexp_native("quasiquote",     true, 1,       1, quasiquote_procedure));
  set("quote",         new sexp::sexp_native("quote",          true, 1,       1, quote_procedure));
  set("reverse",       new sexp::sexp_native("reverse",       false, 1,       1, reverse_procedure));
  set("set!",          new sexp::sexp_native("set!",           true, 2,       2, set_procedure));
  set("string-append", new sexp::sexp_native("string-append", false, 0, INT_MAX, string_append_procedure));
  set("string=",       new sexp::sexp_native("string=",       false, 0, INT_MAX, string_equal_to_procedure));
  set("string>",       new sexp::sexp_native("string>",       false, 0, INT_MAX, string_greater_procedure));
  set("string>=",      new sexp::sexp_native("string>=",      false, 0, INT_MAX, string_greater_equal_procedure));
  set("string<",       new sexp::sexp_native("string<",       false, 0, INT_MAX, string_less_procedure));
  set("string<=",      new sexp::sexp_native("string<=",      false, 0, INT_MAX, string_less_equal_procedure));
  set("warranty",      new sexp::sexp_native("warranty",      false, 0,       0, warranty_procedure));
  set("while",         new sexp::sexp_native("while",          true, 1, INT_MAX, while_procedure));
  set("write",         new sexp::sexp_native("write",         false, 1,       1, write_procedure));
}

/// Startup message
static const char* startup_message =
  "TTCL-uLisp (on " PACKAGE_NAME " " PACKAGE_VERSION ")\n"
  "Copyright (C) 2012  Edgar Gonzalez i Pellicer\n"
  "This program comes with ABSOLUTELY NO WARRANTY; for details type `(warranty)'.\n"
  "This is free software, and you are welcome to redistribute it under certain conditions; type `(copying)' for details.\n";

/// Show startup message
void lisp_interpreter::
show_startup() {
  cout << startup_message;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
