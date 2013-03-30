mrubybind - Binding library for mruby/C++
=========================================

## Usage

### Bind C function and call it from mruby

  // C function
  int square(int x) {
    return x * x;
  }

  // C++
  #include "mrubybind.h"
  
  void install_square(mrb_state* mrb) {
    mrubybind::MrubyBind b(mrb);
    b.bind("square", square);
  }

  // mruby
  puts square(1111)  #=> 1234321

### Bind C++ class and method and call it from mruby

  // C++ class
  class Foo {
  public:
    Foo(int x) : x_(x) {
      cout << "Foo::ctor(" << x << "), " << this << endl;
    }
    virtual ~Foo() {
      cout << "Foo::dtor(), " << this << endl;
    }
    int bar(int y) {
      return x_ + y;
    }
  
  private:
    int x_;
  };

  // Bind
  Foo* new_foo(int x) {
    return new Foo(x);
  }
  
  void install_foo_class(mrb_state* mrb) {
    mrubybind::MrubyBind b(mrb);
    b.bind_class("Foo", new_foo);
    b.bind_class_method("Foo", "bar", &Foo::bar);
  }

  // mruby
  foo = Foo.new(123)
  p foo
  p foo.bar(567)


# License

MIT license.
