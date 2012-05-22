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

#ifndef TTCL_MULISP_SEXP_SEXP_HXX
#define TTCL_MULISP_SEXP_SEXP_HXX

/** @file
    S-Expressions - S-Expression
    @author Edgar Gonzàlez i Pellicer
*/

#include <string>

#include <boost/intrusive_ptr.hpp>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// S-Expression Namespace
  namespace sexp {

    // Forward declarations
    class sexp_const_visitor;
    class sexp_visitor;

    /// S-Expression base class
    class sexp {
    private:
      /// Refererers
      int referers_;

    public:
      /// Constructor
      sexp();

      /// Destructor
      virtual
      ~sexp();

      /// Is pair?
      virtual bool
      is_pair() const;

      /// Is atom?
      virtual bool
      is_atom() const;

      /// Is null?
      virtual bool
      is_null() const;

      /// Is boolean?
      virtual bool
      is_bool() const;

      /// Is number?
      virtual bool
      is_number() const;

      /// Is integer?
      virtual bool
      is_integer() const;

      /// Is real?
      virtual bool
      is_real() const;

      /// Is native?
      virtual bool
      is_native() const;

      /// Is procedure?
      virtual bool
      is_procedure() const;

      /// Is symbol?
      virtual bool
      is_symbol() const;

      /// Is string?
      virtual bool
      is_string() const;

      /// Is true?
      virtual bool
      is_true() const;

      /// Representation
      virtual std::string
      repr() const = 0;

      /// String value
      virtual std::string
      str() const;

      /// Visit
      virtual void
      visit(sexp_visitor& _visitor);

      /// Visit
      virtual void
      visit(sexp_const_visitor& _visitor) const;

      // Friend functions
      friend void intrusive_ptr_add_ref(sexp* _ptr);
      friend void intrusive_ptr_release(sexp* _ptr);
    };

    /// Pointer
    typedef boost::intrusive_ptr<sexp> sexp_ptr;

    /// S-expression cast
    template <typename Target, typename Source>
    boost::intrusive_ptr<Target>
    sexp_cast(const boost::intrusive_ptr<Source>& _source) {
      return boost::intrusive_ptr<Target>
        (dynamic_cast<Target*>(_source.get()), true);
    }

    /// Add reference through an intrusive pointer
    void
    intrusive_ptr_add_ref(sexp* _ptr);

    /// Release reference through an intrusive pointer
    void
    intrusive_ptr_release(sexp* _ptr);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
