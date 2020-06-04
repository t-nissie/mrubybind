// Do not modify this file directly, this is generated
/**
 * mrubybind - Binding library for mruby/C++
 *
 * Usage:
 *   1. Prepare a function which you want to call from mruby:
 *     > int square(int x)  { return x * x; }
 *
 *   2. Create MrubyBind instance:
 *     > MrubyBind b(mirb)
 *
 *   3. Bind a function:
 *     > b.bind("square", square);
 *
 *   4. You can call it from mruby:
 *     > puts square(1111)  #=> 1234321
 *
 *   There are other methods to bind constant/class/instance method in
 *   MrubyBind. Please see the definition of MrubyBind
 *   (the bottom of this file), or README.
 */
#ifndef __MRUBYBIND_H__
#define __MRUBYBIND_H__

#ifndef __cplusplus
#error mrubybind can be used from C++ only.
#endif

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/proc.h"
#include "mruby/variable.h"
//#include "mrubybind_types.h"
// Describe type conversion between C type value and mruby value.

#include "mruby/string.h"
#include <string>
#include <utility>

namespace mrubybind {

//===========================================================================
// C <-> mruby type converter.

// Base template class.
template <class T>
struct Type {
  // Type name used for error message.
  // static const char TYPE_NAME[];

  // Returns whether the given mrb_value can be converted into type T.
  //static int check(mrb_value v) = 0;

  // Converts mrb_value to type T value.
  //static T get(mrb_value v) = 0;

  // Converts type T value to mrb_value.
  //static mrb_value ret(mrb_state*, T i) = 0;
};

// Fixnum
template<>
struct Type<int> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_fixnum_p(v) || mrb_float_p(v); }
  static int get(mrb_value v) { return mrb_fixnum_p(v) ? mrb_fixnum(v) : mrb_float(v); }
  static mrb_value ret(mrb_state*, int i) { return mrb_fixnum_value(i); }
};

template<>
struct Type<unsigned int> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_fixnum_p(v) || mrb_float_p(v); }
  static unsigned int get(mrb_value v) { return mrb_fixnum_p(v) ? mrb_fixnum(v) : mrb_float(v); }
  static mrb_value ret(mrb_state*, unsigned int i) { return mrb_fixnum_value(i); }
};

// float
template<>
struct Type<float> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_float_p(v) || mrb_fixnum_p(v); }
  static float get(mrb_value v) { return mrb_float_p(v) ? mrb_float(v) : mrb_fixnum(v); }
  static mrb_value ret(mrb_state* mrb, float f) { return mrb_float_value(mrb, f); }
};

// double
template<>
struct Type<double> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_float_p(v) || mrb_fixnum_p(v); }
  static double get(mrb_value v) { return mrb_float_p(v) ? mrb_float(v) : mrb_fixnum(v); }
  static mrb_value ret(mrb_state* mrb, double f) { return mrb_float_value(mrb, f); }
};

// String
template<>
struct Type<const char*> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const char* get(mrb_value v) { return RSTRING_PTR(v); }
  static mrb_value ret(mrb_state* mrb, const char* s) { return mrb_str_new_cstr(mrb, s); }
};

template<>
struct Type<std::string> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

template<>
struct Type<const std::string> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

template<>
struct Type<const std::string&> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_string_p(v); }
  static const std::string get(mrb_value v) { return std::string(RSTRING_PTR(v), RSTRING_LEN(v)); }
  static mrb_value ret(mrb_state* mrb, const std::string& s) { return mrb_str_new(mrb, s.c_str(), s.size()); }
};

// Boolean
template<>
struct Type<bool> {
  static const char TYPE_NAME[];
  static int check(mrb_value /*v*/) { return 1; }
  static bool get(mrb_value v) { return mrb_test(v); }
  static mrb_value ret(mrb_state* /*mrb*/, bool b) { return b ? mrb_true_value() : mrb_false_value(); }
};

// Raw pointer
template<>
struct Type<void*> {
  static const char TYPE_NAME[];
  static int check(mrb_value v) { return mrb_cptr_p(v); }
  static void* get(mrb_value v) { return mrb_cptr(v); }
  static mrb_value ret(mrb_state* mrb, void* p) { return mrb_cptr_value(mrb, p); }
};

//===========================================================================
// Binder

// Template class for Binder.
// Binder template class is specialized with type.
template <class T>
struct Binder {
  // Template specialization.
  //static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) = 0;
};

// Template class for Binder.
// Binder template class is specialized with type.
template <class C>
struct ClassBinder {
  static struct mrb_data_type type_info;
  static void dtor(mrb_state*, void* p) {
    C* instance = static_cast<C*>(p);
    delete instance;
  }

  // Template specialization.
  //static void ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
};
template<class C>
mrb_data_type ClassBinder<C>::type_info = { "???", dtor };

mrb_value raise(mrb_state *mrb, int parameter_index,
                const char* required_type_name, mrb_value value);
mrb_value raisenarg(mrb_state *mrb, mrb_value func_name, int narg, int nparam);

