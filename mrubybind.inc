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

// C* ctor(void);
template<class C>
struct ClassBinder<C* (*)(void)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 0); 
    C* (*ctor)(void) = (C* (*)(void))p;
    C* instance = ctor();
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(void) };
template<class C>
struct ClassBinder<void (C::*)(void)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(void);
    M method = *(M*)pp;
    (instance->*method)();
    return mrb_nil_value();
  }
};

// class C { R f(void) };
template<class C, class R>
struct ClassBinder<R (C::*)(void)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 0);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(void);
    M method = *(M*)pp;
    R result = (instance->*method)();
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

// C* ctor(P0);
template<class C, class P0>
struct ClassBinder<C* (*)(P0)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 1); ASSERT(CHECK(0));
    C* (*ctor)(P0) = (C* (*)(P0))p;
    C* instance = ctor(ARG(0));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0) };
template<class C, class P0>
struct ClassBinder<void (C::*)(P0)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 1);ASSERT(CHECK(0));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0);
    M method = *(M*)pp;
    (instance->*method)(ARG(0));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0>
struct ClassBinder<R (C::*)(P0)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 1);ASSERT(CHECK(0));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0));
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

// C* ctor(P0, P1);
template<class C, class P0, class P1>
struct ClassBinder<C* (*)(P0, P1)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 2); ASSERT(CHECK(0)); ASSERT(CHECK(1));
    C* (*ctor)(P0, P1) = (C* (*)(P0, P1))p;
    C* instance = ctor(ARG(0), ARG(1));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0, P1) };
template<class C, class P0, class P1>
struct ClassBinder<void (C::*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 2);ASSERT(CHECK(0)); ASSERT(CHECK(1));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1);
    M method = *(M*)pp;
    (instance->*method)(ARG(0), ARG(1));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1) };
template<class C, class R, class P0, class P1>
struct ClassBinder<R (C::*)(P0, P1)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 2);ASSERT(CHECK(0)); ASSERT(CHECK(1));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0), ARG(1));
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

// C* ctor(P0, P1, P2);
template<class C, class P0, class P1, class P2>
struct ClassBinder<C* (*)(P0, P1, P2)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 3); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    C* (*ctor)(P0, P1, P2) = (C* (*)(P0, P1, P2))p;
    C* instance = ctor(ARG(0), ARG(1), ARG(2));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0, P1, P2) };
template<class C, class P0, class P1, class P2>
struct ClassBinder<void (C::*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 3);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2);
    M method = *(M*)pp;
    (instance->*method)(ARG(0), ARG(1), ARG(2));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2) };
template<class C, class R, class P0, class P1, class P2>
struct ClassBinder<R (C::*)(P0, P1, P2)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 3);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0), ARG(1), ARG(2));
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

// C* ctor(P0, P1, P2, P3);
template<class C, class P0, class P1, class P2, class P3>
struct ClassBinder<C* (*)(P0, P1, P2, P3)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 4); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    C* (*ctor)(P0, P1, P2, P3) = (C* (*)(P0, P1, P2, P3))p;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0, P1, P2, P3) };
template<class C, class P0, class P1, class P2, class P3>
struct ClassBinder<void (C::*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 4);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3);
    M method = *(M*)pp;
    (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3) };
template<class C, class R, class P0, class P1, class P2, class P3>
struct ClassBinder<R (C::*)(P0, P1, P2, P3)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 4);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3));
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

// C* ctor(P0, P1, P2, P3, P4);
template<class C, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 5); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    C* (*ctor)(P0, P1, P2, P3, P4) = (C* (*)(P0, P1, P2, P3, P4))p;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0, P1, P2, P3, P4) };
template<class C, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 5);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4);
    M method = *(M*)pp;
    (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 5);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
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

// C* ctor(P0, P1, P2, P3, P4, P5);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5)> {
  static void ctor(mrb_state* mrb, mrb_value self, void* p, mrb_value* args, int narg) {
    ASSERT(narg == 6); ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    C* (*ctor)(P0, P1, P2, P3, P4, P5) = (C* (*)(P0, P1, P2, P3, P4, P5))p;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = instance;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 6);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5);
    M method = *(M*)pp;
    (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5)> {
  static mrb_value call(mrb_state* mrb, mrb_value self, void* pp, mrb_value* args, int narg) {
    ASSERT(narg == 6);ASSERT(CHECK(0)); ASSERT(CHECK(1)); ASSERT(CHECK(2)); ASSERT(CHECK(3)); ASSERT(CHECK(4)); ASSERT(CHECK(5));
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5);
    M method = *(M*)pp;
    R result = (instance->*method)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return Type<R>::ret(mrb, result);
  }
};

#undef ARG
#undef CHECK
