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

#ifndef TTCL_FN_GAUSSIAN_KERNEL_HXX
#define TTCL_FN_GAUSSIAN_KERNEL_HXX

/** @file
    Functions - Gaussian kernel
    @author Edgar Gonzàlez i Pellicer
*/

#include <cmath>
#include <functional>

#include <ttcl/global.hxx>
#include <ttcl/fn/traits.hxx>
#include <ttcl/mf/coalesce.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {

    /// Gaussian kernel
    template <typename Distance>
    class gaussian_kernel {
    public:
      /// Distance type
      typedef Distance distance_type;

      /// Parameter type
      typedef typename mf::coalesce<
        typename distance_type::result_type, double>::type result_type;

    private:
      /// Alpha parameter
      result_type alpha_;

      /// Gamma parameter
      result_type gamma_;

      /// Distance
      distance_type distance_;

    public:
      /// Constructor
      gaussian_kernel(result_type _alpha = result_type(1),
                      result_type _gamma = result_type(1),
                      const distance_type& _distance = distance_type()) :
        alpha_(_alpha), gamma_(_gamma), distance_(_distance) {
      }

      /// Apply
      template <typename First, typename Second>
      result_type
      operator()(const First&  _first, const Second& _second) const {
        return alpha_ * std::exp(-gamma_ * distance_(_first, _second));
      }
    };


    /// Is symmetric
    /** Specialization for gaussian_kernel
     */
    template <typename Distance>
    struct is_symmetric< gaussian_kernel<Distance> > :
      public is_symmetric<Distance> {
    };


    /// Adaptable gaussian kernel
    /** A model of Adaptable Binary Function
     */
    template <typename Distance>
    class adaptable_gaussian_kernel :
      public std::binary_function<
        typename Distance::first_argument_type,
        typename Distance::second_argument_type,
        typename Distance::result_type> {
    public:
      // Base type
      typedef std::binary_function<
        typename Distance::first_argument_type,
        typename Distance::second_argument_type,
        typename Distance::result_type> base_type;

      /// Distance type
      typedef Distance distance_type;

      /// First argument type
      TTCL_IMPORT_TYPE(base_type, first_argument_type);

      /// Second argument type
      TTCL_IMPORT_TYPE(base_type, second_argument_type);

      /// Result type
      TTCL_IMPORT_TYPE(base_type, result_type);

    private:
      /// Alpha parameter
      result_type alpha_;

      /// Gamma parameter
      result_type gamma_;

      /// Distance
      distance_type distance_;

    public:
      /// Constructor
      adaptable_gaussian_kernel(result_type _alpha = result_type(1),
                                result_type _gamma = result_type(1),
                                const distance_type& _distance =
                                  distance_type()) :
        base_type(), alpha_(_alpha), gamma_(_gamma), distance_(_distance) {
      }

      /// Apply
      result_type
      operator()(const first_argument_type&  _first,
                 const second_argument_type& _second) const {
        return alpha_ * std::exp(-gamma_ * distance_(_first, _second));
      }
    };


    /// Is symmetric
    /** Specialization for adaptable_gaussian_kernel
     */
    template <typename Distance>
    struct is_symmetric< adaptable_gaussian_kernel<Distance> > :
      public is_symmetric<Distance> {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
