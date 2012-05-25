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

#ifndef TTCL_CO__DENSE_FORWARDER_HXX
#define TTCL_CO__DENSE_FORWARDER_HXX

#if !defined(TTCL_CO_BOOST_MATRIX_HXX) && \
    !defined(TTCL_CO_VECVEC_MATRIX_HXX)
#error "Cannot include <ttcl/co/_dense_forwarder.hxx> directly"
#endif

/** @file
    Containers - Dense matrix forwarder
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/forward.hxx>
#include <ttcl/global.hxx>

#include <ttcl/c++11.hxx>
#include <ttcl/forward.hxx>
#include <ttcl/co/_matrix_forwarder.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Dense matrix forwarder
    template <typename T,
              typename Container>
    class _dense_forwarder :
      public _matrix_forwarder<T, Container> {
    public:
      /// Base type
      typedef _matrix_forwarder<T, Container> base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Reference
      TTCL_IMPORT_TYPE(base_type, reference);

      /// Const reference
      TTCL_IMPORT_TYPE(base_type, const_reference);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Forwarded constructor
#define TTCL_CO__DENSE_FORWARDER(z, i, _)                               \
      TTCL_FORWARD_TEMPLATE(i)                                          \
      _dense_forwarder(TTCL_FORWARD_PARAMETERS(i)) :                    \
        base_type(TTCL_FORWARD_CALL(i)) {                               \
      }

      TTCL_FORWARD(TTCL_CO__DENSE_FORWARDER)
#undef TTCL_CO__DENSE_FORWARDER

      /// Constructor from data
      _dense_forwarder(const container_type& _data) :
        base_type(_data) {
      }

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved data
      _dense_forwarder(container_type&& _data) :
        base_type(std::move(_data)) {
      }
#endif

      /// Element access
      /** Non-const version
          @param _row Row
          @param _col Column
      */
      reference
      operator()(size_type _row,
                 size_type _col) {
        return this->data_[_row][_col];
      }

      /// Element access
      /** const version
          @param _row Row
          @param _col Column
      */
      const_reference
      operator()(size_type _row,
                 size_type _col) const {
        return this->data_[_row][_col];
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
