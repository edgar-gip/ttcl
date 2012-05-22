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

SUBDIRS = manual

include Doxygen.am

# if DX_COND_man

# # You'd probably want to post-process man pages and installed the patched
# # versions.
# dist_man1_MANS = @DX_DOCDIR@/man/man1/doxample.c.1

# $(dist_man1_MANS): doxygen-doc

# endif

MOSTLYCLEANFILES = $(DX_CLEANFILES)

EXTRA_DIST = $(DX_CONFIG)

all: doxygen-doc

# Local Variables:
# coding: utf-8
# End:
