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

#include <ttcl/ut/demangle.hxx>

#ifdef __GNUC__
# include <cxxabi.h>
#endif

#include <ttcl/exception.hxx>

using namespace std;
using namespace ttcl;

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Demangle a C++ name
    string
    demangle(const string& _string) {
#ifdef __GNUC__
      int status;
      char* demangled =
        abi::__cxa_demangle(_string.c_str(), NULL, 0, &status);
      switch (status) {
      case 0: {
        string result = demangled;
        free(demangled);
        return result;
      }
      case -1:
        throw bad_alloc();

      case -2:
        TTCL_FIRE("Invalid C++ mangled name `%s'", _string.c_str());

      default:
        TTCL_FIRE("Internal error");
      }
#else
      return _string;
#endif
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
