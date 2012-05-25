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

#ifndef TTCL_IO_IANYSTREAM_HXX
#define TTCL_IO_IANYSTREAM_HXX

/** @file
    Input/Output - Open any input file stream
    @author Edgar Gonzàlez i Pellicer
*/

#include <fstream>
#include <iostream>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Any input stream
    class ianystream {
    public:
      /// Open a file
      static std::istream*
      open(const char* _filename,
           std::ios::openmode _mode = std::ios::in);

      /// Open a file
      static std::ifstream*
      open_raw(const char* _filename,
               std::ios::openmode _mode = std::ios::in);
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
