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

#ifndef TTCL_CL_DENDROGRAM_HXX
#define TTCL_CL_DENDROGRAM_HXX

/** @file
    Clustering - Dendrogram
    @author Edgar Gonzàlez i Pellicer
*/

#include <map>
#include <stack>
#include <vector>

#include <boost/mpl/void.hpp>

#include <ttcl/assert.hxx>
#include <ttcl/types.hxx>
#include <ttcl/cl/hard_clustering.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Dendrogram
    /** @param T Value type
     */
    template <typename T = boost::mpl::void_>
    class dendrogram {
    public:
      /// Value type
      typedef T value_type;

      /// Size type
      typedef size_t size_type;

      /// Node Information
      struct node_info {
        /// Parent
        int parent;

        /// First child
        int first;

        /// Second child
        int second;

        /// Size
        value_type size;

        /// Distance at merge
        value_type distance;
      };

    private:
      /// Data
      std::vector<node_info> data_;

      /// Number of points
      size_type size_;

      /// Number of top clusters
      size_type clusters_;

    public:
      /// Constructor
      /** @param _size Number of points
       */
      dendrogram(size_type _size = 0) {
        // Reset to size
        reset(_size);
      }

      /// Get the number of points
      size_type
      size() const {
        // Size
        return size_;
      }

      /// Get the number of clusters
      size_type
      clusters() const {
        // Clusters
        return clusters_;
      }

      /// Get the number of branches
      size_type
      branches() const {
        // Branches
        return data_.size();
      }

      /// Reset
      /** @param _size Number of points
       */
      void
      reset(size_type _size) {
        // Fill the data with singletons
        data_.clear();
        data_.resize(_size);
        for (size_type i = 0; i < _size; ++i) {
          data_[i].parent   = -1;
          data_[i].first    = -1;
          data_[i].second   = -1;
          data_[i].size     = value_type(1);
          data_[i].distance = value_type();
        }

        // Remember the size
        size_     = _size;
        clusters_ = _size;
      }

      /// Merge
      /** @param _first First child
          @param _second Second child
          @param _distance Distance at merge
      */
      size_type
      merge(size_type _first, size_type _second,
            value_type _distance = value_type()) {
        // Not already merged
        TTCL_ASSERT_EQ(data_[_first ].parent, -1);
        TTCL_ASSERT_EQ(data_[_second].parent, -1);

        // Add the new node
        data_.push_back(node_info());
        size_type new_node = data_.size() - 1;

        // Link to the parent
        data_[_first ].parent   = new_node;
        data_[_second].parent   = new_node;

        // Fill parent information
        data_[new_node].parent   = -1;
        data_[new_node].first    = _first;
        data_[new_node].second   = _second;
        data_[new_node].size     =
          data_[_first].size + data_[_second].size;
        data_[new_node].distance = _distance;

        // One less cluster
        --clusters_;

        // Return the index of the new node
        return new_node;
      }

      /// Accessor
      /** @param _index Index
       */
      const node_info&
      operator[](size_type _index) const {
        return data_[_index];
      }

      /// Cut the dendrogram
      /** @param _clustering Target hard_clustering
          @param _n_clusters Number of clusters
      */
      template <typename Container>
      void
      cut_on(cl::hard_clustering<Container>& _clustering,
             size_type _n_clusters) const {
        // Check size
        TTCL_ASSERT_EQ(_clustering.size(), size_);

        // More clusters than data
        if (_n_clusters >= size_) {
          // Fill all
          for (size_type i = 0; i < size_; ++i)
            _clustering[i] = i;
          _clustering.set_clusters(size_);
          return;
        }

        // Selected clusters
        std::map<size_type, size_type> selection;
        size_type selected_clusters = 0;

        // Special case of a single node
        if (clusters_ == 1) {
          // One node
          selection.insert(std::make_pair(data_.size() - 1,
                                          selected_clusters++));
        }
        else {
          // Find the orphaned ones
          for (size_type i = 0; i < data_.size(); ++i)
            if (data_[i].parent == -1)
              selection.insert(std::make_pair(i, selected_clusters++));
        }

        // Is the tree joint enough?
        while (selected_clusters < _n_clusters) {
          // Find the last one
          std::map<size_type, size_type>::iterator it = selection.end(); --it;
          size_type idx = it->first;

          // Insert the two children
          selection.insert(std::make_pair(data_[idx].first,  it->second));
          selection.insert(std::make_pair(data_[idx].second,
                                          selected_clusters++));

          // Remove the parent
          selection.erase(it);
        }

        // Mark them
        for (std::map<size_type, size_type>::iterator it = selection.begin();
             it != selection.end(); ++it) {
          // Stack
          std::stack<size_type> pending;
          pending.push(it->first);

          // Empty?
          while (not pending.empty()) {
            // Top
            size_type top = pending.top();
            pending.pop();

            // Leaf or branch?
            if (top < size_) {
              // Mark
              _clustering[top] = it->second;
            }
            else {
              // Add the children
              pending.push(data_[top].first);
              pending.push(data_[top].second);
            }
          }
        }

        // Set
        _clustering.set_clusters(selected_clusters);
      }

      /// Cut the dendrogram
      /** Functional convenience version
          @param _n_clusters
      */
      cl::hard_clustering<>
      cut(size_type _n_clusters) const {
        // Build and return
        cl::hard_clustering<> ret(size_);
        cut_on(ret, _n_clusters);
        return ret;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
