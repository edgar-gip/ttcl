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

#ifndef TTCL_SYS_EXCEPTION_HXX
#define TTCL_SYS_EXCEPTION_HXX

/** @file
    System Exceptions
    @author Edgar Gonzalez i Pellicer
*/

#include <errno.h>

#include <cstring>

#include <ttcl/exception.hxx>

/// TTCL Namespace
namespace ttcl {

  /// System Exception
  class sys_exception :
    public exception {
  protected:
    // The error number
    int error_;

  public:
    /// Constructor
    /** @param _file    Exception source file
        @param _line_no Exception source line number
        @param _error   The error number
        @param _message Description message
    */
    sys_exception(const std::string& _file, uint _line_no, int _error,
                  const std::string& _message);

    /// Constructor from a char* and a variable argument list
    /** printf-style interpolation
     */
    sys_exception(const std::string& _file, uint _line_no, int _error,
                  const char* _format, ...) TTCL_PRINTF_CHECK(5, 6);

    /// Copy Constructor
    /** @param _other Source exception
     */
    sys_exception(const sys_exception& _other);

    /// Get the error number
    int
    error() const;

    /// Get the error string
    std::string
    error_string() const;

    /// Write to an ostream
    /** @param _os Target ostream
     */
    virtual void
    display(std::ostream& _os = std::cerr) const;

    /// Description
    virtual const char*
    what() const
      throw();
  };
}

/// Throw a system exception
#define TTCL_SYS_FIRE(...)                                              \
  throw ttcl::sys_exception(__FILE__, __LINE__, errno, __VA_ARGS__)

/// Throw a custom system exception
#define TTCL_CUSTOM_SYS_FIRE(...)                               \
  throw ttcl::sys_exception(__FILE__, __LINE__, __VA_ARGS__)

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
