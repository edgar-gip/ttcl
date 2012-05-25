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

#ifndef TTCL_CO_SPARSE_MATRIX_HXX
#define TTCL_CO_SPARSE_MATRIX_HXX

/** @file
    Containers - Sparse matrix
    @author Edgar Gonzàlez i Pellicer
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/foreach.hpp>

#include <ttcl/c++11.hxx>
#include <ttcl/types.hxx>
#include <ttcl/co/_sparse_forwarder.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Sparse matrix
    template <typename T,
              typename Allocator = std::allocator<T> >
    class sparse_matrix :
      public _sparse_forwarder<T,
        std::vector<std::vector<std::pair<uint, T>,
                                typename Allocator::template rebind<
                                  std::pair<uint, T> >::other>,
                    typename Allocator::template rebind<
                      std::vector<std::pair<uint, T>,
                                  typename Allocator::template rebind<
                                    std::pair<uint, T> >::other> >::other> > {
    public:
      /// Base type
      typedef _sparse_forwarder<T,
        std::vector<std::vector<std::pair<uint, T>,
                                typename Allocator::template rebind<
                                  std::pair<uint, T> >::other>,
                    typename Allocator::template rebind<
                      std::vector<std::pair<uint, T>,
                                  typename Allocator::template rebind<
                                    std::pair<uint, T> >::other> >::other> >
        base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Empty constructor
      TTCL_DEFAULT_CONSTRUCTOR(sparse_matrix);

      /// Constructor from container
      sparse_matrix(const container_type& _container) :
        base_type(_container) {
      }

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved container
      sparse_matrix(container_type&& _container) :
        base_type(_container) {
      }
#endif
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
