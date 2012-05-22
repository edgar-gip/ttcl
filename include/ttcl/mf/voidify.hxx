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

#ifndef TTCL_MF_VOIDIFY_HXX
#define TTCL_MF_VOIDIFY_HXX

/** @file
    Metafunctions - Voidify
    @author Edgar Gonzalez i Pellicer
*/

/// TTCL Namespace
namespace ttcl {

  /// Metafunction Namespace
  namespace mf {

    /// Voidify a type
    template <typename T>
    struct voidify {
      /// Inner void type
      typedef void type;
    };
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
