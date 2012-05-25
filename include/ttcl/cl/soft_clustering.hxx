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

#ifndef TTCL_CL_SOFT_CLUSTERING_HXX
#define TTCL_CL_SOFT_CLUSTERING_HXX

/** @file
    Clustering - Soft clustering results
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl/exception.hxx>
#include <ttcl/global.hxx>
#include <ttcl/cl/hard_clustering.hxx>
#include <ttcl/co/matrix.hxx>

/// TTCL Namespace
namespace ttcl {

  /// Clustering Namespace
  namespace cl {

    /// Hard clustering results
    template < typename Container >
    class hard_clustering;

    /// Soft clustering results
    /** @tparam Container Underlying container
     */
    template < typename Container = co::matrix<double> >
    class soft_clustering :
      public Container {
    private:
      /// Base type
      typedef Container base_type;

    public:
      /// Value type
      TTCL_IMPORT_TYPE(base_type, value_type);

      /// Size type
      TTCL_IMPORT_TYPE(base_type, size_type);

      /// Default constructor
      soft_clustering() :
        base_type() {
      }

      /// Constructor
      /** @param _size Size
          @param _clusters Number of clusters
      */
      soft_clustering(size_type _size,
                      size_type _clusters) :
        base_type(_size, _clusters) {
      }

      /// Copy constructor
      /** @param _other Source soft_clustering
       */
      soft_clustering(const soft_clustering& _other) :
        base_type(static_cast<const base_type&>(_other)) {
      }

      /// Conversion constructor
      /** @param _other Source hard_clustering
       */
      template <typename Cont>
      soft_clustering(const hard_clustering<Cont>& _other) :
        base_type(_other.size(), _other.clusters()) {
        // Other value type
        typedef typename hard_clustering<Cont>::value_type other_value_type;

        // Set each
        for (size_type r = 0; r < samples(); ++r)
          for (size_type cl = 0; cl < clusters(); ++cl)
            (*this)[r][cl] =
              (_other[r] == other_value_type(cl) ? 1 : 0);
      }

      /// Assignment operator
      /** @param _other Source soft_clustering
       */
      soft_clustering&
      operator=(const soft_clustering& _other) {
        // Resize
        this->resize(_other.size(), _other.clusters());

        // Assign as a container
        this->base_type::operator=(_other);

        // Return this
        return *this;
      }

      /// Assignment operator
      /** @param _other Source soft_clustering
       */
      template <typename Cont>
      soft_clustering&
      operator=(const hard_clustering<Cont>& _other) {
        // Other value type
        typedef typename hard_clustering<Cont>::value_type other_value_type;

        // Resize
        this->resize(_other.size(), _other.clusters());

        // Set each
        for (size_type r = 0; r < samples(); ++r)
          for (size_type cl = 0; cl < clusters(); ++cl)
            (*this)[r][cl] =
              (_other[r] == other_value_type(cl) ? 1 : 0);

        // Return this
        return *this;
      }

      /// Number of samples
      size_type
      samples() const {
        return this->rows();
      }

      /// Number of clusters
      size_type
      clusters() const {
        return this->columns();
      }

      /// Most probable cluster
      ssize_t
      mpc(size_type _idx) const {
        // Probability
        ssize_t    high_cl = -1;
        value_type high_pr =  0;
        for (size_type cl = 0; cl < clusters(); ++cl) {
          if ((*this)[_idx][cl] > high_pr) {
            high_cl = cl;
            high_pr = (*this)[_idx][cl];
          }
        }

        // Return it
        return high_cl;
      }

      /// Cluster sizes
      std::vector<value_type>
      cluster_sizes() const {
        // Result vector
        std::vector<value_type> result(clusters(), 0u);

        // For each one
        for (size_type r = 0; r < this->size(); ++r)
          for (size_type cl = 0; cl < clusters(); ++cl)
            result[cl] += (*this)[r][cl];

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
