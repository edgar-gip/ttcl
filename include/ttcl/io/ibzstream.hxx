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

#ifndef TTCL_IO_IBZSTREAM_HXX
#define TTCL_IO_IBZSTREAM_HXX

/** @file
    Input/Output - Input Bzlib-Based Streams
    Adapted from Zlib-Based Streams
    @author Edgar Gonzàlez i Pellicer
*/

#include <iostream>

#include <ttcl/io/_bzstream.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Input Bzlib Stream
    class ibzstream :
      public bzstreambase, public std::istream {
    public:
      /// Empty Constructor
      ibzstream();

      /// Constructor
      ibzstream(const char* _name, int _open_mode = std::ios::in);

      /// Buffer
      bzstreambuf*
      rdbuf();

      /// Open
      void
      open(const char* _name, int _open_mode = std::ios::in);
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
