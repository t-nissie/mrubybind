mrubybind - Binding library for mruby/C++
=========================================

## Usage

### Bind C function and call it from mruby

1. C function (Any type you want):

        int square(int x) {
          return x * x;
        }

2. Bind it using mrubybind:

        #include "mrubybind.h"
        
        void install_square_function(mrb_state* mrb) {
          mrubybind::MrubyBind b(mrb);
          b.bind("square", square);
        }

3. Call it from mruby:

        puts square(1111)  #=> 1234321

### Bind C++ class and method and call it from mruby

1. C++ class:

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

2. Bind C++ class using mrubybind:

        #include "mrubybind.h"
        
        // Helper function for constructor.
        Foo* new_foo(int x) {
          return new Foo(x);
        }
        
        void install_foo_class(mrb_state* mrb) {
          mrubybind::MrubyBind b(mrb);
          b.bind_class("Foo", new_foo);
          b.bind_class_method("Foo", "bar", &Foo::bar);
        }

3. Call it from mruby:

        foo = Foo.new(123)  #=> Foo::ctor(123), 0x104516780
        p foo               #=> #<Foo0x7fa828803d80>
        p foo.bar(567)      #=> 690
                            #=> Foo::dtor(), 0x104516780

# License

MIT license.
