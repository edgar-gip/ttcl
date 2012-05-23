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

#ifndef TTCL_WR_TYPED_SHARED_REFEREE_HXX
#define TTCL_WR_TYPED_SHARED_REFEREE_HXX

/** @file
    Wrappers - Typed shared referee mixin
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/wr/shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Wrapper Namespace
  namespace wr {

    /// Typed referee
    template <typename T, typename Base = shared_referee>
    class typed_shared_referee :
      public Base {
    public:
      /// Element type
      typedef T element_type;

      /// Base type
      typedef Base base_type;

    protected:
      /// Pointer
      element_type* ptr_;

    public:
      /// Constructor
      typed_shared_referee(element_type* _ptr = 0, bool _owned = true,
                           uint _references = 0) :
        base_type(_owned, _references), ptr_(_ptr) {
      }

      /// Destructor
      virtual
      ~typed_shared_referee() {
        if (base_type::owned_)
          delete ptr_;
      }

      /// Type
      virtual const std::type_info&
      type() const {
        return typeid(T);
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
