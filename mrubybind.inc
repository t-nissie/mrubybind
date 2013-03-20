// This file is generated from gen_template.rb
#define ARG(i)  Type<P##i>::get(args[i])
#define CHECK(i)  Type<P##i>::check(args[i])

// void f(void);
template<>
struct Binder<void (*)(void)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    void (*fp)(void) = (void (*)(void))p;
    fp();
    return mrb_nil_value();
  }
};

// R f(void);
template<class R>
struct Binder<R (*)(void)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0); 
    R (*fp)(void) = (R (*)(void))p;
    R result = fp();
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C>
struct Binder<void (C::*)(void)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    typedef void (C::*M)(void);
    M method = *(M*)p;
    (((C*)o)->*method)();
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R>
struct Binder<R (C::*)(void)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    typedef R (C::*M)(void);
    M method = *(M*)p;
    R result = (((C*)o)->*method)();
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0);
template<class P0>
struct Binder<void (*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);ASSERT(CHECK(0));
    void (*fp)(P0) = (void (*)(P0))p;
    fp(ARG(0));
    return mrb_nil_value();
  }
};

// R f(P0);
template<class R, class P0>
struct Binder<R (*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1); ASSERT(CHECK(0));
    R (*fp)(P0) = (R (*)(P0))p;
    R result = fp(ARG(0));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0>
struct Binder<void (C::*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);ASSERT(CHECK(0));
    typedef void (C::*M)(P0);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0>
struct Binder<R (C::*)(P0)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1);ASSERT(CHECK(0));
    typedef R (C::*M)(P0);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1);
template<class P0, class P1>
struct Binder<void (*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2);ASSERT(CHECK(0)); ASSERT(CHECK(1));
    void (*fp)(P0, P1) = (void (*)(P0, P1))p;
    fp(ARG(0), ARG(1));
    return mrb_nil_value();
  }
};

// R f(P0, P1);
template<class R, class P0, class P1>
struct Binder<R (*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2); ASSERT(CHECK(0)); ASSERT(CHECK(1));
    R (*fp)(P0, P1) = (R (*)(P0, P1))p;
    R result = fp(ARG(0), ARG(1));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0, class P1>
struct Binder<void (C::*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2);ASSERT(CHECK(0)); ASSERT(CHECK(1));
    typedef void (C::*M)(P0, P1);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0), ARG(1));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0, class P1>
struct Binder<R (C::*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2);ASSERT(CHECK(0)); ASSERT(CHECK(1));
    typedef R (C::*M)(P0, P1);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0), ARG(1));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2);
template<class P0, class P1, class P2>
struct Binder<void (*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 3);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    void (*fp)(P0, P1, P2) = (void (*)(P0, P1, P2))p;
    fp(ARG(0), ARG(1), ARG(2));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2);
template<class R, class P0, class P1, class P2>
struct Binder<R (*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 3); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    R (*fp)(P0, P1, P2) = (R (*)(P0, P1, P2))p;
    R result = fp(ARG(0), ARG(1), ARG(2));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0, class P1, class P2>
struct Binder<void (C::*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 3);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    typedef void (C::*M)(P0, P1, P2);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0), ARG(1), ARG(2));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0, class P1, class P2>
struct Binder<R (C::*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 3);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    typedef R (C::*M)(P0, P1, P2);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0), ARG(1), ARG(2));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3);
template<class P0, class P1, class P2, class P3>
struct Binder<void (*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 4);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    void (*fp)(P0, P1, P2, P3) = (void (*)(P0, P1, P2, P3))p;
    fp(ARG(0), ARG(1), ARG(2), ARG(3));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3);
template<class R, class P0, class P1, class P2, class P3>
struct Binder<R (*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 4); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    R (*fp)(P0, P1, P2, P3) = (R (*)(P0, P1, P2, P3))p;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0, class P1, class P2, class P3>
struct Binder<void (C::*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 4);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    typedef void (C::*M)(P0, P1, P2, P3);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0, class P1, class P2, class P3>
struct Binder<R (C::*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 4);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    typedef R (C::*M)(P0, P1, P2, P3);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4);
template<class P0, class P1, class P2, class P3, class P4>
struct Binder<void (*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 5);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    void (*fp)(P0, P1, P2, P3, P4) = (void (*)(P0, P1, P2, P3, P4))p;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4);
template<class R, class P0, class P1, class P2, class P3, class P4>
struct Binder<R (*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 5); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    R (*fp)(P0, P1, P2, P3, P4) = (R (*)(P0, P1, P2, P3, P4))p;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0, class P1, class P2, class P3, class P4>
struct Binder<void (C::*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 5);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    typedef void (C::*M)(P0, P1, P2, P3, P4);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4>
struct Binder<R (C::*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 5);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    typedef R (C::*M)(P0, P1, P2, P3, P4);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5);
template<class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 6);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    void (*fp)(P0, P1, P2, P3, P4, P5) = (void (*)(P0, P1, P2, P3, P4, P5))p;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 6); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    R (*fp)(P0, P1, P2, P3, P4, P5) = (R (*)(P0, P1, P2, P3, P4, P5))p;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return Type<R>::ret(mrb, result);
  }
};

// class C { void f(P0) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<void (C::*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 6);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5);
    M method = *(M*)p;
    (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<R (C::*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 6);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return Type<R>::ret(mrb, result);
  }
};

#undef ARG
#undef CHECK
