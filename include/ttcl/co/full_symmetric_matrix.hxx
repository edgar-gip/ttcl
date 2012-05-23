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

#ifndef TTCL_CO_FULL_SYMMETRIC_MATRIX_HXX
#define TTCL_CO_FULL_SYMMETRIC_MATRIX_HXX

/** @file
    Containers - Full Symmetric matrix
    @author Edgar Gonzàlez i Pellicer
*/

#include <vector>

#include <ttcl/assert.hxx>
#include <ttcl/c++0x.hxx>
#include <ttcl/global.hxx>
#include <ttcl/co/_square_matrix.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Container Namespace
  namespace co {

    /// A full symmetric matrix
    /** Storage order:
        (0,0)
        (1,0), (1,1)
        (2,0), (2,1), (2,2)
        ...

        @param Container
     */
    template <typename T,
              typename Container = std::vector<T> >
    class full_symmetric_matrix :
      public _square_matrix<full_symmetric_matrix<T, Container>,
                            T, Container> {
    protected:
      /// Base type
      typedef _square_matrix<full_symmetric_matrix, T, Container> base_type;

    public:
      /// Element
      TTCL_IMPORT_TYPE(base_type, element);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

    public:
      /// Empty constructor
      TTCL_DEFAULT_CONSTRUCTOR(full_symmetric_matrix);

      /// Constructor
      full_symmetric_matrix(size_type _rows,
                            size_type TTCL_ASSERT_PARAM(_cols),
                            const element& _element = element()) :
        base_type(_rows, _rows * (_rows + 1) / 2, _element) {
        TTCL_ASSERT_EQ(_rows, _cols);
      }

      /// Resize
      void
      resize(size_type _rows, size_type _cols,
             const element& _element = element()) {
        TTCL_ASSERT_EQ(_rows, _cols);
        base_type::resize(_rows, _rows * (_rows + 1) / 2, _element);
      }

      /// Element access
      /** Non-const version
          @param _row Row
          @param _col Column
      */
      element&
      operator()(size_type _row, size_type _col) {
        if (_row < _col)
          return this->data_[_col * (_col + 1) / 2 + _row];
        else
          return this->data_[_row * (_row + 1) / 2 + _col];
      }

      /// Element access
      /** const version
          @param _row Row
          @param _col Column
      */
      const element&
      operator()(size_type _row, size_type _col) const {
        if (_row < _col)
          return this->data_[_col * (_col + 1) / 2 + _row];
        else
          return this->data_[_row * (_row + 1) / 2 + _col];
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
