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

#include <boost/assert.hpp>

#include <ttcl/exception.hxx>

using namespace std;

/// Boost namespace
namespace boost {

  /// Assertion failed
  void assertion_failed(const char* _expr, const char* _function,
                        const char* _file, long line) {
    throw ttcl::exception(_file, line, "%s: Assertion `%s' failed",
                          _function, _expr);
  }

  /// Assertion failed with custom message.
  void assertion_failed_msg(const char* _expr, const char* _message,
                            const char* _function, const char* _file,
                            long line) {
    throw ttcl::exception(_file, line, "%s: Assertion `%s' failed: %s",
                          _function, _expr, _message);
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
