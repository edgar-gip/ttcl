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

#ifndef TTCL_CO_CUBE_HXX
#define TTCL_CO_CUBE_HXX

/** @file
    Containers - Cube
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <memory>

#include <boost/multi_array.hpp>

#include <ttcl/c++0x.hxx>
#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// Cube
    /** Implemented on top of boost::multi_array
     */
    template <typename T, typename Alloc = std::allocator<T> >
    class boost_cube :
      public boost::multi_array<T, 3, Alloc> {
    public:
      /// Base type
      typedef boost::multi_array<T, 3, Alloc> base_type;

      /// Element type
      TTCL_IMPORT_TYPE(base_type, element);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Element reference
      typedef element& element_reference;

      /// Const element reference
      typedef const element& const_element_reference;

      /// Empty constructor
      TTCL_DEFAULT_CONSTRUCTOR(boost_cube);

      /// Constructor
      /** @param _rows   Rows
          @param _cols   Cols
          @param _floors Floors
      */
      boost_cube(const size_type _rows,
                 const size_type _cols,
                 const size_type _floors) :
        base_type(boost::extents[_rows][_cols][_floors]) {
      }

      /// Resize
      /** @param _rows  Rows
          @param _cols  Cols
      */
      void
      resize(const size_type _rows,
             const size_type _cols,
             const size_type _floors) {
        // Resize
        base_type::resize(boost::extents[_rows][_cols][_floors]);
      }

      /// Rows
      size_type
      rows() const {
        // Synonym for size
        return this->size();
      }

      /// Columns
      size_type
      columns() const {
        // Second dimension of shape
        return this->shape()[1];
      }

      /// Floors
      size_type
      floors() const {
        // Third dimension of shape
        return this->shape()[2];
      }

      /// Element access
      /** Non-const version
          @param _row Row
          @param _col Column
          @param _flo Floor
      */
      element_reference
      operator()(size_type _row,
                 size_type _col,
                 size_type _flo) {
        return (*this)[_row][_col][_flo];
      }

      /// Element access
      /** const version
          @param _row Row
          @param _col Column
          @param _flo Floor
      */
      const_element_reference
      operator()(size_type _row,
                 size_type _col,
                 size_type _flo) const {
        return (*this)[_row][_col][_flo];
      }

      /// Clear
      void
      clear(const element& _value = element()) {
        std::fill(this->data(),
                  this->data() + rows() * columns() * floors(),
                  _value);
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
