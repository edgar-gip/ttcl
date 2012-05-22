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

#include <cstring>
#include <fstream>
#include <iostream>

#include <ttcl/exception.hxx>
#include <ttcl/sys_exception.hxx>

#include <ttcl_mulisp/run/lisp_interpreter.hxx>
#include <ttcl_mulisp/sexp/sexp_integer.hxx>
#include <ttcl_mulisp/sexp/sexp_string.hxx>

using namespace std;
using ttcl_mulisp::run::lisp_interpreter;
using ttcl_mulisp::sexp::sexp_integer;
using ttcl_mulisp::sexp::sexp_string;

// Main
int
main(int argc, const char* argv[]) {
  try {
    lisp_interpreter lisp;

    if (argc == 1) {
      lisp.set("$0", new sexp_string("-"));
      lisp.set("$N", new sexp_integer(0));

      lisp.show_startup();
      lisp.repl();
    }
    else {
      lisp.set("$0", new sexp_string(argv[1]));
      lisp.set("$N", new sexp_integer(argc - 2));
      for (int i = 2; i < argc; ++i) {
        char buffer[32];
        snprintf(buffer, 32, "$%d", i - 1);
        lisp.set(buffer, new sexp_string(argv[i]));
      }

      if (strcmp(argv[1], "-")) {
        ifstream ifs(argv[1]);
        if (not ifs.is_open())
          TTCL_SYS_FIRE("%s: Cannot open file", argv[1]);

        lisp.eval(argv[1], ifs);
      }
      else {
        lisp.repl();
      }
    }
    return 0;
  }
  catch (ttcl::exception& _e) {
    cerr << _e.message() << endl;
    return -1;
  }
  catch (std::exception& _e) {
    cerr << _e.what() << endl;
    return -1;
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