#define CHECKNARG(narg)  {if(narg != NPARAM) RAISENARG(narg);}
#define RAISENARG(narg)  raisenarg(mrb, mrb_cfunc_env_get(mrb, 1), narg, NPARAM)

template<class ... P>
struct TypeChecker {};

template<class P>
struct TypeChecker<P> {
  static void check(mrb_state* mrb, int i, mrb_value* args) {
    if(!Type<P>::check(args[i])) {
      raise(mrb, i, Type<P>::TYPE_NAME, args[i]);
    }
  }
};

template<class P1, class ... P>
struct TypeChecker<P1, P...> {
  static void check(mrb_state* mrb, int i, mrb_value* args) {
    if(!Type<P1>::check(args[i])) {
      raise(mrb, i, Type<P1>::TYPE_NAME, args[i]);
    } else {
      TypeChecker<P...>::check(mrb, i+1, args);
    }
  }
};

template<class ... P>
void check_args(mrb_state* mrb, mrb_value* args) {
  TypeChecker<P...>::check(mrb, 0, args);
}

// void f(void);
template<>
struct Binder<void (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    void (*fp)(void) = (void (*)(void))mrb_cptr(cfunc);
    fp();
    return mrb_nil_value();
  }
};

// R f(void);
template<class R>
struct Binder<R (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    R (*fp)(void) = (R (*)(void))mrb_cptr(cfunc);
    R result = fp();
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(void);
template<class C>
struct ClassBinder<C* (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value ctor(mrb_state* mrb, mrb_value self) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    C* (*ctor)(void) = (C* (*)(void))mrb_cptr(cfunc);
    C* instance = ctor();
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(void) };
template<class C>
struct ClassBinder<void (C::*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value self) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    C* instance = static_cast<C*>(DATA_PTR(self));
    mrb_value cmethod = mrb_cfunc_env_get(mrb, 0);
    typedef void (C::*M)(void);
    M mp = *(M*)RSTRING_PTR(cmethod);
    (instance->*mp)();
    return mrb_nil_value();
  }
};

// class C { R f(void) };
template<class C, class R>
struct ClassBinder<R (C::*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value self) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    C* instance = static_cast<C*>(DATA_PTR(self));
    mrb_value cmethod = mrb_cfunc_env_get(mrb, 0);
    typedef R (C::*M)(void);
    M mp = *(M*)RSTRING_PTR(cmethod);
    R result = (instance->*mp)();
    return Type<R>::ret(mrb, result);
  }
};

// R f(P...);
template<class R, class ...P>
struct Binder<R (*)(P...)> {
  static const int NPARAM = sizeof...(P);
  typedef R (*fun_t)(P...);
  template<size_t ... I>
  static mrb_value apply_bound_function(
      mrb_state* mrb,
      fun_t fp,
      mrb_value* args,
      std::index_sequence<I...>) {
    R result = fp(Type<P>::get(args[I])...);
    return Type<R>::ret(mrb, result);
  }
  static mrb_value call(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    check_args<P...>(mrb, args);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    R (*fp)(P...) = (R (*)(P...))mrb_cptr(cfunc);
    return apply_bound_function(mrb, fp, args, std::index_sequence_for<P...>());
  }
};

// void f(P...);
template<class ... P>
struct Binder<void (*)(P...)> {
  static const int NPARAM = sizeof...(P);
  typedef void (*fun_t)(P...);
  template<size_t ... I>
  static void apply_bound_function(
      fun_t fp,
      mrb_value* args,
      std::index_sequence<I...>) {
    fp(Type<P>::get(args[I])...);
  }
  static mrb_value call(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    check_args<P...>(mrb, args);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    void (*fp)(P...) = (void (*)(P...))mrb_cptr(cfunc);
    apply_bound_function(fp, args, std::index_sequence_for<P...>());
    return mrb_nil_value();
  }
};

// C* ctor(P...);
template<class C, class ... P>
struct ClassBinder<C* (*)(P...)> {
  static const int NPARAM = sizeof...(P);
  typedef C* (*fun_t)(P...);
  template<size_t ... I>
  static C* apply_bound_function(
      fun_t ctor,
      mrb_value* args,
      std::index_sequence<I...>) {
    return ctor(Type<P>::get(args[I])...);
  }
  static mrb_value ctor(mrb_state* mrb, mrb_value self) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    check_args<P...>(mrb, args);
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    C* (*ctor)(P...) = (C* (*)(P...))mrb_cptr(cfunc);
    C* instance = apply_bound_function(ctor, args, std::index_sequence_for<P...>());
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P...) };
template<class C, class ... P>
struct ClassBinder<void (C::*)(P...)> {
  static const int NPARAM = sizeof...(P);
  typedef void (C::*fun_t)(P...);
  template<size_t ... I>
  static void apply_bound_function(
      C* instance,
      fun_t method,
      mrb_value* args,
      std::index_sequence<I...>) {
    (instance->*method)(Type<P>::get(args[I])...);
  }
  static mrb_value call(mrb_state* mrb, mrb_value self) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    check_args<P...>(mrb, args);
    C* instance = static_cast<C*>(DATA_PTR(self));
    mrb_value cmethod = mrb_cfunc_env_get(mrb, 0);
    typedef void (C::*M)(P...);
    M mp = *(M*)RSTRING_PTR(cmethod);
    apply_bound_function(instance, mp, args, std::index_sequence_for<P...>());
    return mrb_nil_value();
  }
};

