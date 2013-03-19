# This code is compiled by mrbc,
# and included into C code.

module MrubyBind
  def MrubyBind.define_function(binder, name, f)
    Kernel.send(:define_method, name) do |*args|
      MrubyBind::call_cfunc(binder, f, *args)
    end
  end

  def MrubyBind.create_class(binder, klass, f)
    k = Kernel.const_set(klass, Class.new)
    k.class_eval do
      define_method(:initialize) do |*args|
        @instance = MrubyBind::call_cfunc(binder, f, *args)
      end
    end
  end

  def MrubyBind.define_class_method(binder, klass, func, f)
    Kernel.const_get(klass).class_eval do
      define_method(func) do |*args|
        MrubyBind::call_cmethod(binder, @instance, f, *args)
      end
    end
  end
end
