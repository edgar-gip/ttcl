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

#ifndef TTCL_CO_BINARY_MATRIX_HXX
#define TTCL_CO_BINARY_MATRIX_HXX

/** @file
    Data - Binary sparse matrix
    @author Edgar Gonzàlez i Pellicer
*/

#include <memory>
#include <vector>

#include <ttcl/types.hxx>
#include <ttcl/co/_sparse_forwarder.hxx>
#include <ttcl/co/fake_pair.hxx>
#include <ttcl/dt/traits.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Containers Namespace
  namespace co {

    /// Binary sparse matrix
    template <typename Allocator = std::allocator<uint> >
    class binary_matrix :
      public _sparse_forwarder<uint,
        std::vector<std::vector<co::fake_pair_second<uint, uint, 1>,
                                typename Allocator::template rebind<
                                  co::fake_pair_second<uint, uint, 1> >::other>,
                    typename Allocator::template rebind<
                      std::vector<co::fake_pair_second<uint, uint, 1>,
                                  typename Allocator::template rebind<
                                    co::fake_pair_second<uint, uint, 1>
                                  >::other> >::other> > {
    public:
      /// Base type
      typedef _sparse_forwarder<uint,
        std::vector<std::vector<co::fake_pair_second<uint, uint, 1>,
                                typename Allocator::template rebind<
                                  co::fake_pair_second<uint, uint, 1> >::other>,
                    typename Allocator::template rebind<
                      std::vector<co::fake_pair_second<uint, uint, 1>,
                                  typename Allocator::template rebind<
                                    co::fake_pair_second<uint, uint, 1>
                                  >::other> >::other> >
        base_type;

      /// Container type
      TTCL_IMPORT_TYPE(base_type, container_type);

      /// Empty constructor
      TTCL_DEFAULT_CONSTRUCTOR(binary_matrix);

      /// Constructor from container
      binary_matrix(const container_type& _container) :
        base_type(_container) {
      }

#ifdef TTCL_CXX11_RVALUES
      /// Constructor from moved container
      binary_matrix(container_type&& _container) :
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
