# TTCL: The Template Clustering Library
# Copyright (C) 2012  Edgar Gonzàlez i Pellicer
#
# This file is part of TTCL.
#
# TTCL is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

SUBDIRS = unit

LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) tap-driver.sh

TESTS = \
	unit/ttcl/cl/test_hard_data_clusterer \
	unit/ttcl/cl/test_soft_data_clusterer \
	\
	unit/ttcl/co/test_fortran_matrix \
	unit/ttcl/co/test_full_symmetric_matrix \
	unit/ttcl/co/test_hollow_symmetric_matrix \
	unit/ttcl/co/test_matrix \
	unit/ttcl/co/test_vecvec_matrix \
	\
	unit/ttcl/dt/wr/test_feature_data_w \
	unit/ttcl/dt/wr/test_matrix_w \
	\
	unit/ttcl/fn/test_cross_apply \
	\
	unit/ttcl/mf/test_coalesce \
	unit/ttcl/mf/test_maximum_common_type \
	unit/ttcl/mf/test_metaclass_of \
	\
	unit/ttcl/tu/test_choices \
	\
	unit/ttcl/wr/test_interface_wrap

# Local Variables:
# coding: utf-8
# End:
