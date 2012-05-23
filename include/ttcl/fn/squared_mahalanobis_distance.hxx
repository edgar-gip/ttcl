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

#ifndef TTCL_FN_SQUARED_MAHALANOBIS_DISTANCE_HXX
#define TTCL_FN_SQUARED_MAHALANOBIS_DISTANCE_HXX

/** @file
    Functions - Squared Mahalanobis distance
    @author Edgar Gonzàlez i Pellicer
*/

#include <algorithm>
#include <list>
#include <vector>

#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

#include <ttcl/assert.hxx>
#include <ttcl/global.hxx>
#include <ttcl/co/fortran_boost_matrix.hxx>
#include <ttcl/dt/traits.hxx>
#include <ttcl/in/_invert_matrix.hxx>
#include <ttcl/in/_mean_covariance.hxx>
#include <ttcl/fn/traits.hxx>
#include <ttcl/mf/coalesce.hxx>
#include <ttcl/mf/maximum_common_type.hxx>
#include <ttcl/ut/null_type.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {


    /// Squared Mahalanobis distance helper (for dense vectors)
    template <typename Result, typename Matrix>
    Result
    __squared_mahalanobis_distance(const std::vector<Result>& _difference,
                                   const Matrix& _isigma) {
      // Types
      TTCL_IMPORT_TYPE(std::vector<Result>, size_type);

      // Checks
      TTCL_ASSERT_EQ(_isigma.rows(), _isigma.cols());
      TTCL_ASSERT_GE(_difference.size(), _isigma.rows());

      // Sum
      Result sum = Result();

      // Follow
      for (size_type f_1 = 0; f_1 < _difference.size(); ++f_1)
        for (size_type f_2 = 0; f_2 < _difference.size(); ++f_2)
          sum += _isigma[f_1][f_2] * _difference[f_1] * _difference[f_2];

      // Return the sum
      return sum;
    }

    /// Squared Mahalanobis distance helper (for sparse vectors)
    template <typename Size, typename Result, typename Matrix>
    Result
    __squared_mahalanobis_distance(
        const std::list<std::pair<Size, Result> >& _difference,
        const Matrix& _isigma) {
      // Types
      typedef std::list<std::pair<Size, Result> > difference_type;
      TTCL_IMPORT_TYPE(difference_type, const_iterator);

      // Checks
      TTCL_ASSERT_EQ(_isigma.rows(), _isigma.cols());
      TTCL_ASSERT_GT(_difference.back().first, _isigma.rows());

      // Sum
      Result sum = Result();

      // Follow
      for (const_iterator it_1 = _difference.begin();
           it_1 != _difference.end(); ++it_1) {
        sum +=
            _isigma[it_1->first][it_1->first] * it_1->second * it_1->second;

        for (const_iterator it_2 = it_1; it_2 != _difference.end(); ++it_2) {
          sum +=
              _isigma[it_1->first][it_2->first] * it_1->second * it_2->second;
        }
      }

      // Return the sum
      return sum;
    }


    /// Squared Mahalanobis distance implementation
    template <typename First,
              typename Second,
              typename Result = ut::null_type,
              typename Matrix = co::fortran_boost_matrix<Result>,
              typename Enable = void>
    class _squared_mahalanobis_distance_impl;


    /// Squared Mahalanobis distance implementation
    /** Specialization for dense samples
     */
    template <typename First,
              typename Second,
              typename Result,
              typename Matrix>
    class _squared_mahalanobis_distance_impl<
      First, Second, Result, Matrix,
      typename boost::enable_if<
        boost::mpl::and_<
          dt::is_dense_sample<First>,
          dt::is_dense_sample<Second> > >::type> {
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
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename Matrix::element,
                                 effective_result_type> ));

    public:
      /// Apply
      static effective_result_type
      apply(const First&  _first, const Second& _second,
            const Matrix& _isigma) {
        // Types
        TTCL_IMPORT_TYPE(First, size_type);
        TTCL_IMPORT_R_TYPE(First,  const_iterator, first_iterator);
        TTCL_IMPORT_R_TYPE(Second, const_iterator, second_iterator);

        // Difference
        size_type lower    = std::min(_first.size(), _second.size());
        size_type features = std::max(_first.size(), _second.size());
        std::vector<effective_result_type> difference;
        difference.reserve(features);

        size_type f = 0;
        while (f < lower) {
          difference.push_back(_first[f] - _second[f]);
          ++f;
        }

        while (f < _first.size()) {
          difference.push_back(_first[f]);
          ++f;
        }

        while (f < _second.size()) {
          difference.push_back(-_second[f]);
          ++f;
        }

        // Find
        return __squared_mahalanobis_distance(difference, _isigma);
      }
    };


    /// Squared Mahalanobis distance
    /** Specialization for dense versus sparse samples
     */
    template <typename First,
              typename Second,
              typename Result,
              typename Matrix>
    class _squared_mahalanobis_distance_impl<
      First, Second, Result, Matrix,
      typename boost::enable_if<
        boost::mpl::and_<
          dt::is_dense_sample<First>,
          dt::is_sparse_sample<Second> > >::type> {
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
        (( boost::is_convertible<typename Second::value_type::second_type,
                                 effective_result_type> ));
      BOOST_MPL_ASSERT
        (( boost::is_convertible<typename Matrix::element,
                                 effective_result_type> ));

    public:
      /// Apply
      static effective_result_type
      apply(const First&  _first, const Second& _second,
            const Matrix& _isigma) {
        // Types
        TTCL_IMPORT_TYPE  (First,  size_type);
        TTCL_IMPORT_R_TYPE(First,  const_iterator, first_iterator);
        TTCL_IMPORT_R_TYPE(Second, const_iterator, second_iterator);

        // Sparse or dense?
        if (_first.size() >= _second.back().second + 1) {
          // Dense

          // Difference
          typedef std::vector<Result> difference_type;
          difference_type difference;
          difference.reserve(_first.size());

          uint f = 0;
          second_iterator it_s = _second.begin();
          while (f < _first.size()) {
            if (f == it_s->first) {
              difference.push_back(_first[f] - it_s->second);
              ++it_s;
            }
            else {
              difference.push_back(_first[f]);
            }

            ++f;
          }

          while (f < _first.size()) {
            difference.push_back(_first[f]);
            ++f;
          }

          // Find
          return __squared_mahalanobis_distance(difference, _isigma);
        }
        else {
          // Sparse

          // Difference
          typedef std::list< std::pair<size_type, Result> > difference_type;
          difference_type difference;

          uint f = 0;
          second_iterator it_s = _second.begin();
          while (f < _first.size()) {
            if (f == it_s->first) {
              difference.push_back(std::make_pair(f, _first[f] - it_s->second));
              ++it_s;
            }
            else {
              difference.push_back(std::make_pair(f, _first[f]));
            }

            ++f;
          }

          while (it_s != _second.end()) {
            difference.push_back(std::make_pair(it_s->first, -it_s->second));
            ++it_s;
          }

          // Find
          return __squared_mahalanobis_distance(difference, _isigma);
        }
      }
    };


    /// Squared Mahalanobis distance implementation
    /** Specialization for sparse versus dense samples
     */
    template <typename First,
              typename Second,
              typename Result,
              typename Matrix>
    class _squared_mahalanobis_distance_impl<
      First, Second, Result, Matrix,
      typename boost::enable_if<
        boost::mpl::and_<
          dt::is_sparse_sample<First>,
          dt::is_dense_sample<Second> > >::type> {
    public:
      // Effective result type
      typedef typename _squared_mahalanobis_distance_impl<
        Second, First, Result, Matrix>::effective_result_type
        effective_result_type;

    public:
      /// Apply
      static effective_result_type
      apply(const First&  _first, const Second& _second,
            const Matrix& _isigma) {
        // Use symmetry
        return _squared_mahalanobis_distance_impl<
          Second, First, Result, Matrix>::apply(_second, _first, _isigma);
      }
    };


    /// Squared Mahalanobis distance implementation
    /** Specialization for sparse samples
     */
    template <typename First,
              typename Second,
              typename Result,
              typename Matrix>
    class _squared_mahalanobis_distance_impl<
      First, Second, Result, Matrix,
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
      apply(const First&  _first, const Second& _second,
            const Matrix& _isigma) {
        // Types
        TTCL_IMPORT_TYPE(First, size_type);
        TTCL_IMPORT_R_TYPE(First,  const_iterator, first_iterator);
        TTCL_IMPORT_R_TYPE(Second, const_iterator, second_iterator);

        // Difference
        typedef std::list< std::pair<size_type, Result> > difference_type;
        difference_type difference;

        // Follow
        first_iterator  it_f = _first .begin();
        second_iterator it_s = _second.begin();
        while (it_f != _first.end() and it_s != _second.end()) {
          // What to do?
          if (it_f->first < it_s->first) {
            // Update and advance first
            difference.push_back(*it_f); // std::make_pair(it_f->first,
                                         //                it_f->second));
            ++it_f;
          }
          else if (it_f->first > it_s->first) {
            // Update and advance second
            difference.push_back(std::make_pair(it_s->first, -it_s->second));
            ++it_s;
          }
          else {
            // Update
            difference.push_back(std::make_pair(it_f->first,
                                                it_f->second - it_s->second));

            // Advance both
            ++it_f;
            ++it_s;
          }
        }

        // Something remains in first?
        while (it_f != _first.end()) {
          // Update and advance first
          difference.push_back(*it_f); // std::make_pair(it_f->first,
                                       //                it_f->second);
          ++it_f;
        }

        // Something remains in second?
        while (it_s != _second.end()) {
          // Update and advance second
          difference.push_back(std::make_pair(it_s->first, -it_s->second));
          ++it_s;
        }

        // Find
        return __squared_mahalanobis_distance(difference, _isigma);
      }
    };


    /// Squared Mahalanobis distance
    template <typename Result,
              typename Matrix = co::fortran_boost_matrix<Result> >
    class squared_mahalanobis_distance {
    public:
      /// Result type
      typedef Result result_type;

      /// Matrix type
      typedef Matrix matrix_type;

    private:
      /// Inverse covariance matrix
      matrix_type isigma_;

    public:
      /// Constructor from a matrix
      squared_mahalanobis_distance(const matrix_type& _isigma) :
        isigma_(_isigma) {
      }

      /// Copy constructor
      squared_mahalanobis_distance(const squared_mahalanobis_distance& _other) :
        isigma_(_other.isigma_) {
      }

      /// Constructor from a dataset
      template <typename Data>
      squared_mahalanobis_distance(const Data& _data) :
        isigma_(_data.features(), _data.features()) {
        // Find mean and covariance
        std::vector<Result> mu(_data.features());
        in::mean_covariance<Result, Data>::find(mu, isigma_, _data);

        // Invert covariance
        in::invert_hermitian_upper(isigma_);
      }

      /// Apply
      template <typename First, typename Second>
      typename _squared_mahalanobis_distance_impl<
        First, Second, Result>::effective_result_type
      operator()(const First& _first, const Second& _second) const {
        return _squared_mahalanobis_distance_impl<
          First, Second, Result>::apply(_first, _second, isigma_);
      }
    };


    /// Is symmetric
    /** Specialization for squared_mahalanobis_distance
     */
    template <typename Result>
    struct is_symmetric< squared_mahalanobis_distance<Result> > :
      public boost::true_type {
    };


    /// Adaptable squared Mahalanobis distance
    /** A model of Adaptable Binary Function
     */
    template <typename First,
              typename Second,
              typename Result>
    class adaptable_squared_mahalanobis_distance :
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
        return _squared_mahalanobis_distance_impl<
          First, Second, Result>::apply(_first, _second);
      }
    };


    /// Is symmetric
    /** Specialization for adaptable_squared_mahalanobis_distance
     */
    template <typename First,
              typename Second,
              typename Result>
    struct is_symmetric
      <adaptable_squared_mahalanobis_distance<First, Second, Result> > :
      public boost::true_type {
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
