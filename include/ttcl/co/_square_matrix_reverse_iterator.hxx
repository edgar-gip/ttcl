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

#ifndef TTCL_CO__SQUARE_MATRIX_REVERSE_ITERATOR_HXX
#define TTCL_CO__SQUARE_MATRIX_REVERSE_ITERATOR_HXX

#if !defined(TTCL_CO__SQUARE_MATRIX_HXX)
#error "Cannot include <ttcl/co/_square_matrix_reverse_iterator.hxx> directly"
#endif

/** @file
    Containers - Square matrix iterator
    @author Edgar Gonzalez i Pellicer
*/

#include <cstddef>
#include <iterator>
#include <memory>

#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <ttcl/co/_square_matrix_iterator.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Square matrix reverse iterator
    /** A model of Random Access Iterator
     */
    template <typename Matrix, typename Ref>
    class _square_matrix_reverse_iterator :
      public std::reverse_iterator< _square_matrix_iterator<Matrix, Ref> > {
    private:
      /// Base type
      typedef std::reverse_iterator< _square_matrix_iterator<Matrix, Ref> >
        base_type;

    public:
      /// Pointer type
      /** Overrides the base class one
       */
      typedef std::auto_ptr<Ref> pointer;

      /// @name Forwarded constructors
      /// @{

      /// Empty constructor
      _square_matrix_reverse_iterator() :
        base_type() {
      }

      /// Constructor
      explicit
      _square_matrix_reverse_iterator(typename base_type::iterator_type
                                        _other) :
        base_type(_other) {
      }

      /// Copy constructor
      _square_matrix_reverse_iterator(const _square_matrix_reverse_iterator&
                                        _other) :
        base_type(_other) {
      }

      /// Copy constructor
      /** From a different type of operator
       */
      template<typename MatrixO, typename RefO>
      _square_matrix_reverse_iterator
        (const _square_matrix_reverse_iterator<MatrixO, RefO>& _other) :
        base_type(_other) {
      }

      /// @}

      /// Pointer
      pointer
      operator->() const {
        return pointer(new Ref(this->base().matrix_, this->base().row_ - 1));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
