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

include ../../../../Makefile.am.inc

INCLUDES = -I../../../../include -I../../../../ext/tap++/headers

noinst_PROGRAMS = \
	test_cross_apply

test_cross_apply_SOURCES = test_cross_apply.cxx
test_cross_apply_LDADD   = \
	../../../../src/ttcl/libttcl.la ../../../../ext/tap++/source/libtap++.la

# Local Variables:
# coding: utf-8
# End:
