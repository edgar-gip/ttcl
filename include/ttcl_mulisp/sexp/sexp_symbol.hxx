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

#ifndef TTCL_MULISP_SEXP_SEXP_SYMBOL_HXX
#define TTCL_MULISP_SEXP_SEXP_SYMBOL_HXX

/** @file
    S-Expressions - Symbol
    @author Edgar Gonzàlez i Pellicer
*/

#include <string>

#include <ttcl_mulisp/sexp/sexp_atom.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// Symbol
    class sexp_symbol :
      public sexp_atom {
    private:
      /// Value
      std::string value_;

    public:
      /// Constructor
      sexp_symbol(const std::string& _value);

      /// Is symbol?
      virtual bool
      is_symbol() const;

      /// Value
      const std::string&
      value() const;

      /// Cast
      operator std::string() const;

      /// Representation
      virtual std::string
      repr() const;

      /// Visit
      virtual void
      visit(sexp_visitor& _visitor);

      /// Visit
      virtual void
      visit(sexp_const_visitor& _visitor) const;
    };

    /// Pointer
    typedef boost::intrusive_ptr<sexp_symbol> sexp_symbol_ptr;
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
