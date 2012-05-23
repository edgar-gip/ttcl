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

#ifndef TTCL_UT_SINGLETON_HXX
#define TTCL_UT_SINGLETON_HXX

/** @file
    Utilities - Singleton base class
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstdlib>

#include <ttcl/c++0x.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Singleton base class
    template <typename T>
    class singleton {
    public:
      /// Instance type
      typedef T instance_type;

    protected:
      /// Constructor
      singleton() {
      }

      /// Instance
      static T* instance_;

    private:
      // Copy constructor
      singleton(const singleton& _other) TTCL_DELETE;

      // Assignment operator
      singleton& operator=(const singleton& _other) TTCL_DELETE;

    public:
      /// Instance
      static instance_type&
      instance() {
        if (not instance_)
          instance_ = new instance_type();
        return *instance_;
      }
    };
  }
}

/// Singleton static vars
#define TTCL_UT_SINGLETON_STATIC(type) \
  template <> \
  type* ttcl::ut::singleton<type>::instance_ = NULL

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
