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

#ifndef TTCL_UT_REENTRANT_RANDOM_HXX
#define TTCL_UT_REENTRANT_RANDOM_HXX

/** @file
    Utility - Reentrant Random Number Generator
    @author Edgar Gonzàlez i Pellicer
*/

#include <boost/intrusive_ptr.hpp>

#include <ttcl/types.hxx>
#include <ttcl/tu/choices.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    // Reentrant random generator
    template <typename T>
    class reentrant_random;

    /// Reentrant seed block
    class reentrant_seed_block;

    /// Reentrant random generator factory
    class reentrant_random_factory {
    public:
      /// Apply
      template <typename T>
      struct apply {
        /// Result type
        typedef reentrant_random<T> type;
      };

      /// Seed type
      typedef unsigned int seed_type;

    private:
      /// Block
      boost::intrusive_ptr<reentrant_seed_block> block_;

    public:
      /// Constructor
      explicit
      reentrant_random_factory(const seed_type _seed);

      /// Reset the seed
      void
      reset(const seed_type _seed);

      /// Detach
      void
      detach();

      /// Make
      template <typename T>
      reentrant_random<T>
      make() const {
        return reentrant_random<T>(*this);
      }

    protected:
      /// Generate
      static int
      generate(reentrant_seed_block& _block);

      // Friend declarations
      template <typename T>
      friend class reentrant_random;
    };

    /// Remove a
    /// Reentrant Random Generator
    /** A model of STL Adaptable Generator, Adaptable Unary Function
        and Random Number Generator
     */
    template <typename T>
    class reentrant_random {
    public:
      /// Result type
      typedef T result_type;

      /// Argument type
      typedef T argument_type;

    private:
      /// Block
      boost::intrusive_ptr<reentrant_seed_block> block_;

    public:
      /// Constructor
      /** From a factory
       */
      reentrant_random(const reentrant_random_factory& _other) :
        block_(_other.block_) {
      }

      /// Generate a value
      /** Between 0 and 1
       */
      result_type
      operator()() {
        return result_type(reentrant_random_factory::generate(*block_)
                           / (RAND_MAX + 1.0));
      }

      /// Generate a value
      /** Between 0 and max
       */
      result_type
      operator()(const argument_type _max) {
        return result_type(double(_max)
                           * reentrant_random_factory::generate(*block_)
                           / (RAND_MAX + 1.0));
      }
    };

    /// Add a reference
    void
    intrusive_ptr_add_ref(reentrant_seed_block* _ptr);

    /// Release
    void
    intrusive_ptr_release(reentrant_seed_block* _ptr);
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
