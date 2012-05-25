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

#ifndef TTCL_DT_MATRIX_DATA_HXX
#define TTCL_DT_MATRIX_DATA_HXX

/** @file
    Data - Matrix data
    @author Edgar Gonzàlez i Pellicer
*/

#include <memory>
#include <vector>

#include <ttcl/c++11.hxx>
#include <ttcl/forward.hxx>
#include <ttcl/co/binary_matrix.hxx>
#include <ttcl/co/matrix.hxx>
#include <ttcl/co/sparse_matrix.hxx>
#include <ttcl/co/vecvec_matrix.hxx>
#include <ttcl/dt/traits.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Data Namespace
  namespace dt {

    /// Matrix data
    template <typename Matrix>
    class matrix_data :
      public Matrix {
    public:
      /// Base type
      typedef Matrix base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Forwarded constructor
#define TTCL_DT_MATRIX_DATA(z, i, _)                                    \
      TTCL_FORWARD_TEMPLATE(i)                                          \
      matrix_data(TTCL_FORWARD_PARAMETERS(i)) :                         \
        base_type(TTCL_FORWARD_CALL(i)) {                               \
      }

      TTCL_FORWARD(TTCL_DT_MATRIX_DATA)
#undef TTCL_DT_MATRIX_DATA

      /// Constructor from data
      matrix_data(const container_type& _data) :
        base_type(_data) {
      }

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved data
      matrix_data(container_type&& _data) :
        base_type(std::move(_data)) {
      }
#endif

      /// Samples
      size_type
      samples() const {
        return this->rows();
      }

      /// Features
      size_type
      features() const {
        return this->columns();
      }
    };

    /// Is dense data
    /** Specialization for matrix_data<co::vecvec_matrix<...>>
     */
    template <typename T, typename Alloc>
    struct is_dense_data< matrix_data<co::vecvec_matrix<T, Alloc> > > :
      public boost::true_type {
    };

    /// Is dense data
    /** Specialization for matrix_data<co::matrix<...>>
     */
    template <typename T, typename Alloc>
    struct is_dense_data< matrix_data<co::matrix<T, Alloc> > > :
      public boost::true_type {
    };

    /// Is sparse data
    /** Specialization for matrix_data<co::binary_matrix<...>>
     */
    template <typename Alloc>
    struct is_sparse_data< matrix_data<co::binary_matrix<Alloc> > > :
      public boost::true_type {
    };

    /// Is dense data
    /** Specialization for matrix_data<co::sparse_matrix<...>>
     */
    template <typename T, typename Alloc>
    struct is_dense_data< matrix_data<co::sparse_matrix<T, Alloc> > > :
      public boost::true_type {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
