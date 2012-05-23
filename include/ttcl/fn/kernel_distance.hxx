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

#ifndef TTCL_FN_KERNEL_DISTANCE_HXX
#define TTCL_FN_KERNEL_DISTANCE_HXX

/** @file
    Functions - Gaussian kernel
    @author Edgar Gonzàlez i Pellicer
*/

#include <functional>

#include <ttcl/global.hxx>
#include <ttcl/fn/gaussian_kernel.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {

    /// Kernel distance
    /** A model of Adaptable Binary Function
     */
    template <typename Kernel>
    class kernel_distance {
    public:
      /// Kernel type
      typedef Kernel kernel_type;

      /// Result type
      TTCL_IMPORT_TYPE(kernel_type, result_type);

    private:
      /// Kernel
      kernel_type kernel_;

    public:
      /// Constructor
      kernel_distance(const kernel_type& _kernel = kernel_type()) :
        kernel_(_kernel) {
      }

      /// Apply
      template <typename First, typename Second>
      result_type
      operator()(const First&  _first, const Second& _second) const {
        return   kernel_(_first, _first) + kernel_(_second, _second)
               - result_type(2) * kernel_(_first, _second);
      }
    };


    /// Kernel distance
    /** Specialization for gaussian kernel
     */
    template <typename Distance>
    class kernel_distance< gaussian_kernel<Distance> > {
    public:
      /// Kernel type
      typedef gaussian_kernel<Distance> kernel_type;

      /// Result type
      TTCL_IMPORT_TYPE(kernel_type, result_type);

    private:
      /// Kernel
      kernel_type kernel_;

    public:
      /// Constructor
      kernel_distance(const kernel_type& _kernel = kernel_type()) :
        kernel_(_kernel) {
      }

      /// Apply
      template <typename First, typename Second>
      result_type
      operator()(const First&  _first, const Second& _second) const {
        return result_type(2) * (result_type(1) - kernel_(_first, _second));
      }
    };


    /// Is symmetric
    /** Specialization for kernel_distance
     */
    template <typename Kernel>
    struct is_symmetric< kernel_distance<Kernel> > :
      public is_symmetric<Kernel> {
    };


    /// Adaptable kernel distance
    /** A model of Adaptable Binary Function
     */
    template <typename Kernel>
    class adaptable_kernel_distance :
      public std::binary_function<
        typename Kernel::first_argument_type,
        typename Kernel::second_argument_type,
        typename Kernel::result_type> {
    public:
      // Base type
      typedef std::binary_function<
        typename Kernel::first_argument_type,
        typename Kernel::second_argument_type,
        typename Kernel::result_type> base_type;

      /// Kernel type
      typedef Kernel kernel_type;

      /// First argument type
      TTCL_IMPORT_TYPE(base_type, first_argument_type);

      /// Second argument type
      TTCL_IMPORT_TYPE(base_type, second_argument_type);

      /// Result type
      TTCL_IMPORT_TYPE(base_type, result_type);

    private:
      /// Kernel
      kernel_type kernel_;

    public:
      /// Constructor
      adaptable_kernel_distance(const kernel_type& _kernel = kernel_type()) :
        base_type(), kernel_(_kernel) {
      }

      /// Apply
      result_type
      operator()(const first_argument_type&  _first,
                 const second_argument_type& _second) const {
        return   kernel_(_first, _first) + kernel_(_second, _second)
               - result_type(2) * kernel_(_first, _second);
      }
    };


    /// Adaptable kernel distance
    /** Specialization for gaussian kernel
     */
    template <typename Distance>
    class adaptable_kernel_distance< gaussian_kernel<Distance> > :
      public std::binary_function<
        typename gaussian_kernel<Distance>::first_argument_type,
        typename gaussian_kernel<Distance>::second_argument_type,
        typename gaussian_kernel<Distance>::result_type> {
    public:
      // Base type
      typedef std::binary_function<
        typename gaussian_kernel<Distance>::first_argument_type,
        typename gaussian_kernel<Distance>::second_argument_type,
        typename gaussian_kernel<Distance>::result_type> base_type;

      /// First argument type
      TTCL_IMPORT_TYPE(base_type, first_argument_type);

      /// Second argument type
      TTCL_IMPORT_TYPE(base_type, second_argument_type);

      /// Result type
      TTCL_IMPORT_TYPE(base_type, result_type);

      /// Kernel type
      typedef gaussian_kernel<Distance> kernel_type;

    private:
      /// Kernel
      kernel_type kernel_;

    public:
      /// Constructor
      adaptable_kernel_distance(const kernel_type& _kernel = kernel_type()) :
        base_type(), kernel_(_kernel) {
      }

      /// Apply
      result_type
      operator()(const first_argument_type&  _first,
                 const second_argument_type& _second) const {
        return result_type(2) * (result_type(1) - kernel_(_first, _second));
      }
    };


    /// Is symmetric
    /** Specialization for adaptable_kernel_distance
     */
    template <typename Kernel>
    struct is_symmetric< adaptable_kernel_distance<Kernel> > :
      public is_symmetric<Kernel> {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
