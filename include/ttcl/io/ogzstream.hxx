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

#ifndef TTCL_IO_OGZSTREAM_HXX
#define TTCL_IO_OGZSTREAM_HXX

/** @file
    Input/Output - Output Zlib-Based Streams
    @author Deepak Bandyopadhyay
    @author Lutz Kettner
    @author Edgar Gonzàlez i Pellicer
*/

#include <iostream>

#include <ttcl/io/_gzstream.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    //// Output Zlib Stream
    class ogzstream :
      public gzstreambase, public std::ostream {
    public:
      /// Empty Constructor
      ogzstream();

      /// Constructor
      ogzstream(const char* _name, int _open_mode = std::ios::out);

      /// Buffer
      gzstreambuf*
      rdbuf();

      /// Open
      void
      open(const char* _name, int _open_mode = std::ios::out);
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
