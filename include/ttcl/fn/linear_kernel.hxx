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

#ifndef TTCL_FN_LINEAR_KERNEL_HXX
#define TTCL_FN_LINEAR_KERNEL_HXX

/** @file
    Functions - Linear kernel
    @author Edgar Gonzàlez i Pellicer
*/

#include <functional>

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>

#include <ttcl/global.hxx>
#include <ttcl/dt/traits.hxx>
#include <ttcl/fn/traits.hxx>
#include <ttcl/mf/coalesce.hxx>
#include <ttcl/mf/maximum_common_type.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {

    /// Linear kernel implementation
    template <typename First,
              typename Second,
              typename Result = ut::null_type,
              typename Enable = void>
    class _linear_kernel_impl;


    /// Linear kernel implementation
    /** Specialization for non-sparse samples
     */
    template <typename First,
              typename Second,
              typename Result>
    class _linear_kernel_impl<
      First, Second, Result,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::mpl::not_< dt::is_sparse_sample<First> >,
          boost::mpl::not_< dt::is_sparse_sample<Second> > > >::type> {
    public:
      // Effective result type
      typedef typename mf::coalesce<
        Result, typename mf::maximum_common_value_type<First, Second>::type
      >::type effective_result_type;

    private:
      // Check
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename First ::value_type,
                                 effective_result_type> ));
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename Second::value_type,
                                 effective_result_type> ));

    public:
      /// Apply
      static effective_result_type
      apply(const First&  _first, const Second& _second) {
        // Types
        TTCL_IMPORT_R_TYPE(First,  const_iterator, first_iterator);
        TTCL_IMPORT_R_TYPE(Second, const_iterator, second_iterator);

        // Sum
        effective_result_type sum = effective_result_type();

        // Follow
        first_iterator  it_f = _first .begin();
        second_iterator it_s = _second.begin();
        while (it_f != _first.end() and it_s != _second.end()) {
          // Update sum
          effective_result_type diff = *it_f * *it_s;
          sum += diff * diff;

          // Next
          ++it_f;
          ++it_s;
        }

        // Return the sum
        return sum;
      }
    };


    /// Linear kernel
    /** Specialization for sparse samples
     */
    template <typename First,
              typename Second,
              typename Result>
    class _linear_kernel_impl<
      First, Second, Result,
      typename boost::enable_if<
        boost::mpl::and_<
          dt::is_sparse_sample<First>,
          dt::is_sparse_sample<Second> > >::type> {
    public:
      // Effective result type
      typedef typename mf::coalesce<
        Result, typename mf::maximum_common_value_type<First, Second>::type
      >::type effective_result_type;

    private:
      // Check
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename First ::value_type::second_type,
                                 effective_result_type> ));
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename Second::value_type::second_type,
                                 effective_result_type> ));

    public:
      /// Apply
      static effective_result_type
      apply(const First&  _first, const Second& _second) {
        // Types
        TTCL_IMPORT_R_TYPE(First,  const_iterator, first_iterator);
        TTCL_IMPORT_R_TYPE(Second, const_iterator, second_iterator);

        // Sum
        effective_result_type sum = effective_result_type();

        // Follow
        first_iterator  it_f = _first .begin();
        second_iterator it_s = _second.begin();
        while (it_f != _first.end() and it_s != _second.end()) {
          // What to do?
          if (it_f->first < it_s->first) {
            // Advance first
            ++it_f;
          }
          else if (it_f->first > it_s->first) {
            // Advance second
            ++it_s;
          }
          else {
            // Update sum
            sum += it_f->second * it_s->second;

            // Advance both
            ++it_f;
            ++it_s;
          }
        }

        // Return the sum
        return sum;
      }
    };


    /// Linear kernel
    template <typename Result = ut::null_type>
    class linear_kernel {
    public:
      /// Result type
      typedef Result result_type;

      /// Apply
      template <typename First, typename Second>
      typename _linear_kernel_impl<
        First, Second, Result>::effective_result_type
      operator()(const First& _first, const Second& _second) const {
        return _linear_kernel_impl<
          First, Second, Result>::apply(_first, _second);
      }
    };


    /// Is symmetric
    /** Specialization for linear_kernel
     */
    template <typename Result>
    struct is_symmetric< linear_kernel<Result> > :
      public boost::true_type {
    };


    /// Adaptable linear kernel
    /** A model of Adaptable Binary Function
     */
    template <typename First,
              typename Second,
              typename Result>
    class adaptable_linear_kernel :
      public std::binary_function<First, Second, Result> {
    public:
      // Base type
      typedef std::binary_function<First, Second, Result> base_type;

      /// First argument type
      TTCL_IMPORT_TYPE(base_type, first_argument_type);

      /// Second argument type
      TTCL_IMPORT_TYPE(base_type, second_argument_type);

      /// Result type
      TTCL_IMPORT_TYPE(base_type, result_type);

      /// Apply
      result_type
      operator()(const first_argument_type & _first,
                 const second_argument_type& _second) const {
        return _linear_kernel_impl<
          First, Second, Result>::apply(_first, _second);
      }
    };


    /// Is symmetric
    /** Specialization for adaptable_linear_kernel
     */
    template <typename First,
              typename Second,
              typename Result>
    struct is_symmetric< adaptable_linear_kernel<First, Second, Result> > :
      public boost::true_type {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
