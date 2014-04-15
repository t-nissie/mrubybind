// Do not modify this file directly, this is generated
#include "mrubybind.h"
#include "mruby/compile.h"
#include "mruby/dump.h"
#include "mruby/proc.h"
#include "mruby/string.h"
#include "mruby/variable.h"

namespace mrubybind {

//#include "mrubybind.dat"
#include <stdint.h>
const uint8_t binder[] = {
0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x32,0x15,0x99,0x00,0x00,0x00,0x7a,0x4d,0x41,
0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x5c,0x30,0x30,
0x30,0x30,0x00,0x00,0x00,0x32,0x00,0x01,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x04,
0x00,0x80,0x00,0x05,0x00,0x80,0x00,0x44,0x00,0x80,0x00,0x45,0x00,0x00,0x00,0x4a,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x09,0x4d,0x72,0x75,0x62,0x79,0x42,
0x69,0x6e,0x64,0x00,0x00,0x00,0x00,0x1e,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x00,
0x00,0x02,0x00,0x80,0x00,0x05,0x00,0x80,0x00,0x29,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
};

const char Type<int>::TYPE_NAME[] = "Fixnum";
const char Type<unsigned int>::TYPE_NAME[] = "Fixnum";
const char Type<float>::TYPE_NAME[] = "Float";
const char Type<double>::TYPE_NAME[] = "Float";
const char Type<const char*>::TYPE_NAME[] = "String";
const char Type<std::string>::TYPE_NAME[] = "String";
const char Type<const std::string>::TYPE_NAME[] = "String";
const char Type<const std::string&>::TYPE_NAME[] = "String";
const char Type<bool>::TYPE_NAME[] = "Bool";
const char Type<void*>::TYPE_NAME[] = "Voidp";

mrb_value raise(mrb_state *mrb, int parameter_index,
                const char* required_type_name, mrb_value value) {
  const char * argument_class_name = mrb_obj_classname(mrb, value);
  mrb_raisef(mrb, E_TYPE_ERROR, "can't convert %S into %S, argument %S(%S)",
             mrb_str_new_cstr(mrb, argument_class_name),
             mrb_str_new_cstr(mrb, required_type_name),
             mrb_fixnum_value(parameter_index + 1), value);
  return mrb_nil_value();
}

mrb_value raisenarg(mrb_state *mrb, mrb_value func_name, int narg, int nparam) {
  mrb_raisef(mrb, E_ARGUMENT_ERROR, "'%S': wrong number of arguments (%S for %S)",
             func_name,
             mrb_fixnum_value(narg),
             mrb_fixnum_value(nparam));
  return mrb_nil_value();
}

static mrb_value call_cfunc(mrb_state *mrb, mrb_value /*self*/) {
  mrb_value binder;
  mrb_value func_ptr_v;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "oo*", &binder, &func_ptr_v, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, void*, mrb_value*, int);
  BindFunc binderp = reinterpret_cast<BindFunc>(mrb_voidp(binder));
  return binderp(mrb, mrb_voidp(func_ptr_v), args, narg);
}


void
MrubyBind::mrb_define_class_method_raw(mrb_state *mrb, struct RClass *c, mrb_sym mid, struct RProc *p)
{
  mrb_define_class_method(mrb, c, mrb_sym2name(mrb, mid), NULL, MRB_ARGS_ANY());  // Dummy registration.
  mrb_define_method_raw(mrb, ((RObject*)c)->c, mid, p);
}


MrubyBind::MrubyBind(mrb_state* mrb) : mrb_(mrb), mod_(mrb_->kernel_module) {
  Initialize();
}

MrubyBind::MrubyBind(mrb_state* mrb, RClass* mod) : mrb_(mrb), mod_(mod) {
  Initialize();
}

MrubyBind::~MrubyBind() {
  mrb_gc_arena_restore(mrb_, arena_index_);
}

void MrubyBind::Initialize() {
  arena_index_ = mrb_gc_arena_save(mrb_);
  mrb_sym sym_mrubybind = mrb_intern_cstr(mrb_, "MrubyBind");
  if (mrb_const_defined(mrb_, mrb_obj_value(mrb_->kernel_module),
                        sym_mrubybind)) {
    mod_mrubybind_ = mrb_const_get(mrb_, mrb_obj_value(mrb_->kernel_module),
                                   sym_mrubybind);
  } else {
    RClass* mrubybind = mrb_define_module(mrb_, "MrubyBind");
    mod_mrubybind_ = mrb_obj_value(mrubybind);
    mrb_define_module_function(mrb_, mrubybind, "call_cfunc", call_cfunc,
                               ARGS_REQ(2) | ARGS_REST());
    mrb_irep* irep = mrb_read_irep(mrb_, binder);
    if (irep != NULL) {
      mrb_run(mrb_, mrb_proc_new(mrb_, irep), mrb_top_self(mrb_));
    }
  }
}

struct RClass* MrubyBind::GetClass(const char* class_name) {
  mrb_value mod = mrb_obj_value(mod_);
  mrb_value klass_v = mrb_const_get(mrb_, mod, mrb_intern_cstr(mrb_, class_name));
  return mrb_class_ptr(klass_v);
}

void MrubyBind::BindInstanceMethod(
    const char* class_name, const char* method_name,
    mrb_value original_func_v,
    mrb_value (*binder_func)(mrb_state*, mrb_value)) {
  mrb_sym method_name_s = mrb_intern_cstr(mrb_, method_name);
  mrb_value env[] = {
    original_func_v,                  // 0: c function pointer
    mrb_symbol_value(method_name_s),  // 1: method name
  };
  struct RProc* proc = mrb_proc_new_cfunc_with_env(mrb_, binder_func, 2, env);
  struct RClass* klass = GetClass(class_name);
  mrb_define_method_raw(mrb_, klass, method_name_s, proc);
}

}  // namespace mrubybind
