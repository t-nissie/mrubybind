
MAX_PARAM = 10

HEADER = <<EOD
// Following code is generated from gen_template.rb
\#define ARG(i)  Type<P##i>::get(args[i])
\#define CHECK(i)  {if(!Type<P##i>::check(args[i])) return RAISE(i);}
\#define RAISE(i)  raise(mrb, i, Type<P##i>::TYPE_NAME, args[i])

EOD

FUNC_TMPL = <<EOD
// void f(%PARAMS%);
template<%CLASSES0%>
struct Binder<void (*)(%PARAMS%)> {
  static const int NPARAM = %NPARAM%;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    %ASSERTS%
    void (*fp)(%PARAMS%) = (void (*)(%PARAMS%))func_ptr;
    fp(%ARGS%);
    return mrb_nil_value();
  }
  static mrb_value call2(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    %ASSERTS%
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    void (*fp)(%PARAMS%) = (void (*)(%PARAMS%))mrb_voidp(cfunc);
    fp(%ARGS%);
    return mrb_nil_value();
  }
};

// R f(%PARAMS%);
template<class R%CLASSES1%>
struct Binder<R (*)(%PARAMS%)> {
  static const int NPARAM = %NPARAM%;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    %ASSERTS%
    R (*fp)(%PARAMS%) = (R (*)(%PARAMS%))func_ptr;
    R result = fp(%ARGS%);
    return Type<R>::ret(mrb, result);
  }
  static mrb_value call2(mrb_state* mrb, mrb_value /*self*/) {
    mrb_value* args;
    int narg;
    mrb_get_args(mrb, "*", &args, &narg);
    %ASSERTS%
    mrb_value cfunc = mrb_cfunc_env_get(mrb, 0);
    R (*fp)(%PARAMS%) = (R (*)(%PARAMS%))mrb_voidp(cfunc);
    R result = fp(%ARGS%);
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(%PARAMS%);
template<class C%CLASSES1%>
struct ClassBinder<C* (*)(%PARAMS%)> {
  static const int NPARAM = %NPARAM%;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    %ASSERTS%
    C* (*ctor)(%PARAMS%) = (C* (*)(%PARAMS%))new_func_ptr;
    C* instance = ctor(%ARGS%);
    DATA_PTR(self) = instance;
    return self;
  }
};

EOD

METHOD_TMPL = <<EOD
// class C { void f(%PARAMS%) };
template<class C%CLASSES1%>
struct ClassBinder<void (C::*)(%PARAMS%)> {
  static const int NPARAM = %NPARAM%;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    %ASSERTS%
    C* instance = static_cast<C*>(DATA_PTR(self));
    typedef void (C::*M)(%PARAMS%);
    M mp = *(M*)method_pptr;
    (instance->*mp)(%ARGS%);
    return mrb_nil_value();
  }
};

// class C { R f(%PARAMS%) };
template<class C, class R%CLASSES1%>
struct ClassBinder<R (C::*)(%PARAMS%)> {
  static const int NPARAM = %NPARAM%;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    %ASSERTS%
    C* instance = static_cast<C*>(DATA_PTR(self));
    typedef R (C::*M)(%PARAMS%);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(%ARGS%);
    return Type<R>::ret(mrb, result);
  }
};

EOD

FOOTER = <<EOD
\#undef ARG
\#undef CHECK
EOD

def embed_template(str, nparam)
  if nparam == 0
    params = 'void'
    args = ''
    classes = ''
    asserts = '(void)(mrb);(void)(args);(void)(narg);'  # Surppress warning.
  else
    params = (0...nparam).map {|i| "P#{i}"}.join(', ')
    args = (0...nparam).map {|i| "ARG(#{i})"}.join(', ')
    classes = (0...nparam).map {|i| "class P#{i}"}.join(', ')
    asserts = (0...nparam).map {|i| "(void)(narg); CHECK(#{i});"}.join(' ')
  end

  table = {
    '%PARAMS%' => params,
    '%NPARAM%' => nparam.to_s,
    '%ARGS%' => args,
    '%CLASSES0%' => classes,
    '%CLASSES1%' => classes.empty? ? '' : ', ' + classes,
    '%ASSERTS%' => asserts
  }

  return str.gsub(/(#{table.keys.join('|')})/) {|k| table[k]}
end

print HEADER
(0..MAX_PARAM).each do |nparam|
  print embed_template(FUNC_TMPL, nparam)
  print embed_template(METHOD_TMPL, nparam)
end
print FOOTER

#
