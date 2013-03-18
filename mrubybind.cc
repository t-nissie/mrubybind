#include "mrubybind.h"
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>

namespace mrubybind {

static
#include "mrubybind.dat"

RClass *mymodule;

static mrb_value call_cfunc(mrb_state *mrb, mrb_value self) {
  mrb_value binder;
  mrb_value p;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "oo*", &binder, &p, &args, &narg);
  mrb_value (*binderp)(mrb_state*, void*, mrb_value*, int) =
    (mrb_value (*)(mrb_state*, void*, mrb_value*, int))mrb_voidp(binder);
  return binderp(mrb, mrb_voidp(p), args, narg);
}

static mrb_value call_cmethod(mrb_state *mrb, mrb_value self) {
  mrb_value binder;
  mrb_value o;
  mrb_value p;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "ooo*", &binder, &o, &p, &args, &narg);
  mrb_value (*binderp)(mrb_state*, void*, void*, mrb_value*, int) =
    (mrb_value (*)(mrb_state*, void*, void*, mrb_value*, int))mrb_voidp(binder);
  return binderp(mrb, mrb_voidp(o), RSTRING_PTR(p), args, narg);
}

int initialize_mrubybind(mrb_state* mrb) {
  mymodule = mrb_define_module(mrb, "MrubyBind");
  mrb_define_module_function(mrb, mymodule, "call_cfunc", call_cfunc, ARGS_REQ(2) | ARGS_REST());
  mrb_define_module_function(mrb, mymodule, "call_cmethod", call_cmethod, ARGS_REQ(3) | ARGS_REST());
  int n = mrb_read_irep(mrb, binder);
  if (n < 0)
    return 0;
  mrb_run(mrb, mrb_proc_new(mrb, mrb->irep[n]), mrb_top_self(mrb));
  return 1;
}

}  // namespace mrubybind
