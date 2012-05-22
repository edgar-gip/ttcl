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

#ifndef TTCL_MULISP_SEXP_SEXP_PARSER_HXX
#define TTCL_MULISP_SEXP_SEXP_PARSER_HXX

/** @file
    S-Expressions - S-Expression Parser
    @author Edgar Gonzàlez i Pellicer
*/

#include <iosfwd>
#include <vector>

#include <ttcl_mulisp/sexp/sexp.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// S-Expression parser
    class sexp_parser {
    public:
      /// Parse a string
      void
      parse(std::vector<sexp_ptr>& _target, const std::string& _source);

      /// Parse a stream
      void
      parse(std::vector<sexp_ptr>& _target, const std::string& _name,
            std::istream& _is);
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
