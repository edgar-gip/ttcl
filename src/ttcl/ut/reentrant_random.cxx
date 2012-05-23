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

#include <ttcl/ut/reentrant_random.hxx>

#include <cstdlib>
#include <cstring>

#include <ttcl/c++11.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl::ut;

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Reentrant seed block
    class reentrant_seed_block {
    private:
      /// Seed
      reentrant_random_factory::seed_type seed_;

      /// State size
      static const int STATE_SIZE = 256;

      /// State
      char state_[STATE_SIZE];

      /// Data
      struct random_data data_;

      /// References
      uint references_;

    public:
      /// Constructor
      reentrant_seed_block(reentrant_random_factory::seed_type _seed,
                           uint _references = 0);

      /// Copy constructor
      reentrant_seed_block(const reentrant_seed_block& _other);

    private:
      /// Assignment operator
      reentrant_seed_block&
      operator=(const reentrant_seed_block& _other) TTCL_DELETE;

    public:
      /// Data
      const random_data&
      data() const;

      /// Data pointer
      random_data*
      data_ptr();

      /// Reset the seed
      void
      reset(const reentrant_random_factory::seed_type _seed);

      /// Add reference
      void
      add_reference();

      /// Del reference
      void
      del_reference();
    };
  }
}

// Reentrant seed block

/// Constructor
reentrant_seed_block::
reentrant_seed_block(reentrant_random_factory::seed_type _seed,
                     uint _references) :
  seed_(_seed), references_(_references) {
  memset(&data_, 0, sizeof(random_data));
  initstate_r(seed_, state_, STATE_SIZE, &data_);
}

/// Copy constructor
/** @bug Uses knowledge of the internals of the std::random_data type
 */
reentrant_seed_block::
reentrant_seed_block(const reentrant_seed_block& _other) :
  seed_(_other.seed_), references_(0) {
  memcpy(state_, _other.state_, STATE_SIZE);

  data_.rand_type = _other.data_.rand_type;
  data_.rand_sep  = _other.data_.rand_sep;
  data_.rand_deg  = _other.data_.rand_deg;

  data_.state     = 1 + reinterpret_cast<int32_t*>(state_);
  data_.end_ptr   = &data_.state[data_.rand_deg];

  data_.fptr      = data_.state + (_other.data_.fptr - _other.data_.state);
  data_.rptr      = data_.state + (_other.data_.rptr - _other.data_.state);
}

/// Data
const random_data& reentrant_seed_block::
data() const {
  return data_;
}

/// Data pointer
random_data* reentrant_seed_block::
data_ptr() {
  return &data_;
}

/// Reset the seed
void reentrant_seed_block::
reset(const reentrant_random_factory::seed_type _seed) {
  srandom_r(_seed, &data_);
}

/// Add reference
void reentrant_seed_block::
add_reference() {
  ++references_;
}

/// Del reference
void reentrant_seed_block::
del_reference() {
  if (--references_ == 0)
    delete this;
}

// Reentrant Random Generator Base Class

/// Constructor
/** Using a certain value
 */
reentrant_random_factory::
reentrant_random_factory(const seed_type _seed) :
  block_(new reentrant_seed_block(_seed)) {
}

/// Reset the seed
void reentrant_random_factory::
reset(const seed_type _seed) {
  block_->reset(_seed);
}

/// Detach
void reentrant_random_factory::
detach() {
  block_ = new reentrant_seed_block(*block_);
}

/// Generate
int reentrant_random_factory::
generate(reentrant_seed_block& _block) {
  int result;
  random_r(_block.data_ptr(), &result);
  return result;
}

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Add a reference
    void
    intrusive_ptr_add_ref(reentrant_seed_block* _ptr) {
      _ptr->add_reference();
    }

    /// Release
    void
    intrusive_ptr_release(reentrant_seed_block* _ptr) {
      _ptr->del_reference();
    }
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
