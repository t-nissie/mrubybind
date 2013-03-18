# This code is compiled by mrbc,
# and included into C code.

def mrubybind_define_function(binder, name, f)
  Kernel.send(:define_method, name) do |*args|
    mrubybind_call_cfunc(binder, f, *args)
  end
end

def mrubybind_create_class(binder, klass, f)
  k = Kernel.const_set(klass, Class.new)
  k.class_eval do
    define_method(:initialize) do |*args|
      @instance = mrubybind_call_cfunc(binder, f, *args)
    end
  end
end

def mrubybind_define_class_method(binder, klass, func, f)
  Kernel.const_get(klass).class_eval do
    define_method(func) do |*args|
      mrubybind_call_cmethod(binder, @instance, f, *args)
    end
  end
end
