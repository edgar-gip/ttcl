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

#include "config.hxx"

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// Copying string
    static const char* copying_string =
      "TTCL-uLisp (on " PACKAGE_NAME " " PACKAGE_VERSION ")\n"
      "Copyright (C) 2012  Edgar Gonzalez i Pellicer\n\n"

      PACKAGE_NAME " is free software; you can redistribute it and/or modify\n"
      "it under the terms of the GNU General Public License as published by\n"
      "the Free Software Foundation; either version 3 of the License, or\n"
      "(at your option) any later version.\n\n"

      PACKAGE_NAME " is distributed in the hope that it will be useful,\n"
      "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
      "GNU General Public License for more details.\n\n"

      "You should have received a copy of the GNU General Public License\n"
      "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n";

    /// (copying)
    sexp_ptr
    copying_procedure(const vector<sexp_ptr>& /* _args */,
                      interpreter& /* _interpreter */) {
      cout << copying_string;
      return sexp_bool::TRUE;
    }

    /// Warranty string
    static const char* warranty_string =
        "TTCL-uLisp (on " PACKAGE_NAME " " PACKAGE_VERSION ")\n"
        "Copyright (C) 2012  Edgar Gonzalez i Pellicer\n\n"

        "  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
        "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
        "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n"
        "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n"
        "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
        "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n"
        "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n"
        "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n";

    /// (warranty)
    sexp_ptr
    warranty_procedure(const vector<sexp_ptr>& /* _args */,
                       interpreter& /* _interpreter */) {
      cout << warranty_string;
      return sexp_bool::TRUE;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
