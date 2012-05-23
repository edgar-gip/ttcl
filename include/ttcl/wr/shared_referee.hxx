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

#ifndef TTCL_WR_SHARED_REFEREE_HXX
#define TTCL_WR_SHARED_REFEREE_HXX

/** @file
    Wrappers - Shared referee base class
    @author Edgar Gonzàlez i Pellicer
*/

#include <typeinfo>

#include <ttcl/types.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Wrapper Namespace
  namespace wr {

    /// Shared referee base
    class shared_referee {
    protected:
      /// Bool owned
      bool owned_;

      /// Number of references
      uint references_;

    public:
      /// Constructor
      shared_referee(bool _owned = true, uint _references = 0);

      /// Destructor
      virtual
      ~shared_referee();

      /// Type
      virtual const std::type_info&
      type() const = 0;

      /// Add reference
      void
      add_reference();

      /// Del reference
      void
      del_reference();
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
