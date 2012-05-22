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

include ../../Makefile.am.inc

SUBDIRS = ut tu wr

INCLUDES = -I../../include

noinst_LTLIBRARIES = libttcl_core.la
lib_LTLIBRARIES = libttcl.la

libttcl_core_la_SOURCES = \
	boost_assert.cxx exception.cxx sys_exception.cxx

libttcl_la_SOURCES =
libttcl_la_LIBADD  = \
	libttcl_core.la ut/libttcl_ut.la tu/libttcl_tu.la wr/libttcl_wr.la

# Local Variables:
# coding: utf-8
# End:
