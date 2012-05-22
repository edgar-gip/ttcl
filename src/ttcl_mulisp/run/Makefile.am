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

include ../../../Makefile.am.inc

INCLUDES = -I../../../include -I../../ttcl

noinst_LTLIBRARIES = libttcl_mulisp_run.la

libttcl_mulisp_run_la_SOURCES = \
	bool_procedures.cxx control_procedures.cxx display_procedures.cxx \
	eval_procedures.cxx gpl_procedures.cxx interpreter.cxx \
	lisp_interpreter.cxx number_arithmetic_procedures.cxx \
	number_compare_procedures.cxx pair_procedures.cxx \
	quote_procedures.cxx set_procedures.cxx string_compare_procedures.cxx \
	string_operation_procedures.cxx
libttcl_mulisp_run_la_LIBADD = @READLINE_LIBS@

# Local Variables:
# coding: utf-8
# End:
