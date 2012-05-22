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

SUBDIRS = sexp run

INCLUDES = -I../../include

bin_PROGRAMS = ttcl-mulisp

lib_LTLIBRARIES = libttcl_mulisp.la

libttcl_mulisp_la_SOURCES =
libttcl_mulisp_la_LIBADD  = \
	sexp/libttcl_mulisp_sexp.la run/libttcl_mulisp_run.la \
	../ttcl/libttcl.la

ttcl_mulisp_SOURCES = main.cxx
ttcl_mulisp_LDADD = libttcl_mulisp.la ../ttcl/libttcl.la

# Local Variables:
# coding: utf-8
# End:
