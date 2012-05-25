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

#ifndef TTCL_IO_OBINSTREAM_HXX
#define TTCL_IO_OBINSTREAM_HXX

/** @file
    Input/Output - Binary output stream
    @author Edgar Gonzàlez i Pellicer
*/

#include <iostream>

#include <ttcl/c++11.hxx>
#include <ttcl/io/_binstream.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Binary input stream
    /// @bug Generated files are architecture dependent
    class obinstream :
      public _binstream<std::ostream> {
    public:
      /// Parent type
      typedef _binstream<std::ostream> parent_type;

      /// Empty constructor
      obinstream();

      /// Constructor
      obinstream(std::ostream& _stream, bool _is_owned = false);

      /// Constructor
      obinstream(std::ostream* _stream, bool _is_owned = true);

      /// Constructor from a filename
      /** @overload
       */
      obinstream(const char* _filename,
                 std::ios::openmode _mode = std::ios::out);

      /// @name std::ofstream -like operations
      /// @{

      /// Open
      void
      open(std::ostream& _stream, bool _is_owned = false);

      /// Open
      void
      open(std::ostream* _stream, bool _is_owned = true);

      /// Open
      /** @overload
       */
      void
      open(const char* _filename,
           std::ios::openmode _mode = std::ios::out);

      /// Is it open?
      bool
      is_open() const;

      /// Close
      void
      close();

      /// @}

      /// @name Serialization
      /// @{

      /// Serialize a boolean
      obinstream&
      operator<<(const bool& _val);

      /// Serialize a short
      obinstream&
      operator<<(const short& _val);

      /// Serialize an unsigned short
      obinstream&
      operator<<(const unsigned short& _val);

      /// Serialize an integer
      obinstream&
      operator<<(const int& _val);

      /// Serialize an unsigned integer
      obinstream&
      operator<<(const unsigned int& _val);

      /// Serialize a long
      obinstream&
      operator<<(const long& _val);

      /// Serialize an unsigned long
      obinstream&
      operator<<(const unsigned long& _val);

#ifdef TTCL_CXX11_LONG_LONG

      /// Serialize a long long
      obinstream&
      operator<<(const long long& _val);

      /// Serialize an unsigned long long
      obinstream&
      operator<<(const unsigned long long& _val);

#endif

      /// Serialize a float
      obinstream&
      operator<<(const float& _val);

      /// Serialize a double
      obinstream&
      operator<<(const double& _val);

      /// Serialize a long double
      obinstream&
      operator<<(const long double& _val);

      /// Serialize a void pointer
      obinstream&
      operator<<(const void*& _val);

      /// @}

      // Friend declarations
      friend obinstream& operator<<(obinstream& _obs, const char& _ch);
      friend obinstream& operator<<(obinstream& _obs, const signed char& _ch);
      friend obinstream& operator<<(obinstream& _obs, const unsigned char& _ch);
      friend obinstream& operator<<(obinstream& _obs, const char* _str);
      friend obinstream& operator<<(obinstream& _obs, const signed char* _str);
      friend obinstream& operator<<(obinstream& _obs,
                                    const unsigned char* _str);
    };

    /// @name Serialization global functions

    /// Serialize a char
    obinstream&
    operator<<(obinstream& _obs, const char& _ch);

    /// Serialize a signed char
    obinstream&
    operator<<(obinstream& _obs, const signed char& _ch);

    /// Serialize an unsigned char
    obinstream&
    operator<<(obinstream& _obs, const unsigned char& _ch);

    /// Serialize a char string
    /** @bug No size checking is done
     */
    obinstream&
    operator<<(obinstream& _obs, const char* _str);

    /// Serialize a signed char string
    /** @bug No size checking is done
     */
    obinstream&
    operator<<(obinstream& _obs, const signed char* _str);

    /// Serialize an unsigned char string
    /** @bug No size checking is done
     */
    obinstream&
    operator<<(obinstream& _obs, const unsigned char* _str);

    /// @}
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
