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

#ifndef TTCL_MULISP_SEXP_SEXP_NATIVE_HXX
#define TTCL_MULISP_SEXP_SEXP_NATIVE_HXX

/** @file
    S-Expressions - Procedure
    @author Edgar Gonzàlez i Pellicer
*/

#include <string>
#include <vector>

#include <ttcl_mulisp/sexp/sexp_atom.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    /// Interpreter
    class interpreter;
  }

  /// S-Expression Namespace
  namespace sexp {

    /// Native procedure
    class sexp_native :
      public sexp_atom {
    public:
      /// Call type
      typedef sexp_ptr
      call_type(const std::vector<sexp_ptr>&, run::interpreter&);

    private:
      /// Name
      std::string name_;

      /// Is macro
      bool macro_;

      /// Minimum arity
      int min_arity_;

      /// Maximum arity
      int max_arity_;

      /// Call
      call_type* call_;

    public:
      /// Constructor
      sexp_native(const std::string& _name, bool _macro, int _min_arity,
                  int _max_arity, call_type* _call);

      /// Is native?
      virtual bool
      is_native() const;

      /// Name
      const std::string&
      name() const;

      /// Is macro?
      bool
      is_macro() const;

      /// Minimum arity
      int
      min_arity() const;

      /// Maximum arity
      int
      max_arity() const;

      /// Call
      call_type*
      call() const;

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
    typedef boost::intrusive_ptr<sexp_native> sexp_native_ptr;
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
