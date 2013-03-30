# This code is compiled by mrbc,
# and included into C code.

module MrubyBind
  def MrubyBind.define_function(binder, name, f)
    Kernel.send(:define_method, name) do |*args|
      MrubyBind::call_cfunc(binder, f, *args)
    end
  end

  def MrubyBind.bind_class(binder, klass, ctor)
    Kernel.const_get(klass).class_eval do
      define_method(:initialize) do |*args|
        MrubyBind::call_ctorfunc(binder, self, ctor, *args)
      end
    end
  end

  def MrubyBind.bind_class_method(binder, klass, func, f)
    Kernel.const_get(klass).class_eval do
      define_method(func) do |*args|
        MrubyBind::call_cmethod(binder, self, f, *args)
      end
    end
  end
end
