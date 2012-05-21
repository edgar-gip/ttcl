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

#include <ttcl/tu/tuning.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl::tu;

// Option

/// Constructor
option::
option(int _refs) :
  refs_(_refs) {
}

/// Destructor
option::
~option() {
}

// Option id

/// Number of ids
ttcl::uint option_id::total_;

/// Constructor
option_id::
option_id() {
}

// Tuning implementation

/// Default constructor
tuning_imp::
tuning_imp() :
  refs_(1) {
}

/// Copy constructor
tuning_imp::
tuning_imp(const tuning_imp& _other) :
  refs_(1) {
  // Copy every option
  for (std::vector<option*>::const_iterator it =
         _other.options_.begin();
       it != _other.options_.end(); ++it) {
    options_.push_back(*it);
    if (*it)
      ++(*it)->refs_;
  }
}

/// Destructor
tuning_imp::
~tuning_imp() {
  // Free every option
  for (std::vector<option*>::iterator it = options_.begin();
       it != options_.end(); ++it)
    if (*it and --(*it)->refs_ == 0)
      delete *it;
}

// Tuning

/// Default implementation
tuning_imp tuning::default_imp_;

/// Default constructor
tuning::
tuning() :
  imp_(&default_imp_) {
  // One more reference
  ++default_imp_.refs_;
}

/// Copy constructor
/** @param _other Source tuning
 */
tuning::
tuning(const tuning& _other) :
  imp_(_other.imp_) {
  // One more reference
  ++imp_->refs_;
}

/// Destructor
tuning::
~tuning() {
  // Free the implementation
  if (--imp_->refs_ == 0)
    delete imp_;
}

/// Assignment operator
/** @param _other Source tuning
 */
tuning& tuning::
operator=(const tuning& _other) {
  // Check it's not the same
  if (imp_ != _other.imp_) {
    // Free the current one
    if (--imp_->refs_ == 0)
      delete imp_;

    // Assign and increase
    imp_ = _other.imp_;
    ++imp_->refs_;
  }

  // Return this
  return *this;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
