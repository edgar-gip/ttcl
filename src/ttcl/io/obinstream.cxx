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

#include <ttcl/io/obinstream.hxx>

#include <fstream>
#include <iostream>
#include <limits>

#include <ttcl/c++11.hxx>
#include <ttcl/exception.hxx>
#include <ttcl/io/_binstream.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl::io;

/// Empty constructor
obinstream::
obinstream() :
  parent_type() {
}

/// Constructor
obinstream::
obinstream(ostream& _stream, bool _is_owned) :
  parent_type(&_stream, _is_owned) {
}

/// Constructor
obinstream::
obinstream(ostream* _stream, bool _is_owned) :
  parent_type(_stream, _is_owned) {
}

/// Constructor from a filename
obinstream::
obinstream(const char* _filename,
           ios::openmode _mode) :
  parent_type(new ofstream(_filename,
                           _mode | ios::binary), true) {
}

/// Open
void obinstream::
open(ostream& _stream, bool _is_owned) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = &_stream;
  is_owned_ = _is_owned;
}

/// Open
void obinstream::
open(ostream* _stream, bool _is_owned) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = _stream;
  is_owned_ = _is_owned;
}

/// Open
/** @overload
 */
void obinstream::
open(const char* _filename, ios::openmode _mode) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = new ofstream(_filename, _mode | ios::binary);
  is_owned_ = true;
}

/// Is it open?
bool obinstream::
is_open() const {
  return stream_;
}

/// Close
void obinstream::
close() {
  if (is_owned_)
    delete stream_;

  stream_ = 0;
}

/// Serialize a boolean
obinstream& obinstream::
operator<<(const bool& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(bool));
  return *this;
}

/// Serialize a short
obinstream& obinstream::
operator<<(const short& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(short));
  return *this;
}

/// Serialize an unsigned short
obinstream& obinstream::
operator<<(const unsigned short& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val),
                 sizeof(unsigned short));
  return *this;
}

/// Serialize an integer
obinstream& obinstream::
operator<<(const int& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(int));
  return *this;
}

/// Serialize an unsigned integer
obinstream& obinstream::
operator<<(const unsigned int& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val),
                 sizeof(unsigned int));
  return *this;
}

/// Serialize a long
obinstream& obinstream::
operator<<(const long& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(long));
  return *this;
}

/// Serialize an unsigned long
obinstream& obinstream::
operator<<(const unsigned long& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val),
                 sizeof(unsigned long));
  return *this;
}

#ifdef TTCL_CXX11_LONG_LONG

/// Serialize a long long
obinstream& obinstream::
operator<<(const long long& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(long long));
  return *this;
}

/// Serialize an unsigned long long
obinstream& obinstream::
operator<<(const unsigned long long& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val),
                 sizeof(unsigned long long));
  return *this;
}

#endif

/// Serialize a float
obinstream& obinstream::
operator<<(const float& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(float));
  return *this;
}

/// Serialize a double
obinstream& obinstream::
operator<<(const double& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(double));
  return *this;
}

/// Serialize a long double
obinstream& obinstream::
operator<<(const long double& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val),
                 sizeof(long double));
  return *this;
}

/// Serialize a void pointer
obinstream& obinstream::
operator<<(const void*& _val) {
  stream_->write(reinterpret_cast<const char*>(&_val), sizeof(void*));
  return *this;
}

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Serialize a char
    obinstream&
    operator<<(obinstream& _obs, const char& _ch) {
      _obs.stream_->put(_ch);
      return _obs;
    }

    /// Serialize a signed char
    obinstream&
    operator<<(obinstream& _obs, const signed char& _ch) {
      _obs.stream_->put(_ch);
      return _obs;
    }

    /// Serialize an unsigned char
    obinstream&
    operator<<(obinstream& _obs, const unsigned char& _ch) {
      _obs.stream_->put(_ch);
      return _obs;
    }

    /// Serialize a char string
    obinstream&
    operator<<(obinstream& _obs, const char* _str) {
      *_obs.stream_ << _str;
      _obs.stream_->put('\0');
      return _obs;
    }

    /// Serialize a signed char string
    obinstream&
    operator<<(obinstream& _obs, const signed char* _str) {
      *_obs.stream_ << _str;
      _obs.stream_->put('\0');
      return _obs;
    }

    /// Serialize an unsigned char string
    obinstream&
    operator<<(obinstream& _obs, const unsigned char* _str) {
      *_obs.stream_ << _str;
      _obs.stream_->put('\0');
      return _obs;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
