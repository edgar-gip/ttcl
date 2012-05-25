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

#ifndef TTCL_CL_HARD_CLUSTERING_HXX
#define TTCL_CL_HARD_CLUSTERING_HXX

/** @file
    Clustering - Hard clustering results
    @author Edgar Gonzàlez i Pellicer
*/

#include <map>
#include <vector>

#include <ttcl/exception.hxx>
#include <ttcl/global.hxx>
#include <ttcl/cl/soft_clustering.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Soft clustering results
    template < typename Container >
    class soft_clustering;

    /// Hard clustering results
    /** @tparam Container Underlying container
     */
    template < typename Container = std::vector<int> >
    class hard_clustering :
      public Container {
    private:
      /// Base type
      typedef Container base_type;

    public:
      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

    private:
      /// Number of clusters
      value_type clusters_;

    public:
      /// Default constructor
      hard_clustering() :
        base_type(), clusters_(0) {
      }

      /// Constructor
      /** @param _size Size
          @param _clusters Number of clusters
      */
      hard_clustering(size_type _size,
                      value_type _clusters = 0) :
        base_type(_size), clusters_(_clusters) {
      }

      /// Copy constructor
      /** @param _other Source hard_clustering
       */
      hard_clustering(const hard_clustering& _other) :
        base_type(_other), clusters_(_other.clusters_) {
      }

      /// Conversion constructor
      /** @param _other Source soft_clustering
       */
      template <typename Cont>
      hard_clustering(const soft_clustering<Cont>& _other) :
        base_type(_other.samples()), clusters_(_other.clusters()) {
        // Set each
        for (size_type row = 0; row < this->size(); ++row) {
          // Set to the most probable cluster
          (*this)[row] = _other.mpc(row);
        }
      }

      /// Assignment operator
      /** @param _other Source hard_clustering
       */
      hard_clustering& operator=(const hard_clustering& _other) {
        // Assign as a container
        this->base_type::operator=(_other);
        clusters_ = _other.clusters_;

        // Return this
        return *this;
      }

      /// Assignment operator
      /** @param _other Source soft_clustering
       */
      template <typename Cont>
      hard_clustering& operator=(const soft_clustering<Cont>& _other) {
        // Resize
        this->resize(_other.samples());
        clusters_ = _other.clusters();

        // Set each
        for (size_type row = 0; row < this->size(); ++row) {
          // Set to the most probable cluster
          (*this)[row] = _other.mpc(row);
        }

        // Return this
        return *this;
      }

      /// Resize
      /** @param _size Size
      */
      void resize(const size_type _size) {
        // Resize the base
        base_type::resize(_size, value_type(-1));
      }

      /// Resize
      /** @param _size Size
          @param _clusters Number of clusters
          @warning No checking is done
      */
      void resize(const size_type _size,
                  const size_type _clusters) {
        // Resize the base, and update the clusters
        base_type::resize(_size, value_type(-1));
        clusters_ = _clusters;
      }

      /// Number of samples
      size_type
      samples() const {
        return this->size();
      }

      /// Number of clusters
      value_type clusters() const {
        return clusters_;
      }

      /// Manually set the number of clusters
      /** @param _clusters Number of clusters
          @warning No checking is done
      */
      void set_clusters(value_type _clusters) {
        clusters_ = _clusters;
      }

      /// Update the number of clusters
      value_type update_clusters() {
        // Find the largest one
        value_type max_cluster = value_type(-1);
        for (typename base_type::const_iterator it = this->begin();
             it != this->end(); ++it)
          if (*it > max_cluster)
            max_cluster = *it;

        // Return the updated number
        return (clusters_ = max_cluster + 1);
      }

      /// Reindex the clusters
      value_type reindex_clusters() {
        // New index
        value_type n_clusters = 0;
        std::map<value_type, value_type> reindex;

        // Follow
        for (typename base_type::iterator it = this->begin();
             it != this->end(); ++it) {
          // Defined?
          if (*it != value_type(-1)) {
            // Look it up
            typename std::map<value_type, value_type>::iterator rit =
              reindex.find(*it);
            if (rit == reindex.end())
              // Add it
              rit = reindex.insert(std::make_pair(*it, n_clusters++)).first;

            // Change it
            *it = rit->second;
          }
        }

        // Return the updated number
        return (clusters_ = n_clusters);
      }

      /// Cluster sizes
      std::vector<size_type> cluster_sizes() const {
        // Result vector
        std::vector<size_type> result(clusters_, size_type(0));

        // For each one
        for (typename base_type::const_iterator it = this->begin();
             it != this->end(); ++it)
          if (*it != value_type(-1))
            ++result[*it];

        // Return them
        return result;
      }
    };
  }
}

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
