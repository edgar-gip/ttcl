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

#include <ttcl_mulisp/run/interpreter.hxx>

#include "config.hxx"

#include <wordexp.h>

#include <cctype>
#include <cstdlib>
#include <cstring>

#include <boost/foreach.hpp>

#ifdef HAVE_LIBREADLINE
#include <readline/history.h>
#include <readline/readline.h>
#endif

#include <ttcl/exception.hxx>

#include <ttcl_mulisp/sexp/sexp.hxx>
#include <ttcl_mulisp/sexp/sexp_bool.hxx>
#include <ttcl_mulisp/sexp/sexp_pair.hxx>
#include <ttcl_mulisp/sexp/sexp_parser.hxx>
#include <ttcl_mulisp/sexp/sexp_symbol.hxx>

using namespace std;
using namespace ttcl_mulisp;
using namespace ttcl_mulisp::run;
using namespace ttcl_mulisp::sexp;

// Parser
static sexp_parser parser;

#ifndef TTCL_CXX0X_DEFAULTS
/// Constructor
interpreter::
interpreter() {
}
#endif

/// Destructor
interpreter::
~interpreter() {
}

/// Get variable
sexp_ptr interpreter::
get(const string& _name) const {
  auto it = variables_.find(_name);
  if (it == variables_.end()) {
    TTCL_FIRE("Unbound variable `%s'", _name.c_str());
  }
  return it->second;
}

/// Set variable
void interpreter::
set(const string& _name, sexp_ptr _value) {
  variables_[_name] = _value;
}

/// Localize variable
void interpreter::
localize(const string& _name) {
  auto it = variables_.find(_name);
  if (it == variables_.end()) {
    push_down_.push(make_pair(_name, sexp_ptr(NULL)));
  }
  else {
    push_down_.push(*it);
  }
}

/// Push context
void interpreter::
push_context() {
  push_down_sizes_.push(push_down_.size());
}

/// Pop context
void interpreter::
pop_context() {
  if (push_down_sizes_.empty()) {
    TTCL_FIRE("No context to pop");
  }

  int target_size = push_down_sizes_.top();
  push_down_sizes_.pop();

  while (push_down_.size() > target_size) {
    pair<string, sexp_ptr> binding = push_down_.top();
    push_down_.pop();

    if (binding.second) {
      variables_[binding.first] = binding.second;
    }
    else {
      variables_.erase(binding.first);
    }
  }
}

/// Parse
vector<sexp_ptr> interpreter::
parse(const string& _string) {
  vector<sexp_ptr> sexps;
  parser.parse(sexps, _string);
  return sexps;
}

/// Parse
sexp_ptr interpreter::
parse_one(const string& _string) {
  vector<sexp_ptr> sexps;
  parser.parse(sexps, _string);

  if (sexps.size() != 1) {
    TTCL_FIRE("Parsing did not produce a single expression");
  }

  return sexps[0];
}

/// Eval
sexp_ptr interpreter::
eval(sexp_ptr _expr) {
  _expr->visit(*this);
  return result_;
}

/// Eval
sexp_ptr interpreter::
eval(const string& _string) {
  vector<sexp_ptr> sexps;
  parser.parse(sexps, _string);

  sexp_ptr result;
  BOOST_FOREACH(const sexp_ptr& _sexp, sexps)
    result = eval(_sexp);

  return result;
}

/// Eval
sexp_ptr interpreter::
eval(const string& _name, istream& _stream) {
  vector<sexp_ptr> sexps;
  parser.parse(sexps, _name, _stream);

  sexp_ptr result;
  BOOST_FOREACH(const sexp_ptr& _sexp, sexps)
    result = eval(_sexp);

  return result;
}

