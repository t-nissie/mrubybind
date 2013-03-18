#ifndef __MRUBYBIND_INC__
#define __MRUBYBIND_INC__

// void f();
template<>
struct Binder<void (*)(void)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    void (*fp)(void) = (void (*)(void))p;
    fp();
    return mrb_nil_value();
  }
};

// R f();
template<class R>
struct Binder<R (*)(void)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    R (*fp)(void) = (R (*)(void))p;
    R result = fp();
    return Type<R>::ret(result);
  }
};

// void f(P0);
template<class P0>
struct Binder<void (*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);
    ASSERT(Type<P0>::check(args[0]));
    void (*fp)(P0) = (void (*)(P0))p;
    fp(Type<P0>::get(args[0]));
    return mrb_nil_value();
  }
};

// R f(P0);
template<class R, class P0>
struct Binder<R (*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);
    ASSERT(Type<P0>::check(args[0]));
    R (*fp)(P0) = (R (*)(P0))p;
    R result = fp(Type<P0>::get(args[0]));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1);
template<class P0, class P1>
struct Binder<void (*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2);
    ASSERT(Type<P0>::check(args[0]));
    ASSERT(Type<P1>::check(args[1]));
    void (*fp)(P0, P1) = (void (*)(P0, P1))p;
    fp(Type<P0>::get(args[0]),
       Type<P1>::get(args[1]));
    return mrb_nil_value();
  }
};

// R f(P0, P1);
template<class R, class P0, class P1>
struct Binder<R (*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2);
    ASSERT(Type<P0>::check(args[0]));
    ASSERT(Type<P1>::check(args[1]));
    R (*fp)(P0, P1) = (R (*)(P0, P1))p;
    R result = fp(Type<P0>::get(args[0]),
                  Type<P1>::get(args[1]));
    return Type<R>::ret(mrb, result);
  }
};




// class C { R f(P0) };
template<class C, class R, class P0>
struct Binder<R (C::*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);
    ASSERT(Type<P0>::check(args[0]));
    typedef R (C::*M)(P0);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(Type<P0>::get(args[0]));
    return Type<R>::ret(mrb, result);
  }
};

#endif
