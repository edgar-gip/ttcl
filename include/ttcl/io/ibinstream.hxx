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

#ifndef TTCL_IO_IBINSTREAM_HXX
#define TTCL_IO_IBINSTREAM_HXX

/** @file
    Input/Output - Binary input stream
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
    class ibinstream :
      public _binstream<std::istream> {
    public:
      /// Parent type
      typedef _binstream<std::istream> parent_type;

      /// Empty constructor
      ibinstream();

      /// Constructor
      ibinstream(std::istream& _stream, bool _is_owned = false);

      /// Constructor
      ibinstream(std::istream* _stream, bool _is_owned = true);

      /// Constructor from a filename
      /** @overload
       */
      ibinstream(const char* _filename,
                 std::ios_base::openmode _mode = std::ios_base::in);

      /// @name std::ifstream -like operations
      /// @{

      /// Open
      void
      open(std::istream& _stream, bool _is_owned = false);

      /// Open
      void
      open(std::istream* _stream, bool _is_owned = true);

      /// Open
      /** @overload
       */
      void
      open(const char* _filename,
           std::ios_base::openmode _mode = std::ios_base::in);

      /// Is it open?
      bool
      is_open() const;

      /// Close
      void
      close();

      /// @}

      /// @name Deserialization
      /// @{

      /// Deserialize a boolean
      ibinstream&
      operator>>(bool& _val);

      /// Deserialize a short
      ibinstream&
      operator>>(short& _val);

      /// Deserialize an unsigned short
      ibinstream&
      operator>>(unsigned short& _val);

      /// Deserialize an integer
      ibinstream&
      operator>>(int& _val);

      /// Deserialize an unsigned integer
      ibinstream&
      operator>>(unsigned int& _val);

      /// Deserialize a long
      ibinstream&
      operator>>(long& _val);

      /// Deserialize an unsigned long
      ibinstream&
      operator>>(unsigned long& _val);

#ifdef TTCL_CXX11_LONG_LONG

      /// Deserialize a long long
      ibinstream&
      operator>>(long long& _val);

      /// Deserialize an unsigned long long
      ibinstream&
      operator>>(unsigned long long& _val);

#endif

      /// Deserialize a float
      ibinstream&
      operator>>(float& _val);

      /// Deserialize a double
      ibinstream&
      operator>>(double& _val);

      /// Deserialize a long double
      ibinstream&
      operator>>(long double& _val);

      /// Deserialize a void pointer
      ibinstream&
      operator>>(void*& _val);

      /// @}

      // Friend declarations
      friend ibinstream& operator>>(ibinstream& _ibs, char& _ch);
      friend ibinstream& operator>>(ibinstream& _ibs, signed char& _ch);
      friend ibinstream& operator>>(ibinstream& _ibs, unsigned char& _ch);
      friend ibinstream& operator>>(ibinstream& _ibs, char* _str);
      friend ibinstream& operator>>(ibinstream& _ibs, signed char* _str);
      friend ibinstream& operator>>(ibinstream& _ibs, unsigned char* _str);
    };

    /// @name Deserialization global functions

    /// Deserialize a char
    ibinstream&
    operator>>(ibinstream& _ibs, char& _ch);

    /// Deserialize a signed char
    ibinstream&
    operator>>(ibinstream& _ibs, signed char& _ch);

    /// Deserialize an unsigned char
    ibinstream&
    operator>>(ibinstream& _ibs, unsigned char& _ch);

    /// Deserialize a char string
    /** @bug No size checking is done
     */
    ibinstream&
    operator>>(ibinstream& _ibs, char* _str);

    /// Deserialize a signed char string
    /** @bug No size checking is done
     */
    ibinstream&
    operator>>(ibinstream& _ibs, signed char* _str);

    /// Deserialize an unsigned char string
    /** @bug No size checking is done
     */
    ibinstream&
    operator>>(ibinstream& _ibs, unsigned char* _str);

    /// @}
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
