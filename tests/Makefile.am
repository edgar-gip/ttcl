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

include ../Makefile.am.inc

INCLUDES = -I../include -I../ext/tap++/headers

noinst_PROGRAMS = \
	test_mf_coalesce test_mf_maximum_common_type test_mf_metaclass_of \
	\
	test_tu_choices

test_mf_coalesce_SOURCES = test_mf_coalesce.cxx
test_mf_coalesce_LDADD   = \
	../src/ttcl/libttcl.la ../ext/tap++/source/libtap++.la

test_mf_maximum_common_type_SOURCES = test_mf_maximum_common_type.cxx
test_mf_maximum_common_type_LDADD   = \
	../src/ttcl/libttcl.la ../ext/tap++/source/libtap++.la

test_mf_metaclass_of_SOURCES = test_mf_metaclass_of.cxx
test_mf_metaclass_of_LDADD   = \
	../src/ttcl/libttcl.la ../ext/tap++/source/libtap++.la

test_tu_choices_SOURCES = test_tu_choices.cxx
test_tu_choices_LDADD   = \
	../src/ttcl/libttcl.la ../ext/tap++/source/libtap++.la

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) tap-driver.sh

TESTS = \
	test_mf_coalesce test_mf_maximum_common_type test_mf_metaclass_of \
	\
	test_tu_choices

# Local Variables:
# coding: utf-8
# End:
