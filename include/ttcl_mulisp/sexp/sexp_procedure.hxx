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

#ifndef TTCL_MULISP_SEXP_SEXP_PROCEDURE_HXX
#define TTCL_MULISP_SEXP_SEXP_PROCEDURE_HXX

/** @file
    S-Expressions - Procedure
    @author Edgar Gonzàlez i Pellicer
*/

#include <string>
#include <vector>

#include <ttcl/c++0x.hxx>

#include <ttcl_mulisp/sexp/sexp_atom.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    /// Procedure
    class sexp_procedure :
      public sexp_atom {
    private:
      /// Name
      std::string name_;

      /// Parameters
      std::vector<std::string> parameters_;

      /// Body
      std::vector<sexp_ptr> body_;

    public:
      /// Constructor
      sexp_procedure(const std::string& _name,
                     const std::vector<std::string>& _parameters,
                     const std::vector<sexp_ptr>& _body);

#ifdef TTCL_CXX0X_RVALUES
      /// Move constructor
      sexp_procedure(std::vector<std::string>&& _parameters,
                     std::vector<sexp_ptr>&& _body);
#endif

      /// Is procedure?
      virtual bool
      is_procedure() const;

      /// Name
      const std::string&
      name() const;

      /// Parameters
      const std::vector<std::string>&
      parameters() const;

      /// Body
      const std::vector<sexp_ptr>&
      body() const;

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
    typedef boost::intrusive_ptr<sexp_procedure> sexp_procedure_ptr;
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
