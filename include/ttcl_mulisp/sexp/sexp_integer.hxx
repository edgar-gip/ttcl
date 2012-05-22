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

#ifndef TTCL_MULISP_SEXP_SEXP_INTEGER_HXX
#define TTCL_MULISP_SEXP_SEXP_INTEGER_HXX

/** @file
    S-Expressions - Integer
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl_mulisp/sexp/sexp_number.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// Integer
    class sexp_integer :
      public sexp_number {
    private:
      /// Value
      int value_;

    public:
      /// Constructor
      sexp_integer(const int _value);

      /// Is integer?
      virtual bool
      is_integer() const;

      /// Value
      int
      value() const;

      /// Cast
      operator int() const;

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
    typedef boost::intrusive_ptr<sexp_integer> sexp_integer_ptr;
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