// class C { R f(P...) };
template<class C, class R, class ... P>
struct ClassBinder<R (C::*)(P...)> {
  static const int NPARAM = sizeof...(P);
  typedef R (C::*fun_t)(P...);
  template<size_t ... I>
  static mrb_value apply_bound_function(
      mrb_state* mrb,
      C* instance,
      fun_t method,
      mrb_value* args,
      std::index_sequence<I...>) {
    R result = (instance->*method)(Type<P>::get(args[I])...);
    return Type<R>::ret(mrb, result);
  }
  static mrb_value call(mrb_state* mrb, mrb_value self) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    CHECKNARG(narg);
    check_args<P...>(mrb, args);
    C* instance = static_cast<C*>(DATA_PTR(self));
    mrb_value cmethod = mrb_cfunc_env_get(mrb, 0);
    typedef R (C::*M)(P...);
    M mp = *(M*)RSTRING_PTR(cmethod);
    return apply_bound_function(mrb, instance, mp, args, std::index_sequence_for<P...>());
  }
};
#undef ARG
#undef CHECK

}  // namespace mrubybind

namespace mrubybind {

//===========================================================================
// MrubyBind - utility class for binding C functions/classes to mruby.
class MrubyBind {
public:
  MrubyBind(mrb_state* mrb);
  MrubyBind(mrb_state* mrb, RClass* mod);
  ~MrubyBind();

  // Bind constant value.
  template <class T>
  void bind_const(const char* name, T v) {
    mrb_define_const(mrb_, mod_, name, Type<T>::ret(mrb_, v));
  }

  // Bind function.
  template <class Func>
  void bind(const char* func_name, Func func_ptr) {
    mrb_sym func_name_s = mrb_intern_cstr(mrb_, func_name);
    mrb_value env[] = {
      mrb_cptr_value(mrb_, (void*)func_ptr),  // 0: c function pointer
      mrb_symbol_value(func_name_s),          // 1: function name
    };
    struct RProc* proc = mrb_proc_new_cfunc_with_env(mrb_, Binder<Func>::call, 2, env);
    mrb_method_t method;
    MRB_METHOD_FROM_PROC(method, proc);
    if (mod_ == mrb_->kernel_module)
      mrb_define_method_raw(mrb_, mod_, func_name_s, method);
    else
      mrb_define_class_method_raw(mrb_, mod_, func_name_s, method);
  }

  // Bind class.
  template <class Func>
  void bind_class(const char* class_name, Func new_func_ptr) {
    struct RClass *tc = mrb_define_class(mrb_, class_name, mrb_->object_class);
    MRB_SET_INSTANCE_TT(tc, MRB_TT_DATA);
    BindInstanceMethod(class_name, "initialize",
                       mrb_cptr_value(mrb_, (void*)new_func_ptr),
                       ClassBinder<Func>::ctor);
  }

  // Bind instance method.
  template <class Method>
  void bind_instance_method(const char* class_name, const char* method_name,
                            Method method_ptr) {
    mrb_value method_pptr_v = mrb_str_new(mrb_,
                                          reinterpret_cast<char*>(&method_ptr),
                                          sizeof(method_ptr));
    BindInstanceMethod(class_name, method_name,
                       method_pptr_v, ClassBinder<Method>::call);
  }

  // Bind static method.
  template <class Method>
  void bind_static_method(const char* class_name, const char* method_name,
                          Method method_ptr) {
    mrb_sym method_name_s = mrb_intern_cstr(mrb_, method_name);
    mrb_value env[] = {
      mrb_cptr_value(mrb_, (void*)method_ptr),  // 0: method pointer
      mrb_symbol_value(method_name_s),          // 1: method name
    };
    struct RProc* proc = mrb_proc_new_cfunc_with_env(mrb_, Binder<Method>::call, 2, env);
    struct RClass* klass = GetClass(class_name);
    mrb_method_t method;
    MRB_METHOD_FROM_PROC(method, proc);
    mrb_define_class_method_raw(mrb_, klass, method_name_s, method);
  }

private:
  void Initialize();

  // Returns mruby class under a module.
  struct RClass* GetClass(const char* class_name);

  // Utility for binding instance method.
  void BindInstanceMethod(const char* class_name, const char* method_name,
                          mrb_value original_func_v,
                          mrb_value (*binder_func)(mrb_state*, mrb_value));

  // Mimic mruby API.
  // TODO: Send pull request to the official mruby repository.
  void
  mrb_define_class_method_raw(mrb_state *mrb, struct RClass *c, mrb_sym mid, mrb_method_t method);

  mrb_state* mrb_;
  RClass* mod_;
  int arena_index_;
};

}  // namespace mrubybind

#endif
