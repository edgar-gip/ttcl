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

#ifndef TTCL_MULISP_RUN_INTERPRETER_HXX
#define TTCL_MULISP_RUN_INTERPRETER_HXX

/** @file
    Lisp interpreter - Base interpreter
    @author Edgar Gonzàlez i Pellicer
*/

#include <iosfwd>
#include <stack>
#include <string>
#include <unordered_map>

#include <ttcl/c++0x.hxx>

#include <ttcl_mulisp/sexp/sexp.hxx>
#include <ttcl_mulisp/sexp/sexp_visitor.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  // Interpreter Namespace
  namespace run {

    /// Base interpreter
    class interpreter :
      public sexp::sexp_visitor {
    private:
      /// Variables
      std::unordered_map<std::string, sexp::sexp_ptr> variables_;

      /// Push down stack
      std::stack< std::pair<std::string, sexp::sexp_ptr> > push_down_;

      /// Push down size stack
      std::stack<int> push_down_sizes_;

      /// Return value register
      /** For visitation-based evaluation
       */
      sexp::sexp_ptr result_;

    public:
      /// Constructor
      interpreter() TTCL_DEFAULT;

    private:
      /// Copy constructor
      interpreter(const interpreter& _other) TTCL_DELETE;

      /// Assignment operator
      interpreter&
      operator=(const interpreter& _other) TTCL_DELETE;

    public:
      /// Destructor
      virtual
      ~interpreter();

      /// Get variable
      sexp::sexp_ptr
      get(const std::string& _name) const;

      /// Set variable
      void
      set(const std::string& _name, sexp::sexp_ptr _value);

      /// Localize variable
      void
      localize(const std::string& _name);

      /// Push context
      void
      push_context();

      /// Pop context
      void
      pop_context();

      /// Parse
      std::vector<sexp::sexp_ptr>
      parse(const std::string& _string);

      /// Parse one
      sexp::sexp_ptr
      parse_one(const std::string& _string);

      /// Eval
      sexp::sexp_ptr
      eval(sexp::sexp_ptr _expr);

      /// Eval
      /** @overload
       */
      sexp::sexp_ptr
      eval(const std::string& _string);

      /// Eval
      /** @overload
       */
      sexp::sexp_ptr
      eval(const std::string& _name, std::istream& _stream);

      /// Apply
      sexp::sexp_ptr
      apply(sexp::sexp_ptr _functor, const std::vector<sexp::sexp_ptr>& _arguments);

      /// @name S-Expression visitor interface
      /// @{

      /// Visit
      virtual void
      visit(sexp::sexp& _sexp);

      /// Visit
      virtual void
      visit(sexp::sexp_pair& _sexp);

      /// Visit
      virtual void
      visit(sexp::sexp_symbol& _sexp);

      /// @}

      /// REPL
      void
      repl();
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
