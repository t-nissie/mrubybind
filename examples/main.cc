#include <mruby.h>
#include <mruby/compile.h>
#include "mrubybind.h"

#include <iostream>
#include <string>
using namespace std;

int square(int x) {
  return x * x;
}

string emphasize(const char* str) {
  return "* " + string(str) + " *";
}

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

Foo* new_foo(int x) {
  return new Foo(x);
}

int main() {
  mrb_state* mrb = mrb_open();

  {
    mrubybind::MrubyBind b(mrb);
    b.bind("square", square);
    b.bind("emphasize", emphasize);
  }
  mrb_load_string(mrb,
                  "puts square(1111)\n"
                  "puts emphasize('Hello, mruby!')\n"
                  );
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
  }

  {
    mrubybind::MrubyBind b(mrb);
    b.bind_class("Foo", new_foo);
    b.bind_class_method("Foo", "bar", &Foo::bar);
  }
  mrb_load_string(mrb,
                  "foo = Foo.new(123)\n"
                  "p foo\n"
                  "p foo.bar(567)\n"
                  );

  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
  }

  mrb_close(mrb);
  return 0;
}
