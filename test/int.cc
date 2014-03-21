#include <mruby.h>
#include <mruby/compile.h>
#include "mrubybind.h"

int square(int x) {
  return x * x;
}

int main() {
  mrb_state* mrb = mrb_open();

  {
    mrubybind::MrubyBind b(mrb);
    b.bind("square", square);
  }

  mrb_load_string(mrb, "puts square(1111)");
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
  }

  mrb_close(mrb);
  return 0;
}
