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

#include <tap++/tap++.h>

#include <ttcl/assert.hxx>
#include <ttcl/types.hxx>
#include <ttcl/cl/hard_data_clusterer.hxx>

#include "dummy_data.hxx"

// Dummy clusterer
class dummy_clusterer :
  public ttcl::cl::hard_data_clusterer<dummy_data> {
public:
  /// Perform the hard clustering
  virtual void
  hard_cluster_on(hard_clustering_type& _hard_clustering,
                  const data_type& _data,
                  const ttcl::uint _n_clusters) const {
    TTCL_ASSERT_EQ(_hard_clustering.size(), _data.size());

    for (ttcl::uint i = 0; i < _data.size(); ++i)
      _hard_clustering[i] = i % _n_clusters;

    _hard_clustering.set_clusters(_n_clusters);
  }
};

// Clustering types
typedef dummy_clusterer::hard_clustering_type hard_clustering;
typedef dummy_clusterer::soft_clustering_type soft_clustering;

// Samples
const uint n_samples = 100;

// Number of clusters
const uint n_clusters = 5;

// Test
int
main() {
  // Plan
  TAP::plan(2 * (2 + n_samples)
            + 2 * (2 + n_samples * n_clusters));

  // Data
  dummy_data data (n_samples);

  // Clusterer
  dummy_clusterer clusterer;

  { // Hard cluster
    hard_clustering hc = clusterer.hard_cluster(data, n_clusters);
    TAP::is(hc.clusters(), n_clusters);
    if (TAP::is(hc.size(), n_samples)) {
      for (int i = 0; i < n_samples; ++i) {
        TAP::is(hc[i], i % n_clusters);
      }
    }
    else {
      TAP::skip(n_samples);
    }
  }

  { // Hard cluster on
    hard_clustering hc (data.size(), 0);
    clusterer.hard_cluster_on(hc, data, n_clusters);
    TAP::is(hc.clusters(), n_clusters);
    if (TAP::is(hc.size(), n_samples)) {
      for (int i = 0; i < n_samples; ++i) {
        TAP::is(hc[i], i % n_clusters);
      }
    }
    else {
      TAP::skip(n_samples);
    }
  }

  { // Soft cluster
    soft_clustering sc = clusterer.soft_cluster(data, n_clusters);
    bool c1 = TAP::is(sc.clusters(), n_clusters);
    bool c2 = TAP::is(sc.size(), n_samples);
    if (c1 && c2) {
      for (int i = 0; i < n_samples; ++i) {
        for (int c = 0; c < n_clusters; ++c) {
          if (c == i % n_clusters) {
            TAP::is(sc[i][c], 1.0);
          }
          else {
            TAP::is(sc[i][c], 0.0);
          }
        }
      }
    }
    else {
      TAP::skip(n_samples * n_clusters);
    }
  }

  { // Soft cluster on
    soft_clustering sc (data.size(), n_clusters);
    clusterer.soft_cluster_on(sc, data, n_clusters);
    bool c1 = TAP::is(sc.clusters(), n_clusters);
    bool c2 = TAP::is(sc.size(), n_samples);
    if (c1 && c2) {
      for (int i = 0; i < n_samples; ++i) {
        for (int c = 0; c < n_clusters; ++c) {
          if (c == i % n_clusters) {
            TAP::is(sc[i][c], 1.0);
          }
          else {
            TAP::is(sc[i][c], 0.0);
          }
        }
      }
    }
    else {
      TAP::skip(n_samples * n_clusters);
    }
  }

  // Return
  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
