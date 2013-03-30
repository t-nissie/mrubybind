#ifndef __MRUBYBIND_H__
#define __MRUBYBIND_H__

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include "mrubybind_types.h"

namespace mrubybind {

class MrubyBind {
 public:
  MrubyBind(mrb_state* mrb);

  // Bind function.
  template <class Func>
  void bind(const char* name, Func f) {
    mrb_value binder = mrb_voidp_value((void*)Binder<Func>::call);
    mrb_value fn = mrb_str_new_cstr(mrb, name);
    mrb_value fp = mrb_voidp_value((void*)f);
    mrb_funcall(mrb, mod_mrubybind, "define_function", 3, binder, fn, fp);
  }

  // Bind class.
  template <class Func>
  void define_class(const char* class_name, Func f) {
    mrb_value binder = mrb_voidp_value((void*)Binder<Func>::call);
    mrb_value cn = mrb_str_new_cstr(mrb, class_name);
    mrb_value fp = mrb_voidp_value((void*)f);
    mrb_funcall(mrb, mod_mrubybind, "define_class", 3, binder, cn, fp);
  }

  // Bind class method.
  template <class Method>
  void define_class_method(const char* class_name, const char* method_name, Method m) {
    mrb_value binder = mrb_voidp_value((void*)Binder<Method>::call);
    mrb_value cn = mrb_str_new_cstr(mrb, class_name);
    mrb_value mn = mrb_str_new_cstr(mrb, method_name);
    mrb_value mp = mrb_str_new(mrb, (char*)&m, sizeof(m));
    mrb_funcall(mrb, mod_mrubybind, "define_class_method", 4, binder, cn, mn, mp);
  }

 private:
  mrb_state* mrb;
  mrb_value mod_mrubybind;
};

}  // namespace mrubybind

#endif