/// Apply
sexp_ptr interpreter::
apply(sexp_ptr _functor, const vector<sexp_ptr>& _arguments) {
  sexp_ptr result;

  if (_functor->is_native()) {
    sexp_native_ptr n_functor = sexp_cast<sexp_native>(_functor);

    if (_arguments.size() < n_functor->min_arity() or
        _arguments.size() > n_functor->max_arity()) {
      if (n_functor->min_arity() == n_functor->max_arity()) {
        TTCL_FIRE("(%s): Expected %d arguments, %zd provided",
                  n_functor->name().c_str(), n_functor->min_arity(),
                  _arguments.size());
      }
      else {
        TTCL_FIRE("(%s): Expected %d to %d arguments, %zd provided",
                  n_functor->name().c_str(), n_functor->min_arity(),
                  n_functor->max_arity(), _arguments.size());
      }
    }

    result = (*(n_functor->call()))(_arguments, *this);
  }
  else if (_functor->is_procedure()) {
    sexp_procedure_ptr    p_functor  = sexp_cast<sexp_procedure>(_functor);
    const vector<string>& parameters = p_functor->parameters();

    if (_arguments.size() != parameters.size())
      TTCL_FIRE("(%s): Expected %zd arguments, %zd provided",
                p_functor->name().c_str(), parameters.size(),
                _arguments.size());

    push_context();
    for (int i = 0; i < parameters.size(); ++i) {
      localize(parameters[i]);
      set(parameters[i], _arguments[i]);
    }

    try {
      BOOST_FOREACH(sexp_ptr expr, p_functor->body()) {
        result = eval(expr);
      }

      pop_context();
    }
    catch (...) {
      pop_context();
      throw;
    }
  }
  else {
    TTCL_FIRE("Functor is not a procedure");
  }

  return result;
}


// S-Expression const visitor interface

/// Visit
void interpreter::
visit(ttcl_mulisp::sexp::sexp& _sexp) {
  // By default, values are self-evaluating
  result_ = &_sexp;
}

/// Visit
void interpreter::
visit(sexp_pair& _sexp) {
  sexp_ptr functor = eval(_sexp.car());

  vector<sexp_ptr> arguments;
  sexp_ptr list = _sexp.cdr();
  while (list->is_pair()) {
    sexp_pair_ptr p = sexp_cast<sexp_pair>(list);
    arguments.push_back(p->car());
    list = p->cdr();
  }

  if (not list->is_null())
    TTCL_FIRE("Ill-formed functional application");

  if (not (functor->is_native() and
           sexp_cast<sexp_native>(functor)->is_macro())) {
    BOOST_FOREACH(sexp_ptr& arg, arguments) {
      arg = eval(arg);
    }
  }

  result_ = apply(functor, arguments);
}

/// Visit
void interpreter::
visit(sexp_symbol& _sexp) {
  if (_sexp.value()[0] == ':' or _sexp.value()[0] == '@') {
    result_ = &_sexp;
  }
  else {
    result_ = get(_sexp.value());
  }
}


#ifdef HAVE_LIBREADLINE

/// Deinitialize readline
static void
deinitialize_readline() {
  wordexp_t p;
  if (not wordexp("~/.ttcl-cluster.history", &p, WRDE_NOCMD) and
      p.we_wordc == 1) {
    write_history(p.we_wordv[0]);
    wordfree(&p);
  }
}

/// Initialize readline
static void
initialize_readline() {
  static bool initialized = false;
  if (not initialized) {
    using_history();

    wordexp_t p;
    if (not wordexp("~/.ttcl-cluster.history", &p, WRDE_NOCMD) and
        p.we_wordc == 1) {
      read_history(p.we_wordv[0]);
      wordfree(&p);
    }

    atexit(deinitialize_readline);
  }
}

/// Strip whitespace
static void
strip_whitespace(char* _string) {
  char* start = _string;
  while (*start and isspace(*start)) ++start;

  if (not *start) {
    _string[0] = '\0';
    return;
  }

  char* end = start + strlen(start) - 1;
  while (end != start and isspace(*end)) --end;

  int length = end - start + 1;
  memmove(start, _string, length);
  _string[length] = 0;
}

#endif

/// REPL
void interpreter::
repl() {
#ifdef HAVE_LIBREADLINE
  initialize_readline();

  while (true) {
    char* line = readline(">> ");
    if (not line)
      break;

    strip_whitespace(line);

    if (*line) {
      add_history(line);
      try {
        cout << eval(line)->repr() << endl;
      }
      catch (ttcl::exception& _e) {
        cout << "ttcl::exception: " << _e.message() << endl;
      }
    }
  }

#else
  while (not cin.eof()) {
    cout << ">> " << flush;

    string line;
    if (getline(cin, line)) {
      try {
        cout << eval(line)->repr() << endl;
      }
      catch (ttcl::exception& _e) {
        cout << "ttcl::exception: " << _e.message() << endl;
      }
    }
  }
#endif

  cout << endl;
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
