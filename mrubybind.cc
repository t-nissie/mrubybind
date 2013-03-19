#include "mrubybind.h"
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>
#include <mruby/variable.h>

namespace mrubybind {

static
#include "mrubybind.dat"

static mrb_value call_cfunc(mrb_state *mrb, mrb_value self) {
  mrb_value binder;
  mrb_value p;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "oo*", &binder, &p, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, void*, mrb_value*, int);
  BindFunc binderp = (BindFunc)mrb_voidp(binder);
  return binderp(mrb, mrb_voidp(p), args, narg);
}

static mrb_value call_cmethod(mrb_state *mrb, mrb_value self) {
  mrb_value binder;
  mrb_value o;
  mrb_value p;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "ooo*", &binder, &o, &p, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, void*, void*, mrb_value*, int);
  BindFunc binderp = (BindFunc)mrb_voidp(binder);
  return binderp(mrb, mrb_voidp(o), RSTRING_PTR(p), args, narg);
}

MrubyBind::MrubyBind(mrb_state* mrb) {
  this->mrb = mrb;
  mrb_sym sym_mrubybind = mrb_intern(mrb, "MrubyBind");
  if (mrb_const_defined(mrb, mrb_obj_value(mrb->kernel_module), sym_mrubybind)) {
    this->mod_mrubybind = mrb_const_get(mrb, mrb_obj_value(mrb->kernel_module), sym_mrubybind);
  } else {
    RClass* mrubybind = mrb_define_module(mrb, "MrubyBind");
    this->mod_mrubybind = mrb_obj_value(mrubybind);
    mrb_define_module_function(mrb, mrubybind, "call_cfunc", call_cfunc,
                               ARGS_REQ(2) | ARGS_REST());
    mrb_define_module_function(mrb, mrubybind, "call_cmethod", call_cmethod,
                               ARGS_REQ(3) | ARGS_REST());
    int n = mrb_read_irep(mrb, binder);
    if (n >= 0) {
      mrb_run(mrb, mrb_proc_new(mrb, mrb->irep[n]), mrb_top_self(mrb));
    }
  }
}

}  // namespace mrubybind
