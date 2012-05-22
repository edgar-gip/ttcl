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

#include "procedures.hxx"

#include <functional>

#include <boost/foreach.hpp>

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_integer.hxx>
#include <ttcl_mulisp/sexp/sexp_number.hxx>
#include <ttcl_mulisp/sexp/sexp_real.hxx>

using namespace std;

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  /// Interpreter Namespace
  namespace run {

    using namespace sexp;

    /// Identity element
    template <typename Operator>
    struct id_element;

    /// Identity element
    /** Specialization for plus
     */
    template <typename T>
    struct id_element< plus<T> > {
      static constexpr T value() {
        return T(0);
      }
    };

    /// Identity element
    /** Specialization for minus
     */
    template <typename T>
    struct id_element< minus<T> > {
      static constexpr T value() {
        return T(0);
      }
    };

    /// Identity element
    /** Specialization for multiplies
     */
    template <typename T>
    struct id_element< multiplies<T> > {
      static constexpr T value() {
        return T(1);
      }
    };

    /// Identity element
    /** Specialization for divides
     */
    template <typename T>
    struct id_element< divides<T> > {
      static constexpr T value() {
        return T(1);
      }
    };

    // Arithmetic
    template <template <typename> class Operator>
    sexp_ptr
    arithmetic(const char* _name, const vector<sexp_ptr>& _args) {
      bool seen_real = false;
      BOOST_FOREACH(sexp_ptr arg, _args) {
        if (not arg->is_number())
          TTCL_FIRE("(%s): Bad argument type: number expected", _name);

        sexp_number_ptr num_arg = sexp_cast<sexp_number>(arg);
        if (num_arg->is_real())
          seen_real = true;
      }

      if (_args.size() == 0) {
        return new sexp_integer(id_element<Operator<int>>::value());
      }
      else if (_args.size() == 1) {
        if (seen_real) {
          Operator<double> operation;
          return new sexp_real(operation(id_element<Operator<double>>::value(),
                                         sexp_cast<sexp_real>(_args[0])->value()));
        }
        else {
          Operator<int> operation;
          return new sexp_integer(operation(id_element<Operator<int>>::value(),
                                            sexp_cast<sexp_integer>(_args[0])
                                            ->value()));
        }
      }
      else {
        if (seen_real) {
          Operator<double> operation;

          double result;
          if (_args[0]->is_real())
            result = sexp_cast<sexp_real>(_args[0])->value();
          else
            result = sexp_cast<sexp_integer>(_args[0])->value();

          for (int i = 1; i < _args.size(); ++i) {
            double cur;
            if (_args[i]->is_real())
              cur = sexp_cast<sexp_real>(_args[i])->value();
            else
              cur = sexp_cast<sexp_integer>(_args[i])->value();
            result = operation(result, cur);
          }

          return new sexp_real(result);
        }
        else {
          Operator<int> operation;

          int result = sexp_cast<sexp_integer>(_args[0])->value();

          for (int i = 1; i < _args.size(); ++i) {
            int cur = sexp_cast<sexp_integer>(_args[i])->value();
            result = operation(result, cur);
          }

          return new sexp_integer(result);
        }
      }
    }

    /// (+ expr ...)
    sexp_ptr
    number_plus_procedure(const vector<sexp_ptr>& _args,
                          interpreter& /* _interpreter */) {
      return arithmetic<plus>("+", _args);
    }

    /// (- expr ...)
    sexp_ptr
    number_minus_procedure(const vector<sexp_ptr>& _args,
                           interpreter& /* _interpreter */) {
      return arithmetic<minus>("-", _args);
    }

    /// (* expr ...)
    sexp_ptr
    number_multiplies_procedure(const vector<sexp_ptr>& _args,
                                interpreter& /* _interpreter */) {
      return arithmetic<multiplies>("*", _args);
    }

    /// (/ expr ...)
    sexp_ptr
    number_divides_procedure(const vector<sexp_ptr>& _args,
                             interpreter& /* _interpreter */) {
      return arithmetic<divides>("/", _args);
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
