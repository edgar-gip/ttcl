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

#include <ttcl_mulisp/sexp/sexp_parser.hxx>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

#include <boost/intrusive_ptr.hpp>

#include <boost/spirit/version.hpp>
#if SPIRIT_VERSION < 0x2000
#  define SPIRIT boost::spirit
#  include <boost/spirit/attribute.hpp>
#  include <boost/spirit/core.hpp>
#  include <boost/spirit/phoenix.hpp>
#  include <boost/spirit/utility.hpp>
#else
#  define SPIRIT boost::spirit::classic
#  include <boost/spirit/include/classic_attribute.hpp>
#  include <boost/spirit/include/classic_core.hpp>
#  include <boost/spirit/include/classic_utility.hpp>
#  include <boost/spirit/include/phoenix1.hpp>
#endif

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_integer.hxx>
#include <ttcl_mulisp/sexp/sexp_null.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_real.hxx>
#include <ttcl_mulisp/sexp/sexp_symbol.hxx>
#include <ttcl_mulisp/sexp/sexp_string.hxx>
#include <ttcl/ut/c_escape.hxx>

using namespace std;
using namespace ttcl;
using namespace ttcl_mulisp::sexp;


/// Sexp Closure
struct sexp_closure :
  SPIRIT::closure<sexp_closure, sexp_ptr> {
  member1 val;
};

/// Sexp Sequence Closure
struct sexp_seq_closure :
  SPIRIT::closure<sexp_seq_closure, vector<sexp_ptr> > {
  member1 seq;
};

/// Base sexp grammar
struct _sexp_grammar {
  /// Pair construction helper function
  static sexp_pair_ptr
  make_cons(sexp_ptr _car, sexp_ptr _cdr) {
    return new sexp_pair(_car, _cdr);
  }

  /// Null construction helper function
  static sexp_null_ptr
  make_null() {
    return sexp_null::EOL;
  }

  /// Bool construction helper function
  static sexp_bool_ptr
  make_bool(const bool _value) {
    if (_value)
      return sexp_bool::TRUE;
    else
      return sexp_bool::FALSE;
  }

  /// Integer construction helper function
  static sexp_integer_ptr
  make_integer(const int _value) {
    return new sexp_integer(_value);
  }

  /// Real construction helper function
  static sexp_real_ptr
  make_real(const double _value) {
    return new sexp_real(_value);
  }

  /// Symbol construction helper function
  static sexp_symbol_ptr
  make_symbol(const string& _value) {
    return new sexp_symbol(_value);
  }

  /// String construction helper function
  static sexp_string_ptr
  make_string(const string& _value) {
    return new sexp_string(ut::c_unescape(_value));
  }

  /// Quote construction helper function
  static sexp_pair_ptr
  make_quote(sexp_ptr _expr) {
    return make_cons(make_symbol("quote"),
                     make_cons(_expr, make_null()));
  }

  /// Quasiquote construction helper function
  static sexp_pair_ptr
  make_quasiquote(sexp_ptr _expr) {
    return make_cons(make_symbol("quasiquote"),
                     make_cons(_expr, make_null()));
  }

  /// Unquote-splicing construction helper function
  static sexp_pair_ptr
  make_unquote_splicing(sexp_ptr _expr) {
    return make_cons(make_symbol("unquote-splicing"),
                     make_cons(_expr, make_null()));
  }

  /// Unquote construction helper function
  static sexp_pair_ptr
  make_unquote(sexp_ptr _expr) {
    return make_cons(make_symbol("unquote"),
                     make_cons(_expr, make_null()));
  }

  /// Push back helper function
  static void
  push_back_sexp(vector<sexp_ptr>& _seq, sexp_ptr _expr) {
    _seq.push_back(_expr);
  }
};

