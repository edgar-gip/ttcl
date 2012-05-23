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

#ifndef TTCL_WR_INTERFACE_WRAP_HXX
#define TTCL_WR_INTERFACE_WRAP_HXX

/** @file
    Wrappers - Base interface wrapper
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/wr/shared_ptr.hxx>
#include <ttcl/wr/shared_referee.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Wrapper Namespace
  namespace wr {

    /// Base interface wrapper
    template <typename Interface = shared_referee>
    class interface_wrap {
    protected:
      /// Pointer
      shared_ptr<Interface> ptr_;

      /// Empty constructor
      interface_wrap() :
        ptr_() {
      }

      /// Constructor
      interface_wrap(Interface* _ptr) :
        ptr_(_ptr) {
      }

      /// Type
      const std::type_info&
      type() const {
        return ptr_->type();
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
