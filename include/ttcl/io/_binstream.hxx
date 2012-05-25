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

#ifndef TTCL_IO__BINSTREAM_HXX
#define TTCL_IO__BINSTREAM_HXX

#if !defined(TTCL_IO_IBINSTREAM_HXX) && \
    !defined(TTCL_IO_OBINSTREAM_HXX)
# error "Cannot include <ttcl/io/_binstream.hxx> directly"
#endif

/** @file
    Input/Output - Base binary stream
    @author Edgar Gonzàlez i Pellicer
*/

#include <iostream>

#include <boost/noncopyable.hpp>

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Base binary stream
    /** Uses the Curiously Recurring Template Pattern
     */
    template <typename Stream>
    class _binstream :
      private boost::noncopyable {
    public:
      /// Stream type
      typedef Stream stream_type;

    protected:
      /// Inner stream
      stream_type* stream_;

      /// Is stream owned?
      bool is_owned_;

    protected:
      /// Empty constructor
      _binstream();

      /// Constructor
      _binstream(stream_type* _stream, bool _is_owned = false);

      /// Destructor
      ~_binstream();

    public:
      /// @name std::[io]stream -like operations
      /// @{

      /// Synchronize
      int
      sync();

      /// Good
      bool
      good() const;

      /// Eof
      bool
      eof() const;

      /// Fail
      bool
      fail() const;

      /// Bad
      bool
      bad() const;

      /// ! operator
      bool
      operator!() const;

      /// Conversion to pointer
      operator void*() const;

      /// Get error state flags
      std::ios_base::iostate
      rdstate() const;

      /// Set error state flags
      void
      setstate(std::ios_base::iostate _state);

      /// Clear error state flags
      void
      clear(std::ios_base::iostate _state = std::ios_base::goodbit);

      /// Get exceptions
      std::ios_base::iostate
      exceptions() const;

      /// Set exceptions
      void
      exceptions(std::ios_base::iostate _except);

      /// @}
    };

    // Empty constructor
    template <typename Stream>
    _binstream<Stream>::
    _binstream() :
      stream_(0), is_owned_(false) {
    }

    // Constructor
    template <typename Stream>
    _binstream<Stream>::
    _binstream(stream_type* _stream, bool _is_owned) :
      stream_(_stream), is_owned_(_is_owned) {
    }

    // Destructor
    template <typename Stream>
    _binstream<Stream>::
    ~_binstream() {
      if (is_owned_)
        delete stream_;
    }

    // Synchronize
    template <typename Stream>
    int _binstream<Stream>::
    sync() {
      return stream_->sync();
    }

    // Good
    template <typename Stream>
    bool _binstream<Stream>::
    good() const {
      return stream_->good();
    }

    // Eof
    template <typename Stream>
    bool _binstream<Stream>::
    eof() const {
      return stream_->eof();
    }

    // Fail
    template <typename Stream>
    bool _binstream<Stream>::
    fail() const {
      return stream_->fail();
    }

    // Bad
    template <typename Stream>
    bool _binstream<Stream>::
    bad() const {
      return stream_->bad();
    }

    // ! operator
    template <typename Stream>
    bool _binstream<Stream>::
    operator!() const {
      return !(*stream_);
    }

    // Conversion to pointer
    template <typename Stream>
    _binstream<Stream>::
    operator void*() const {
      return (void*)(*stream_);
    }

    // Get error state flags
    template <typename Stream>
    std::ios_base::iostate _binstream<Stream>::
    rdstate() const {
      return stream_->rdstate();
    }

    // Set error state flags
    template <typename Stream>
    void _binstream<Stream>::
    setstate(std::ios_base::iostate _state) {
      stream_->setstate(_state);
    }

      // Clear error state flags
    template <typename Stream>
    void _binstream<Stream>::
    clear(std::ios_base::iostate _state) {
      stream_->clear(_state);
    }

    // Get exceptions
    template <typename Stream>
    std::ios_base::iostate _binstream<Stream>::
    exceptions() const {
      return stream_->exceptions();
    }

    // Set exceptions
    template <typename Stream>
    void _binstream<Stream>::
    exceptions(std::ios_base::iostate _except) {
      stream_->exceptions(_except);
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
