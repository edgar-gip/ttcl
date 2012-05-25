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

#include <ttcl/io/ibinstream.hxx>

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
ibinstream::
ibinstream() :
  parent_type() {
}

/// Constructor
ibinstream::
ibinstream(istream& _stream, bool _is_owned) :
  parent_type(&_stream, _is_owned) {
}

/// Constructor
ibinstream::
ibinstream(istream* _stream, bool _is_owned) :
  parent_type(_stream, _is_owned) {
}

/// Constructor from a filename
ibinstream::
ibinstream(const char* _filename,
           ios_base::openmode _mode) :
  parent_type(new ifstream(_filename,
                           _mode | ios_base::binary), true) {
}

/// Open
void ibinstream::
open(istream& _stream, bool _is_owned) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = &_stream;
  is_owned_ = _is_owned;
}

/// Open
void ibinstream::
open(istream* _stream, bool _is_owned) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = _stream;
  is_owned_ = _is_owned;
}

/// Open
void ibinstream::
open(const char* _filename, ios_base::openmode _mode) {
  if (stream_)
    TTCL_FIRE("Stream already open");

  stream_   = new ifstream(_filename, _mode | ios_base::binary);
  is_owned_ = true;
}

/// Is it open?
bool ibinstream::
is_open() const {
  return stream_;
}

/// Close
void ibinstream::
close() {
  if (is_owned_)
    delete stream_;

  stream_ = 0;
}

/// Deserialize a boolean
ibinstream& ibinstream::
operator>>(bool& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(bool));
  return *this;
}

/// Deserialize a short
ibinstream& ibinstream::
operator>>(short& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(short));
  return *this;
}

/// Deserialize an unsigned short
ibinstream& ibinstream::
operator>>(unsigned short& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(unsigned short));
  return *this;
}

/// Deserialize an integer
ibinstream& ibinstream::
operator>>(int& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(int));
  return *this;
}

/// Deserialize an unsigned integer
ibinstream& ibinstream::
operator>>(unsigned int& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(unsigned int));
  return *this;
}

/// Deserialize a long
ibinstream& ibinstream::
operator>>(long& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(long));
  return *this;
}

/// Deserialize an unsigned long
ibinstream& ibinstream::
operator>>(unsigned long& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(unsigned long));
  return *this;
}

#ifdef TTCL_CXX11_LONG_LONG

/// Deserialize a long long
ibinstream& ibinstream::
operator>>(long long& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(long long));
  return *this;
}

/// Deserialize an unsigned long long
ibinstream& ibinstream::
operator>>(unsigned long long& _val) {
  stream_->read(reinterpret_cast<char*>(&_val),
                sizeof(unsigned long long));
  return *this;
}

#endif

/// Deserialize a float
ibinstream& ibinstream::
operator>>(float& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(float));
  return *this;
}

/// Deserialize a double
ibinstream& ibinstream::
operator>>(double& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(double));
  return *this;
}

/// Deserialize a long double
ibinstream& ibinstream::
operator>>(long double& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(long double));
  return *this;
}

/// Deserialize a void pointer
ibinstream& ibinstream::
operator>>(void*& _val) {
  stream_->read(reinterpret_cast<char*>(&_val), sizeof(void*));
  return *this;
}

/// TTCL Namespace
namespace ttcl {

  /// Input/Output Namespace
  namespace io {

    /// Deserialize a char
    ibinstream&
    operator>>(ibinstream& _ibs, char& _ch) {
      _ibs.stream_->get(_ch);
      return _ibs;
    }

    /// Deserialize a signed char
    ibinstream&
    operator>>(ibinstream& _ibs, signed char& _ch) {
      _ibs.stream_->get(*reinterpret_cast<char*>(&_ch));
      return _ibs;
    }

    /// Deserialize an unsigned char
    ibinstream&
    operator>>(ibinstream& _ibs, unsigned char& _ch) {
      _ibs.stream_->get(*reinterpret_cast<char*>(&_ch));
      return _ibs;
    }

    /// Deserialize a char string
    ibinstream&
    operator>>(ibinstream& _ibs, char* _str) {
      _ibs.stream_->
        getline(_str, numeric_limits<streamsize>::max(), '\0');
      return _ibs;
    }

    /// Deserialize a signed char string
    ibinstream&
    operator>>(ibinstream& _ibs, signed char* _str) {
      _ibs.stream_->
        getline(reinterpret_cast<char*>(_str),
                numeric_limits<streamsize>::max(), '\0');
      return _ibs;
    }

    /// Deserialize an unsigned char string
    ibinstream&
    operator>>(ibinstream& _ibs, unsigned char* _str) {
      _ibs.stream_->
        getline(reinterpret_cast<char*>(_str),
                numeric_limits<streamsize>::max(), '\0');
      return _ibs;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
