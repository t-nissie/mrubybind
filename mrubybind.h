#ifndef __MRUBYBIND_H__
#define __MRUBYBIND_H__

#include <assert.h>
#include <mruby.h>
#include <mruby/string.h>
#include <string>
#define ASSERT(expr)  assert(expr)

namespace mrubybind {

//===========================================================================
// C <-> mruby type converter.

template <class T>
struct Type {
  //static int check(mrb_value v) = 0;
  //static int get(mrb_value v) = 0;
  //static mrb_value ret(mrb_state*, int i) = 0;
};

// Fixnum
template<>
struct Type<int> {
  static int check(mrb_value v) { return mrb_fixnum_p(v); }
  static int get(mrb_value v) { return mrb_fixnum(v); }
  static mrb_value ret(mrb_state*, int i) { return mrb_fixnum_value(i); }
};

// float
template<>
struct Type<float> {
  static int check(mrb_value v) { return mrb_float_p(v); }
  static float get(mrb_value v) { return mrb_float(v); }
  static mrb_value ret(mrb_state*, float f) { return mrb_float_value(f); }
};

// double
template<>
struct Type<mrb_float> {
  static int check(mrb_value v) { return mrb_float_p(v); }
  static double get(mrb_value v) { return mrb_float(v); }
  static mrb_value ret(mrb_state*, double f) { return mrb_float_value(f); }
};

// String
template<>
struct Type<const char*> {
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const char* get(mrb_value v) { return RSTRING_PTR(v); }
  static mrb_value ret(mrb_state* mrb, const char* s) { return mrb_str_new_cstr(mrb, s); }
};

template<>
struct Type<std::string> {
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

template<>
struct Type<const std::string> {
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

template<>
struct Type<const std::string&> {
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

// Boolean
template<>
struct Type<bool> {
  static int check(mrb_value v) { return 1; }
  static bool get(mrb_value v) { return mrb_test(v); }
  static mrb_value ret(mrb_state* mrb, bool b) { return b ? mrb_true_value() : mrb_false_value(); }
};

// Raw pointer
template<>
struct Type<void*> {
  static int check(mrb_value v) { return mrb_voidp_p(v); }
  static void* get(mrb_value v) { return mrb_voidp(v); }
  static mrb_value ret(mrb_state* mrb, void* p) { return mrb_voidp_value(p); }
};

//===========================================================================
// Binder

// Template class for Binder.
// Binder template class is specialized with type.
template <class T>
struct Binder {
  //static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) = 0;
};

// Includes generated template specialization.
#include "mrubybind.inc"

//===========================================================================
// Interface

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
    mrb_funcall(mrb, mod_mrubybind, "create_class", 3, binder, cn, fp);
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

#undef ASSERT

#endif
