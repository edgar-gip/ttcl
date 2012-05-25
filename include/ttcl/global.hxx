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

#ifndef TTCL_GLOBAL_HXX
#define TTCL_GLOBAL_HXX

/** @file
    Global Definitions
    @author Edgar Gonzàlez i Pellicer
*/

/// printf()-like Format Check
#ifdef __GNUC__
# define TTCL_PRINTF_CHECK(str_idx, par_idx)            \
  __attribute__((format(printf, str_idx, par_idx)))
#else
# define TTCL_PRINTF_CHECK()
#endif

/// Import type
#define TTCL_IMPORT_TYPE(class, type)           \
  typedef typename class::type type

/// Import and rename type
#define TTCL_IMPORT_R_TYPE(class, type, newtype)        \
  typedef typename class::type newtype

/// Forwarded arguments
#ifndef TTCL_FORWARDED_ARGS
#define TTCL_FORWARDED_ARGS 6
#endif

#endif

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
