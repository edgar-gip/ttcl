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

#ifndef TTCL_UT_INDEXED_COMPARE_HXX
#define TTCL_UT_INDEXED_COMPARE_HXX

/** @file
    Utilities - Indexed compare
    @author Edgar Gonzalez i Pellicer
*/

#include <functional>
#include <map>
#include <vector>

#include <boost/call_traits.hpp>

#include <ttcl/global.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Utility Namespace
  namespace ut {

    /// Indexed compare class for sequences
    template <typename Container,
              typename Ordering = std::less<typename Container::value_type> >
    class _sequence_indexed_compare {
    public:
      /// Container type
      typedef Container container_type;

      /// Key type
      TTCL_IMPORT_R_TYPE(container_type, size_type, key_type);

      /// Ordering type
      typedef Ordering ordering_type;

      /// Parameter type
      TTCL_IMPORT_TYPE(boost::call_traits<key_type>, param_type);

    private:
      /// Reference to the container
      const container_type& container_;

      /// Ordering
      const ordering_type ordering_;

    public:
      /// Constructor
      _sequence_indexed_compare(const container_type& _container,
                                const ordering_type& _ordering =
                                  ordering_type()) :
        container_(_container), ordering_(_ordering) {
      }

      /// Compare
      bool
      operator()(param_type _a, param_type _b) const {
        return ordering_(container_[_a], container_[_b]);
      }
    };

    // Make an indexed compare for vector
    template <typename Data, typename Alloc, typename Ordering>
    _sequence_indexed_compare<std::vector<Data, Alloc>, Ordering>
    indexed_compare(const std::vector<Data, Alloc>& _container,
                    const Ordering& _ordering) {
      return _sequence_indexed_compare<std::vector<Data, Alloc>,
        Ordering>(_container, _ordering);
    }

    // Make an indexed compare for vector
    template <typename Data, typename Alloc>
    _sequence_indexed_compare<std::vector<Data, Alloc> >
    indexed_compare(const std::vector<Data, Alloc>& _container) {
      return _sequence_indexed_compare<std::vector<Data, Alloc> >(_container);
    }

    /// Indexed compare class for associaciative containers
    template <typename Container,
              typename Ordering = std::less<typename Container::data_type> >
    class _associative_indexed_compare {
    public:
      /// Container type
      typedef Container container_type;

      /// Key type
      TTCL_IMPORT_TYPE(container_type, key_type);

      /// Ordering type
      typedef Ordering ordering_type;

      /// Parameter type
      TTCL_IMPORT_TYPE(boost::call_traits<key_type>, param_type);

    private:
      /// Reference to the container
      const container_type& container_;

      /// Ordering
      const ordering_type ordering_;

    public:
      /// Constructor
      _associative_indexed_compare(const container_type& _container,
                                   const ordering_type& _ordering =
                                     ordering_type()) :
        container_(_container), ordering_(_ordering) {
      }

      /// Compare
      bool
      operator()(param_type _a, param_type _b) const {
        // Check both are defined
        typename container_type::const_iterator it_a =
          container_.find(_a);
        if (it_a != container_.end()) {
          typename container_type::const_iterator it_b =
            container_.find(_b);
          if (it_b != container_.end())
            return ordering_(it_a->second, it_b->second);
        }

        // Comparisons to undefined always yield false
        return false;
      }
    };

    // Make an indexed compare for a map
    template <typename Key, typename Data, typename Compare, typename Alloc,
              typename Ordering>
    _associative_indexed_compare<std::map<Key, Data, Compare, Alloc>, Ordering>
    indexed_compare(const std::map<Key, Data, Compare, Alloc>& _container,
                    const Ordering& _ordering) {
      return _associative_indexed_compare<std::map<Key, Data, Compare, Alloc>,
                                         Ordering>(_container, _ordering);
    }

    // Make an indexed compare for a map
    template <typename Key, typename Data, typename Compare, typename Alloc>
    _associative_indexed_compare<std::map<Key, Data, Compare, Alloc> >
    indexed_compare(const std::map<Key, Data, Compare, Alloc>& _container) {
      return _associative_indexed_compare<
        std::map<Key, Data, Compare, Alloc> >(_container);
    }
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
