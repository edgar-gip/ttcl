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

#include <ttcl/io/ianystream.hxx>

#include <cstring>
#include <fstream>
#include <iostream>

#include <ttcl/exception.hxx>
#include <ttcl/io/ibzstream.hxx>
#include <ttcl/io/igzstream.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl::io;

/// Open a file
istream* ianystream::
open(const char* _filename, ios::openmode _mode) {
  // Ensure mode is not out
  if (_mode & ios::out)
    TTCL_FIRE("Can't open a ianystream in ios::out mode");

  // Ensure mode is in
  _mode |= ios::in;

  // Length
  int length = strlen(_filename);

  // Filename ends in .gz or .tgz?
  if ((length > 3 and
       not strcmp(_filename + length - 3, ".gz")) or
      (length > 4 and
       not strcmp(_filename + length - 4, ".tgz"))) {
    // Open gzip-compressed
    igzstream* igzs = new igzstream(_filename, _mode);
    if (not igzs->is_open()) {
      delete igzs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return igzs;
  }
  // Filename ends in .bz2 or .tbz or .tb2?
  else if (length > 4 and
           (not strcmp(_filename + length - 4, ".bz2") or
            not strcmp(_filename + length - 4, ".tbz") or
            not strcmp(_filename + length - 4, ".tb2"))) {
    // Open bzip2-compressed
    ibzstream* ibzs = new ibzstream(_filename, _mode);
    if (not ibzs->is_open()) {
      delete ibzs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return ibzs;
  }
  // Otherwise
  else {
    // Just open
    ifstream* ifs = new ifstream(_filename, _mode);
    if (not ifs->is_open()) {
      delete ifs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return ifs;
  }
}

/// Open a file
ifstream* ianystream::
open_raw(const char* _filename, ios::openmode _mode) {
  // Just open
  ifstream* ifs = new ifstream(_filename, _mode);
  if (not ifs->is_open()) {
    delete ifs;
    TTCL_FIRE("Cannot open %s", _filename);
  }
  return ifs;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
