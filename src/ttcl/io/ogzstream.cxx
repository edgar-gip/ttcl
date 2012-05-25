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

#include <ttcl/io/ogzstream.hxx>

using namespace std;
using namespace ttcl::io;

/// Empty Constructor
ogzstream::
ogzstream() :
  ostream(&buf_) {
}

/// Constructor
ogzstream::
ogzstream(const char* _name, int _open_mode) :
  gzstreambase(_name, _open_mode), ostream(&buf_) {
}

/// Buffer
gzstreambuf* ogzstream::
rdbuf() {
  return gzstreambase::rdbuf();
}

/// Open
void ogzstream::
open(const char* _name, int _open_mode) {
  gzstreambase::open(_name, _open_mode);
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
