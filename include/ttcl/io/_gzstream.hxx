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

#ifndef TTCL_IO__GZSTREAM_HXX
#define TTCL_IO__GZSTREAM_HXX

#if !defined(TTCL_IO__GZSTREAM_CXX) && \
    !defined(TTCL_IO_IGZSTREAM_HXX) && \
    !defined(TTCL_IO_OGZSTREAM_HXX)
# error "Cannot include <ttcl/io/_gzstream.hxx> directly"
#endif

/** @file
    Input/Output - Zlib-Based Streams
    @author Deepak Bandyopadhyay
    @author Lutz Kettner
    @author Edgar Gonzàlez i Pellicer
*/

#include <zlib.h>

#include <iostream>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Zlib Stream Buffer
    class gzstreambuf :
      public std::streambuf {
    private:
      /// Size of data buffer
      /** Totals 512 bytes under g++ for igzstream at the end.
       */
      static const int bufferSize = 47 + 256;

      /// File handle for compressed file
      gzFile file_;

      /// Data buffer
      char buffer_[bufferSize];

      /// Open/close state of stream
      char opened_;

      /// I/O mode
      int mode_;

      /// Flush buffer
      int
      flush_buffer();

    public:
      /// Constructor
      gzstreambuf();

      /// Destructor
      ~gzstreambuf();

      /// Is it open?
      int
      is_open() const;

      /// Open
      gzstreambuf*
      open(const char* _name, int _open_mode);

      /// Close
      gzstreambuf*
      close();

      /// Overflow
      /** Used for output buffer only
       */
      virtual int
      overflow(int c = EOF);

      /// Underflow
      /** Used for input buffer only
       */
      virtual int
      underflow();

      /// Sync
      virtual int
      sync();
    };


    /// Zlib Stream Base
    class gzstreambase :
      virtual public std::ios {
    protected:
      /// Stream buffer
      gzstreambuf buf_;

    public:
      /// Empty Constructor
      gzstreambase();

      /// Constructor
      gzstreambase(const char* _name, int _open_mode);

      /// Destructor
      ~gzstreambase();

      /// Is it open?
      int
      is_open() const;

      /// Open
      void
      open(const char* _name, int _open_mode);

      /// Close
      void
      close();

      /// Buffer
      gzstreambuf*
      rdbuf();
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
