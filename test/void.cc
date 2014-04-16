#include <mruby.h>
#include <mruby/compile.h>
#include "mrubybind.h"

void dummy() {
  printf("dummy called\n");
}

int main() {
  mrb_state* mrb = mrb_open();

  {
    mrubybind::MrubyBind b(mrb);
    b.bind("dummy", dummy);
  }
  if (mrb->arena_idx != 0) {
    fprintf(stderr, "Arena increased!\n");
    return EXIT_FAILURE;
  }

  int result_code = EXIT_SUCCESS;
  mrb_load_string(mrb, "dummy()");
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    result_code = EXIT_FAILURE;
  }

  mrb_close(mrb);
  return result_code;
}
