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

#ifndef TTCL_FN_CROSS_APPLY_HXX
#define TTCL_FN_CROSS_APPLY_HXX

/** @file
    Functions - Cross-apply a function
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>

#include <ttcl/global.hxx>
#include <ttcl/co/traits.hxx>
#include <ttcl/fn/traits.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Functions Namespace
  namespace fn {

    // Pre-declarations
    template <typename SeqA, typename SeqB, typename Function>
    class cross_apply_thunk;

    template <typename SeqA, typename SeqB, typename Function>
    cross_apply_thunk<SeqA, SeqB, Function>
    cross_apply(const SeqA& _seqA, const SeqB& _seqB,
                const Function& _function);


    /// Function cross-application calculation thunk
    template <typename SeqA, typename SeqB, typename Function>
    class cross_apply_thunk {
    private:
      /// Sequence A
      const SeqA& seqA_;

      /// Sequence B
      const SeqB& seqB_;

      /// Function
      const Function& function_;

      /// Constructor
      cross_apply_thunk(const SeqA& _seqA,
                        const SeqB& _seqB,
                        const Function& _function) :
        seqA_(_seqA), seqB_(_seqB), function_(_function) {
      }

    public:
      /// Convert to matrix
      /** Effective calculation
       */
      template <typename Matrix>
      operator Matrix() const {
        // Types
        TTCL_IMPORT_R_TYPE(Matrix, element, value_type);

        // Create the output (and reset)
        Matrix output(seqA_.size(), seqB_.size(), value_type());

        // Fill matrix
        fill_matrix(output);

        // Return
        return output;
      }

    private:
      /// Fill the matrix
      template <typename Matrix>
      void
      fill_matrix(Matrix& _output) const {
        // Types
        TTCL_IMPORT_TYPE  (Matrix, size_type);
        TTCL_IMPORT_R_TYPE(SeqA, const_iterator, seqA_iterator);
        TTCL_IMPORT_R_TYPE(SeqB, const_iterator, seqB_iterator);

        // Fill
        size_type i = 0;
        for (seqA_iterator it_a = seqA_.begin();
             it_a != seqA_.end(); ++it_a, ++i) {
          size_type j = 0;
          for (seqB_iterator it_b = seqB_.begin();
               it_b != seqB_.end(); ++it_b, ++j)
            _output[i][j] = function_(*it_a, *it_b);
        }
      }

      // Friend
      friend cross_apply_thunk
      cross_apply<SeqA, SeqB, Function>(const SeqA& _seqA,
                                          const SeqB& _seqB,
                                          const Function& _function);
    };


    /// Calculate function matrix
    template <typename SeqA, typename SeqB, typename Function>
    cross_apply_thunk<SeqA, SeqB, Function>
    cross_apply(const SeqA& _seqA, const SeqB& _seqB,
                const Function& _function) {
      return
        cross_apply_thunk<SeqA, SeqB, Function>(_seqA, _seqB, _function);
    }


    // Pre-declarations
    template <typename Seq, typename Function>
    class cross_self_apply_thunk;

    template <typename Seq, typename Function>
    cross_self_apply_thunk<Seq, Function>
    cross_apply(const Seq& _seq, const Function& _function);


    /// Function cross-self-application calculation thunk
    template <typename Seq, typename Function>
    class cross_self_apply_thunk {
    private:
      /// Sequence
      const Seq& seq_;

      /// Function
      const Function& function_;

      /// Constructor
      cross_self_apply_thunk(const Seq& _seq,
                             const Function& _function) :
        seq_(_seq), function_(_function) {
      }

    public:
      /// Convert to matrix
      /** Effective calculation
       */
      template <typename Matrix>
      operator Matrix() const {
        // Types
        TTCL_IMPORT_TYPE(Matrix, size_type);
        TTCL_IMPORT_TYPE(Matrix, value_type);

        // Create the output (and reset)
        size_type size = seq_.size();
        Matrix output(size, size, value_type());

        // Fill matrix
        fill_matrix(output);

        // Return
        return output;
      }

    private:
      /// Fill the matrix
      template <typename Matrix>
      void
      fill_matrix(Matrix& _output,
                  typename boost::enable_if<
                    boost::mpl::and_<
                      boost::mpl::not_<
                        boost::mpl::or_<
                          co::is_hollow_symmetric_matrix<Matrix>,
                          co::is_full_symmetric_matrix<Matrix>
                        >
                      >,
                      boost::mpl::not_<
                        is_symmetric<Function>
                      >
                    >
                  >::type* /* _dummy */ = 0) const {
        // Types
        TTCL_IMPORT_TYPE  (Matrix, size_type);
        TTCL_IMPORT_R_TYPE(Seq, const_iterator, seq_iterator);

        // Fill
        size_type i = 0;
        for (seq_iterator it_i = seq_.begin();
             it_i != seq_.end(); ++it_i, ++i) {
          size_type j = 0;
          for (seq_iterator it_j = seq_.begin();
               it_j != it_i; ++it_j, ++j) {
            _output[i][j] = function_(*it_i, *it_j);
            _output[j][i] = function_(*it_j, *it_i);
          }
          _output[i][i] = function_(*it_i, *it_i);
        }
      }

      /// Fill the matrix
      /** Specialization for symmetric functions
       */
      template <typename Matrix>
      void
      fill_matrix(Matrix& _output,
                  typename boost::enable_if<
                    boost::mpl::and_<
                      boost::mpl::not_<
                        boost::mpl::or_<
                          co::is_hollow_symmetric_matrix<Matrix>,
                          co::is_full_symmetric_matrix<Matrix>
                        >
                      >,
                      is_symmetric<Function>
                    >
                  >::type* /* _dummy */ = 0) const {
        // Types
        TTCL_IMPORT_TYPE  (Matrix, size_type);
        TTCL_IMPORT_R_TYPE(Seq, const_iterator, seq_iterator);

        // Fill
        size_type i = 0;
        for (seq_iterator it_i = seq_.begin();
             it_i != seq_.end(); ++it_i, ++i) {
          size_type j = 0;
          for (seq_iterator it_j = seq_.begin();
               it_j != it_i; ++it_j, ++j)
            _output[i][j] = _output[j][i] = function_(*it_i, *it_j);
          _output[i][i] = function_(*it_i, *it_i);
        }
      }

      /// Fill the matrix
      /** Specialization for full symmetric matrix
       */
      template <typename Matrix>
      void
      fill_matrix(Matrix& _output,
                  typename boost::enable_if<
                    co::is_full_symmetric_matrix<Matrix>
                  >::type* /* _dummy */ = 0) const {
        // Asserts
        BOOST_STATIC_ASSERT(fn::is_symmetric<Function>::value);

        // Types
        TTCL_IMPORT_R_TYPE(Matrix, data_iterator, matrix_iterator);
        TTCL_IMPORT_R_TYPE(Seq, const_iterator, seq_iterator);

        // Fill
        matrix_iterator it_m = _output.data_begin();
        for (seq_iterator it_i = seq_.begin();
             it_i != seq_.end(); ++it_i) {
          for (seq_iterator it_j = seq_.begin();
               it_j != it_i; ++it_j)
            *it_m++ = function_(*it_i, *it_j);
          *it_m++ = function_(*it_i, *it_i);
        }
      }

      /// Fill the matrix
      /** Specialization for hollow symmetric matrix
       */
      template <typename Matrix>
      void
      fill_matrix(Matrix& _output,
                  typename boost::enable_if<
                    co::is_hollow_symmetric_matrix<Matrix>
                  >::type* /* _dummy */ = 0) const {
        // Asserts
        BOOST_STATIC_ASSERT(fn::is_symmetric<Function>::value);

        // Types
        TTCL_IMPORT_R_TYPE(Matrix, data_iterator, matrix_iterator);
        TTCL_IMPORT_R_TYPE(Seq, const_iterator, seq_iterator);

        // Fill
        matrix_iterator it_m = _output.data_begin();
        for (seq_iterator it_i = seq_.begin();
             it_i != seq_.end(); ++it_i)
          for (seq_iterator it_j = seq_.begin();
               it_j != it_i; ++it_j)
            *it_m++ = function_(*it_i, *it_j);
      }

      // Friend
      friend cross_self_apply_thunk
      cross_apply<Seq, Function>(const Seq& _seq,
                                 const Function& _function);
    };


    /// Calculate function matrix
    template <typename Seq, typename Function>
    cross_self_apply_thunk<Seq, Function>
    cross_apply(const Seq& _seq, const Function& _function) {
      return cross_self_apply_thunk<Seq, Function>(_seq, _function);
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
