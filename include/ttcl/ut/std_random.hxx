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

#ifndef TTCL_UT_STD_RANDOM_HXX
#define TTCL_UT_STD_RANDOM_HXX

/** @file
    Utility - Standard Random Number Generator
    @author Edgar Gonzàlez i Pellicer
*/

#include <cstdlib>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    // Standard random generator
    template <typename T>
    struct std_random;

    /// Standard Random Factory
    class std_random_factory {
    public:
      /// Apply
      template <typename T>
      struct apply {
        /// Result type
        typedef std_random<T> type;
      };

      /// Seed type
      typedef unsigned int seed_type;

      /// Set the seed
      static void
      set_seed(const seed_type _seed);

      /// Make
      template <typename T>
      std_random<T>
      make() const {
        return std_random<T>(*this);
      }

    protected:
      /// Generate
      static int
      generate();

      // Friend declarations
      template <typename T>
      friend class std_random;
    };

    /// Standard Random Generator
    /** A model of STL Adaptable Generator, Adaptable Unary Function
        and Random Number Generator
     */
    template <typename T>
    class std_random {
    public:
      /// Result type
      typedef T result_type;

      /// Argument type
      typedef T argument_type;

      /// Constructor
      /** From a factory
       */
      std_random(const std_random_factory& _factory) {
      }

      /// Generate a value
      /** Between 0 and 1
       */
      result_type
      operator()() {
        return result_type(std_random_factory::generate()
                           / (RAND_MAX + 1.0));
      }

      /// Generate a value
      /** Between 0 and max
       */
      result_type
      operator()(const argument_type _max) {
        return result_type(double(_max)
                           * std_random_factory::generate()
                           / (RAND_MAX + 1.0));
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