/// S-Expression grammar
struct sexp_grammar :
  public SPIRIT::grammar<sexp_grammar,
                         sexp_seq_closure::context_t>,
  public _sexp_grammar {

  /// Definition
  template <typename ScannerT>
  struct definition {
    /// Start rule
    SPIRIT::rule<ScannerT> start_rule;

    /// Expression sequence subrule
    SPIRIT::subrule<0> expr_seq;

    /// Expression subrule
    SPIRIT::subrule<1, sexp_closure::context_t> expr;

    /// List subrule
    SPIRIT::subrule<2, sexp_closure::context_t> expr_list;

    /// Atom character set
    SPIRIT::chset<> atom_char_set;

    /// Constructor
    definition(const sexp_grammar& _self) {
      atom_char_set =
        SPIRIT::chset<>("!$%&*+./0-9:<=>?@A-Z^_a-z~")
      | SPIRIT::ch_p('-');

      start_rule =
        ( expr_seq =
            *expr
            [phoenix::bind(&push_back_sexp)(_self.seq, phoenix::arg1)],


          expr =
            SPIRIT::strict_real_p
            [expr.val = phoenix::bind(&make_real)(phoenix::arg1)]

          | SPIRIT::int_p
            [expr.val = phoenix::bind(&make_integer)(phoenix::arg1)]


          | SPIRIT::ch_p('#') >>
            (SPIRIT::ch_p('t') |  SPIRIT::ch_p('f'))
            [expr.val = phoenix::bind(&make_bool)(*phoenix::arg1 == 't')]

          | SPIRIT::lexeme_d[+atom_char_set]
            [expr.val = phoenix::bind(&make_symbol)
             (phoenix::construct_<string>(phoenix::arg1,
                                          phoenix::arg2))]

          | SPIRIT::lexeme_d
            [SPIRIT::confix_p(SPIRIT::ch_p('"'),
                              (*SPIRIT::lex_escape_ch_p)
                              [expr.val = phoenix::bind(&make_string)
                               (phoenix::construct_<string>(phoenix::arg1,
                                                            phoenix::arg2))],
                              SPIRIT::ch_p('"'))]

          | SPIRIT::ch_p('(') >>
            expr [expr.val = phoenix::arg1] >>
            SPIRIT::ch_p('.') >>
            expr [expr.val = phoenix::bind(&make_cons)
                  (expr.val, phoenix::arg1)] >>
            SPIRIT::ch_p(')')

          | SPIRIT::ch_p('(') >>
            expr_list [expr.val = phoenix::arg1] >>
            SPIRIT::ch_p(')')

          | SPIRIT::ch_p('\'') >> expr
            [expr.val = phoenix::bind(&make_quote)(phoenix::arg1)]

          | SPIRIT::ch_p('`') >> expr
            [expr.val = phoenix::bind(&make_quasiquote)(phoenix::arg1)]

          | SPIRIT::str_p(",@") >> expr
            [expr.val = phoenix::bind(&make_unquote_splicing)(phoenix::arg1)]

          | SPIRIT::ch_p(',') >> expr
            [expr.val = phoenix::bind(&make_unquote)(phoenix::arg1)],

          expr_list =
            expr      [expr_list.val = phoenix::arg1] >>
            expr_list [expr_list.val = phoenix::bind(&make_cons)
                       (expr_list.val, phoenix::arg1)]

          | SPIRIT::eps_p
            [expr_list.val = phoenix::bind(&make_null)()]
          );
    }

    /// Start symbol
    const SPIRIT::rule<ScannerT>& start() const {
      return start_rule;
    }
  };
};

/// Grammar
static sexp_grammar sexp_gr;

// S-Expression parser

/// Parse a string
void sexp_parser::
parse(vector<sexp_ptr>& _target, const string& _source) {
  // Parse
  SPIRIT::parse_info<> info =
    SPIRIT::parse(_source.c_str(),
                  sexp_gr[phoenix::var(_target) = phoenix::arg1],
                  (SPIRIT::space_p | SPIRIT::comment_p(";")));

  // OK?
  if (not info.hit) {
    TTCL_FIRE("Cannot parse string `%s'", _source.c_str());
  }

  // Full?
  if (not info.full) {
    TTCL_FIRE("Cannot parse string `%s'", info.stop);
  }
}

/// Parse a stream
void sexp_parser::
parse(vector<sexp_ptr>& _target, const string& _name, istream& _is) {
  // Pending
  string pending;

  // Clear target
  _target.clear();

  // Read lines
  int n_lines = 0;
  string line;
  while (getline(_is, line)) {
    // One more line
    ++n_lines;

    // Add to pending
    pending.append(line);
    pending.append("\n");

    // Parse the lines
    vector<sexp_ptr> exprs;
    SPIRIT::parse_info<> info =
      SPIRIT::parse(pending.c_str(),
                    sexp_gr[phoenix::var(exprs) = phoenix::arg1],
                    (SPIRIT::space_p | SPIRIT::comment_p(";")));

    // OK?
    if (not info.hit) {
      TTCL_FIRE("%s:%d: Cannot parse string `%s'",
                _name.c_str(), n_lines, pending.c_str());
    }

    // Append the found expressions
    copy(exprs.begin(), exprs.end(),
         back_inserter(_target));

    // Finished
    if (info.full) {
      pending.clear();
    }
    else {
      pending = info.stop;
    }
  }

  // Full?
  if (not pending.empty()) {
    TTCL_FIRE("%s:%d: Cannot parse string `%s'",
              _name.c_str(), n_lines, pending.c_str());
  }
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
