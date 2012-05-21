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

#include <ttcl/sys_exception.hxx>

#include <errno.h>

#include <cstring>

using namespace std;
using namespace ttcl;

// System Exception

/// Constructor
sys_exception::
sys_exception(const string& _file, uint _line_no, int _error,
              const string& _message) :
  exception(_file, _line_no, _message), error_(_error) {
}

/// Constructor from a char* and a variable argument list
/** printf-style interpolation
 */
sys_exception::
sys_exception(const string& _file, uint _line_no, int _error,
              const char* _format, ...) :
  exception(_file, _line_no), error_(_error) {
  // Create the list
  va_list args;
  va_start(args, _format);

  // Call
  fill_printf(_format, args);

  // End
  va_end(args);
}

/// Copy Constructor
sys_exception::
sys_exception(const sys_exception& _other) :
  exception(_other), error_(_other.error_) {
}

/// Get the error number
int sys_exception::
error() const {
  return error_;
}

/// Get the error string
string sys_exception::
error_string() const {
  return string(strerror(error_));
}

/// Write to an ostream
void sys_exception::
display(ostream& _os) const {
  _os << message_ << " caused by " << strerror(error_)
      << " in " << file_ << ":" << line_no_ << endl;
#ifdef TTCL_EXCEPTION_BACKTRACE
  for (int i = 0; i < n_filled_; ++i)
    _os << " from " << functions_[i] << " ["
        << addresses_[i] << ']' << endl;
#endif
}

/// Description
const char* sys_exception::
what() const
  throw() {
  static char buffer[TTCL_EXCEPTION_WHAT_SIZE];
#ifdef TTCL_EXCEPTION_BACKTRACE
  int printed =
#endif
    snprintf(buffer, TTCL_EXCEPTION_WHAT_SIZE - 1,
             "%s caused by %s in %s:%d",
             message_.c_str(), strerror(error_),
             file_.c_str(), line_no_);

#ifdef TTCL_EXCEPTION_BACKTRACE
  int i = 0;
  while (printed < TTCL_EXCEPTION_WHAT_SIZE - 1 and
         i < n_filled_) {
    printed += snprintf(buffer + printed, TTCL_EXCEPTION_WHAT_SIZE - printed,
                        " from %s [%p]", functions_[i], addresses_[i]);
    ++i;
  }
#endif
  return buffer;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
