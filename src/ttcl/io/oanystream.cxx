#include <ttcl/io/oanystream.hxx>

#include <cstring>
#include <fstream>
#include <iostream>

#include <ttcl/exception.hxx>
#include <ttcl/io/obzstream.hxx>
#include <ttcl/io/ogzstream.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl::io;

/// Open a file
ostream* oanystream::
open(const char* _filename, ios::openmode _mode) {
  // Ensure mode is not in
  if (_mode & ios::in)
    TTCL_FIRE("Can't open a oanystream in ios::in mode");

  // Ensure mode is out
  _mode |= ios::out;

  // Length
  int length = strlen(_filename);

  // Filename ends in .gz?
  if (length > 3 and
      not strcmp(_filename + length - 3, ".gz")) {
    // Open gzip-compressed
    ogzstream* ogzs = new ogzstream(_filename, _mode);
    if (not ogzs->is_open()) {
      delete ogzs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return ogzs;
  }
  // Filename ends in .bz2?
  else if (length > 4 and
           not strcmp(_filename + length - 4, ".bz2")) {
    // Open bzip2-compressed
    obzstream* obzs = new obzstream(_filename, _mode);
    if (not obzs->is_open()) {
      delete obzs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return obzs;
  }
  // Otherwise
  else {
    // Just open
    ofstream* ofs = new ofstream(_filename, _mode);
    if (not ofs->is_open()) {
      delete ofs;
      TTCL_FIRE("Cannot open %s", _filename);
    }
    return ofs;
  }
}

/// Open a file
ofstream* oanystream::
open_raw(const char* _filename, ios::openmode _mode) {
  // Just open
  ofstream* ofs = new ofstream(_filename, _mode);
  if (not ofs->is_open()) {
    delete ofs;
    TTCL_FIRE("Cannot open %s", _filename);
  }
  return ofs;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
