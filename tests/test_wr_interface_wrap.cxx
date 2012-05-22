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

#include <boost/mpl/void.hpp>
#include <boost/type_traits/is_same.hpp>

#include <tap++/tap++.h>

#include <ttcl/wr/interface_wrap.hxx>
#include <ttcl/wr/shared_referee.hxx>
#include <ttcl/wr/typed_shared_referee.hxx>

/***************/
/* F interface */
/***************/

// F
class f {
public:
  // Function
  virtual int
  fun_f() const = 0;
};

// F interface
class f_interface :
  public ttcl::wr::shared_referee {
public:
  // Constructor
  f_interface(bool _owned = true,
              uint _references = 0) :
    ttcl::wr::shared_referee(_owned, _references) {
  }

  // Function
  virtual int
  fun_f() const = 0;
};

// F referee
template <typename T, typename Interface>
class f_referee :
  public ttcl::wr::typed_shared_referee<T, Interface> {
public:
  // Constructor
  f_referee(T* _ptr = NULL, bool _owned = true) :
    ttcl::wr::typed_shared_referee<T, Interface>(_ptr, _owned) {
  }

  // Function
  virtual int
  fun_f() const {
    return this->ptr_->fun_f();
  }
};

// Base F wrapper
template <typename Interface>
class base_f_wrap :
  public ttcl::wr::interface_wrap<Interface> {
public:
  // Base type
  typedef ttcl::wr::interface_wrap<Interface> base_type;

protected:
  /// Empty constructor
  base_f_wrap() :
    base_type() {
  }

  /// Constructor
  base_f_wrap(Interface* _ptr) :
    base_type(_ptr) {
  }

public:
  // Function
  virtual int
  fun_f() const {
    return this->ptr_->fun_f();
  }
};

// F wrapper
class f_wrap :
  public base_f_wrap<f_interface> {
private:
  // Base type
  typedef base_f_wrap<f_interface> base_type;

public:
  // Empty Constructor
  f_wrap() :
    base_type() {
  }

  // Constructor
  template <typename T>
  f_wrap(T* _value, bool _owned = true) :
    base_type(new f_referee<T, f_interface>(_value, _owned)) {
  }

  // Constructor
  template <typename T>
  f_wrap(T& _value, bool _owned = false) :
    base_type(new f_referee<T, f_interface>(&_value, _owned)) {
  }
};

/***************/
/* G interface */
/***************/

// G
class g :
  public f {
public:
  // Function
  virtual int
  fun_g() const = 0;
};

// G interface
class g_interface :
  public f_interface {
public:
  // Constructor
  g_interface(bool _owned = true,
              uint _references = 0) :
    f_interface(_owned, _references) {
  }

  // Function
  virtual int
  fun_g() const = 0;
};

// G referee
template <typename T, typename Interface>
class g_referee :
  public f_referee<T, Interface> {
public:
  // Constructor
  g_referee(T* _ptr = NULL, bool _owned = true) :
    f_referee<T, Interface>(_ptr, _owned) {
  }

  // Function
  virtual int
  fun_g() const {
    return this->ptr_->fun_g();
  }
};

// Base G wrapper
template <typename Interface>
class base_g_wrap :
  public base_f_wrap<Interface> {
public:
  // Base type
  typedef base_f_wrap<Interface> base_type;

protected:
  /// Empty constructor
  base_g_wrap() :
    base_type() {
  }

  /// Constructor
  base_g_wrap(Interface* _ptr) :
    base_type(_ptr) {
  }

public:
  // Function
  virtual int
  fun_g() const {
    return this->ptr_->fun_g();
  }
};

// G wrapper
class g_wrap :
  public base_g_wrap<g_interface> {
private:
  // Base type
  typedef base_g_wrap<g_interface> base_type;

public:
  // Empty Constructor
  g_wrap() :
    base_type() {
  }

  // Constructor
  template <typename T>
  g_wrap(T* _value, bool _owned = true) :
    base_type(new g_referee<T, g_interface>(_value, _owned)) {
  }

  // Constructor
  template <typename T>
  g_wrap(T& _value, bool _owned = false) :
    base_type(new g_referee<T, g_interface>(&_value, _owned)) {
  }
};

/*******************/
/* Implementations */
/*******************/

// Implementation A
class A :
  public f {
public:
  // Function
  virtual int
  fun_f() const {
    return 1;
  }
};

// Implementation B
class B :
  public g {
public:
  // Function
  virtual int
  fun_f() const {
    return 2;
  }

  // Function
  virtual int
  fun_g() const {
    return 2;
  }
};

// Implementation C
class C :
  public g {
public:
  // Function
  virtual int
  fun_f() const {
    return 3;
  }

  // Function
  virtual int
  fun_g() const {
    return 3;
  }
};

/********/
/* Test */
/********/

// Main
int main() {
  TAP::plan(7);

  f_wrap f_w;

  f_w = new A();
  TAP::is(f_w.fun_f(), 1);

  f_w = new B();
  TAP::is(f_w.fun_f(), 2);

  f_w = new C();
  TAP::is(f_w.fun_f(), 3);

  g_wrap g_w;

  g_w = new B();
  TAP::is(g_w.fun_f(), 2);
  TAP::is(g_w.fun_g(), 2);

  g_w = new C();
  TAP::is(g_w.fun_f(), 3);
  TAP::is(g_w.fun_g(), 3);

  return TAP::exit_status();
}

// Local Variables:
// coding: utf-8
// indent-tabs-mode: nil
// End:
