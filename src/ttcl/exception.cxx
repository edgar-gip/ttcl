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

#include <ttcl/exception.hxx>

#ifdef TTCL_EXCEPTION_BACKTRACE
# include <execinfo.h>
# ifdef TTCL_EXCEPTION_DEMANGLE
#  include <cxxabi.h>
# endif
#endif

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>

#include <ttcl/global.hxx>
#include <ttcl/types.hxx>

using namespace std;
using namespace ttcl;

// Exception

/// Constructor
ttcl::exception::
exception(const string& _file, ttcl::uint _line_no,
          const string& _message) :
#ifdef TTCL_EXCEPTION_BACKTRACE
  message_(_message), file_(_file), line_no_(_line_no),
  addresses_(0), functions_(0) {
  // Get the backtrace
  get_backtrace();
#else
  message_(_message), file_(_file), line_no_(_line_no) {
#endif
}

/// Constructor from a char* and a variable argument list
ttcl::exception::
exception(const string& _file, ttcl::uint _line_no,
          const char* _format, ...) :
#ifdef TTCL_EXCEPTION_BACKTRACE
  message_(), file_(_file), line_no_(_line_no),
  addresses_(0), functions_(0) {
  // Get the backtrace
  get_backtrace();
#else
  message_(), file_(_file), line_no_(_line_no) {
#endif

  // Create the list
  va_list args;
  va_start(args, _format);

  // Call
  fill_printf(_format, args);

  // End
  va_end(args);
}

/// Non-message specifying constructor
ttcl::exception::
exception(const string& _file, ttcl::uint _line_no) :
#ifdef TTCL_EXCEPTION_BACKTRACE
  message_(), file_(_file), line_no_(_line_no),
  addresses_(0), functions_(0) {
  // Get the backtrace
  get_backtrace();
#else
  message_(), file_(_file), line_no_(_line_no) {
#endif
}

#ifdef TTCL_EXCEPTION_BACKTRACE
/// Get the backtrace
void ttcl::exception::
get_backtrace() {
  // Get the backtrace
  void* bt_buffer[20];
  n_filled_ = backtrace(bt_buffer, 20);

  // Split the first 2
  n_filled_ -= 2;

  // Allocate space for addresses
  addresses_ =
    reinterpret_cast<void**>(malloc(n_filled_ * sizeof(void*)));
  if (not addresses_)
    throw bad_alloc();

  // Copy them
  memcpy(addresses_, bt_buffer + 2, n_filled_ * sizeof(void*));

  // Convert to symbols
  functions_ = backtrace_symbols(addresses_, n_filled_);

  // Check for out of memory
  if (not functions_) {
    free(addresses_);
    throw bad_alloc();
  }

# ifdef TTCL_EXCEPTION_DEMANGLE
  // Demangle each
  for (int i = 0; i < n_filled_; ++i) {
    // Demangled name
    char* demangled = 0;

    // Find the '('
    char* start = strchr(functions_[i], '(');
    if (start) {
      // Find the '+'
      char* end = strchr(start, '+');
      if (end) {
        // Copy to a dmg_buffer
        char dmg_buffer[1024];
        strncpy(dmg_buffer, start + 1, end - start - 1);
        dmg_buffer[end - start - 1] = '\0';

        // Demangle
        int status;
        demangled = abi::__cxa_demangle(dmg_buffer, NULL, 0, &status);

        // Error?
        if (status)
          demangled = strdup(dmg_buffer);
      }
    }

    // Demangled found?
    if (demangled) {
      // Replace
      functions_[i] = demangled;
    }
    else {
      // Just duplicate
      functions_[i] = strdup(functions_[i]);
    }
  }
# endif
}
#endif

/// Fill printf-style
void ttcl::exception::
fill_printf(const char* _format, va_list _args) {
  // Buffer
  char pf_buffer[TTCL_EXCEPTION_WHAT_SIZE];

  // Print to the buffer
  vsnprintf(pf_buffer, TTCL_EXCEPTION_WHAT_SIZE, _format, _args);

  // Save the message
  message_ = pf_buffer;
}

/// Copy Constructor
ttcl::exception::
exception(const exception& _other) :
  std::exception(_other), message_(_other.message_),
  file_(_other.file_), line_no_(_other.line_no_) {
#ifdef TTCL_EXCEPTION_BACKTRACE
  // How many filled?
  n_filled_ = _other.n_filled_;

  // Reserve memory for the addresses
  addresses_ =
    reinterpret_cast<void**>(malloc(n_filled_ * sizeof(void*)));
  if (not addresses_)
    throw bad_alloc();

  // Copy the addresses
  memcpy(addresses_, _other.addresses_, n_filled_ * sizeof(void*));

  // Reserve memory for the function names
  functions_ =
    reinterpret_cast<char**>(malloc(n_filled_ * sizeof(char*)));
  if (not functions_) {
    free(addresses_);
    throw bad_alloc();
}

# ifdef TTCL_EXCEPTION_DEMANGLE
  // Duplicate each function name
  for (int i = 0; i < n_filled_; ++i)
    functions_[i] = strdup(_other.functions_[i]);
# else
  // Copy the function names
  memcpy(functions_, _other.functions_, n_filled_ * sizeof(char*));
# endif
#endif
}

/// Destructor
ttcl::exception::
~exception() throw () {
#ifdef TTCL_EXCEPTION_BACKTRACE
# ifdef TTCL_EXCEPTION_DEMANGLE
  // Free each demangled name
  for (uint i = 0; i < n_filled_; ++i)
    free(functions_[i]);
# endif

  // Free the trace arrays
  free(addresses_);
  free(functions_);
#endif
}

/// Get the message
const string& ttcl::exception::
message() const {
  return message_;
}

/// Get the message
const char* ttcl::exception::
c_message() const {
  return message_.c_str();
}

/// Get the file
const string& ttcl::exception::
file() const {
  return file_;
}

/// Get the file
const char* ttcl::exception::
c_file() const {
  return file_.c_str();
}

/// Get the line number
ttcl::uint ttcl::exception::
line_no() const {
  return line_no_;
}

/// Write to an ostream
void ttcl::exception::
display(ostream& _os) const {
  _os << message_ << " in " << file_
      << ":" << line_no_ << endl;

#ifdef TTCL_EXCEPTION_BACKTRACE
  for (int i = 0; i < n_filled_; ++i)
    _os << " from " << functions_[i] << " ["
        << addresses_[i] << ']' << endl;
#endif
}

/// Description
const char* ttcl::exception::
what() const
  throw() {
  static char buffer[TTCL_EXCEPTION_WHAT_SIZE];
#ifdef TTCL_EXCEPTION_BACKTRACE
  int printed =
#endif
    snprintf(buffer, TTCL_EXCEPTION_WHAT_SIZE - 1, "%s in %s:%d",
             message_.c_str(), file_.c_str(), line_no_);

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
