// Simple usage for binding function under some module.

#include <mruby.h>
#include <mruby/compile.h>
#include "mrubybind.h"

void modfunc(int v) {
  printf("modfunc called: %d\n", v);
}

int main() {
  mrb_state* mrb = mrb_open();

  {
    RClass* mod = mrb_define_module(mrb, "Mod");
    mrubybind::MrubyBind b(mrb, mod);
    b.bind("modfunc", modfunc);
    b.bind_const("FOO_VALUE", 1234);
  }

  int result_code = EXIT_SUCCESS;
  mrb_load_string(mrb, "Mod.modfunc(Mod::FOO_VALUE)");
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    result_code = EXIT_FAILURE;
  }

  mrb_close(mrb);
  return 0;
}
