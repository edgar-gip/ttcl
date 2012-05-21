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

#ifndef TTCL_TU_TUNING_HXX
#define TTCL_TU_TUNING_HXX

/** @file
    Utilities - Options and Tuning
    @author Edgar Gonzàlez i Pellicer
*/

#include <vector>

#include <ttcl/exception.hxx>
#include <ttcl/types.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Tuning Namespace
  namespace tu {

    /// Option
    /** Heavily based on std::locale::facet

        Children must have an option_id id field
     */
    class option {
    private:
      /// Number of references
      uint refs_;

    protected:
      /// Constructor
      explicit option(int _refs = 0);

      /// Destructor
      virtual
      ~option();

      // Friends
      friend class tuning;
      friend struct tuning_imp;
    };

    /// Option id
    /** Heavily based on std::locale::facet::id
     */
    class option_id {
    private:
      /// The index
      uint index_;

      /// Number of ids
      static uint total_;

    public:
      /// Constructor
      option_id();

      // Friend declarations
      friend class option;
      friend class tuning;
    };

    /// Tuning implementation
    /** Heavily based on std::locale::imp
     */
    struct tuning_imp {
      /// Number of references
      uint refs_;

      /// Options
      std::vector<option*> options_;

      /// Default constructor
      tuning_imp();

      /// Copy constructor
      tuning_imp(const tuning_imp& _other);

      /// Destructor
      ~tuning_imp();
    };

    /// Tuning
    /** Heavily based on std::locale
     */
    class tuning {
    private:
      /// Implementation
      tuning_imp* imp_;

      /// Default implementation
      static tuning_imp default_imp_;

    public:
      /// Default constructor
      tuning();

      /// Copy constructor
      /** @param _other Source tuning
       */
      tuning(const tuning& _other);

      /// Destructor
      ~tuning();

      /// Assignment operator
      /** @param _other Source tuning
       */
      tuning&
      operator=(const tuning& _other);

      /// Add an option
      /** @param _opt Option
       */
      template <class Option>
      tuning&
      set(Option* _opt);

      /// Remove an option
      template <class Option>
      void
      remove();

      /// Retrieve an option
      template <class Option>
      const Option&
      get() const;
    };

    /// Add an option
    /** @param _opt Option
     */
    template <class Option>
    tuning& tuning::
    set(Option* _opt) {
      // Sharing the implementation?
      if (imp_->refs_ > 1) {
        // Detach
        tuning_imp* new_imp = new tuning_imp(*imp_);
        --imp_->refs_;
        imp_ = new_imp;
      }

      // Get the option index
      uint index = Option::id_.index_;
      if (not index)
        // Set a new one
        index = Option::id_.index_ = ++option_id::total_;

      // Do we have place?
      if (index >= imp_->options_.size())
        imp_->options_.resize(index, 0);

      // Something to replace?
      if (imp_->options_[index - 1] and
          --imp_->options_[index - 1]->refs_ == 0)
        delete imp_->options_[index - 1];

      // Save it
      imp_->options_[index - 1] = _opt;
      ++_opt->option::refs_;

      // Return this
      return *this;
    }

    /// Remove an option
    template <class Option>
    void tuning::
    remove() {
      // Look for it
      uint index = Option::id_.index_;
      if (index - 1 < imp_->options_.size() and
          imp_->options_[index - 1]) {
        if (--imp_->options_[index - 1]->refs_ == 0)
          delete imp_->options_[index - 1];
        imp_->options_[index - 1] = 0;
      }
    }

    /// Retrieve an option
    template <class Option>
    const Option& tuning::
    get() const {
      // Get the option index
      uint index = Option::id_.index_;
      if (not index)
        // Set a new one
        index = Option::id_.index_ = ++option_id::total_;

      // Do we have place?
      if (index >= imp_->options_.size())
        imp_->options_.resize(index, 0);

      // Is it null?
      if (not imp_->options_[index - 1]) {
        // Does the default have place?
        if (index >= default_imp_.options_.size())
          default_imp_.options_.resize(index, 0);

        // Is it null?
        if (not default_imp_.options_[index - 1]) {
          default_imp_.options_[index - 1] =
            new Option(Option::default_value());
          ++default_imp_.options_[index - 1]->refs_;
        }

        // Copy and set
        imp_->options_[index - 1] =
          default_imp_.options_[index - 1];
        ++imp_->options_[index - 1]->refs_;
      }

      // Cast it
      return static_cast<const Option&>(*(imp_->options_[index - 1]));
    }
  }
}

/// Define an option
#define TTCL_TU_OPTION(type, name, default)     \
  class name :                                  \
    public ttcl::tu::option {                   \
  public:                                       \
    typedef type value_type;                    \
                                                \
    static ttcl::tu::option_id id_;             \
                                                \
    static type default_value() {               \
      return default;                           \
    }                                           \
                                                \
  private:                                      \
    value_type value_;                          \
                                                \
  public:                                       \
    name(value_type _value = type(0)) :         \
      value_(_value) {                          \
    }                                           \
                                                \
    operator value_type() const {               \
      return value_;                            \
    }                                           \
  };

/// Generic static
#define TTCL_TU_STATIC                                  \
  ttcl::uint ttcl::tu::option_id::total_;               \
  ttcl::tu::tuning_imp ttcl::tu::tuning::default_imp_;

/// Option static vars
#define TTCL_TU_OPTION_STATIC(name)             \
  ttcl::tu::option_id name::id_;

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
