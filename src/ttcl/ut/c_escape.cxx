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

#include <ttcl/ut/c_escape.hxx>

#include <cctype>

#include <boost/foreach.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace ttcl;

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Escape a String to C
    string
    c_escape(const string& _string) {
      // Result
      string result;

      // For each character
      BOOST_FOREACH (const char& c, _string) {
        switch (c) {
        case '\n': result += "\\n"; break;
        case '\t': result += "\\t"; break;
        case '\v': result += "\\v"; break;
        case '\b': result += "\\b"; break;
        case '\r': result += "\\r"; break;
        case '\f': result += "\\f"; break;
        case '\a': result += "\\a"; break;
        case '\\': result += "\\\\"; break;
        case '"' : result += "\\\""; break;
        default:
          if (c < ' ') {
            result += boost::str(boost::format("\\x%02x") % c);
          }
          else {
            result += c;
          }
        }
      }

      // Return
      return result;
    }

    /// Unescape a String from C
    string
    c_unescape(const string& _string) {
      // Result
      string result;

      // Src iterators
      string::const_iterator src = _string.begin();

      // For each
      while (src != _string.end()) {
        // Is it a slash
        if (*src == '\\') {
          // Unescape
          switch (*++src) {
            // Escape sequences
          case 'n': result += '\n'; ++src; break;
          case 't': result += '\t'; ++src; break;
          case 'v': result += '\v'; ++src; break;
          case 'b': result += '\b'; ++src; break;
          case 'r': result += '\r'; ++src; break;
          case 'f': result += '\f'; ++src; break;
          case 'a': result += '\a'; ++src; break;
            // Convert from hexa
          case 'x': {
            ++src;
            int n = 0;
            int t = 0;
            while (n < 4 && isxdigit(*src)) {
              t *= 16;
              if (isdigit(*src))
                t += *src - '0';
              else if (islower(*src))
                t += *src - 'a';
              else
                t += *src - 'A';
              ++src;
              ++n;
            }
            result += (char)(t & 0xFF);
            break;
          }
            // Convert from octal
          case '0': case '1': case '2':
          case '3': case '4': case '5':
          case '6': case '7': {
            int n = 1;
            int t = *src++ - '0';
            while (n < 3 && *src >= '0' && *src <= '7') {
              t *= 8;
              t += *src++ - '0';
              ++n;
            }
            result += (char)(t & 0xff);
            break;
          }
            // Others
          default:
            result += *src++;
          }
        }
        else {
          // Just add
          result += *src++;
        }
      }

      // Return
      return result;
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
