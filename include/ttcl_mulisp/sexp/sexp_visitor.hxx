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

#ifndef TTCL_MULISP_SEXP_SEXP_VISITOR_HXX
#define TTCL_MULISP_SEXP_SEXP_VISITOR_HXX

/** @file
    S-Expressions - Visitor
    @author Edgar Gonzàlez i Pellicer
*/

#include <string>

#include <boost/intrusive_ptr.hpp>

#include <ttcl_mulisp/sexp/sexp.hxx>
#include <ttcl_mulisp/sexp/sexp_atom.hxx>
#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_integer.hxx>
#include <ttcl_mulisp/sexp/sexp_native.hxx>
#include <ttcl_mulisp/sexp/sexp_null.hxx>
#include <ttcl_mulisp/sexp/sexp_number.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_procedure.hxx>
#include <ttcl_mulisp/sexp/sexp_real.hxx>
#include <ttcl_mulisp/sexp/sexp_string.hxx>
#include <ttcl_mulisp/sexp/sexp_symbol.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// S-Expression visitor interface
    class sexp_visitor {
    public:
      /// Visit
      virtual void
      visit(sexp& _sexp);

      /// Visit
      virtual void
      visit(sexp_atom& _sexp);

      /// Visit
      virtual void
      visit(sexp_bool& _sexp);

      /// Visit
      virtual void
      visit(sexp_integer& _sexp);

      /// Visit
      virtual void
      visit(sexp_null& _sexp);

      /// Visit
      virtual void
      visit(sexp_number& _sexp);

      /// Visit
      virtual void
      visit(sexp_pair& _sexp);

      /// Visit
      virtual void
      visit(sexp_real& _sexp);

      /// Visit
      virtual void
      visit(sexp_native& _sexp);

      /// Visit
      virtual void
      visit(sexp_procedure& _sexp);

      /// Visit
      virtual void
      visit(sexp_string& _sexp);

      /// Visit
      virtual void
      visit(sexp_symbol& _sexp);
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
