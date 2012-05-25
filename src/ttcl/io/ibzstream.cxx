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

#include <ttcl/io/ibzstream.hxx>

using namespace std;
using namespace ttcl::io;

/// Empty Constructor
ibzstream::
ibzstream() :
  istream(&buf_) {
}

/// Constructor
ibzstream::
ibzstream(const char* _name, int _open_mode) :
  bzstreambase(_name, _open_mode), istream(&buf_) {
}

/// Buffer
bzstreambuf* ibzstream::
rdbuf() {
  return bzstreambase::rdbuf();
}

/// Open
void ibzstream::
open(const char* _name, int _open_mode) {
  bzstreambase::open(_name, _open_mode);
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
