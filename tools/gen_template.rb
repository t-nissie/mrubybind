
MAX_PARAM = 6

HEADER = <<EOD
\#define ARG(i)  Type<P##i>::get(args[i])
\#define CHECK(i)  Type<P##i>::check(args[i])

EOD

FUNC_TMPL = <<EOD
// void f(%PARAMS%);
template<%CLASSES0%>
struct Binder<void (*)(%PARAMS%)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == %NPARAM%);%ASSERTS%
    void (*fp)(%PARAMS%) = (void (*)(%PARAMS%))p;
    fp(%ARGS%);
    return mrb_nil_value();
  }
};

// R f(%PARAMS%);
template<class R%CLASSES1%>
struct Binder<R (*)(%PARAMS%)> {
  static mrb_value call(mrb_state* mrb, void* p, mrb_value* args, int narg) {
    ASSERT(narg == %NPARAM%); %ASSERTS%
    R (*fp)(%PARAMS%) = (R (*)(%PARAMS%))p;
    R result = fp(%ARGS%);
    return Type<R>::ret(mrb, result);
  }
};

EOD

METHOD_TMPL = <<EOD
// class C { void f(P0) };
template<class C%CLASSES1%>
struct Binder<void (C::*)(%PARAMS%)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == %NPARAM%);%ASSERTS%
    typedef void (C::*M)(%PARAMS%);
    M method = *(M*)p;
    (((C*)o)->*method)(%ARGS%);
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R%CLASSES1%>
struct Binder<R (C::*)(%PARAMS%)> {
  static mrb_value call(mrb_state* mrb, void* o, void* p, mrb_value* args, int narg) {
    ASSERT(narg == %NPARAM%);%ASSERTS%
    typedef R (C::*M)(%PARAMS%);
    M method = *(M*)p;
    R result = (((C*)o)->*method)(%ARGS%);
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
    asserts = ''
  else
    params = (0...nparam).map {|i| "P#{i}"}.join(', ')
    args = (0...nparam).map {|i| "ARG(#{i})"}.join(', ')
    classes = (0...nparam).map {|i| "class P#{i}"}.join(', ')
    asserts = (0...nparam).map {|i| "ASSERT(CHECK(#{i}));"}.join(' ')
  end

  return str.gsub(/%PARAMS%/, params).
             gsub(/%NPARAM%/, nparam.to_s).
             gsub(/%ARGS%/, args).
             gsub(/%CLASSES0%/, classes).
             gsub(/%CLASSES1%/, classes.empty? ? '' : ', ' + classes).
             gsub(/%ASSERTS%/, asserts)
end

print HEADER
(0..MAX_PARAM).each do |nparam|
  print embed_template(FUNC_TMPL, nparam)
  print embed_template(METHOD_TMPL, nparam)
end
print FOOTER

#
