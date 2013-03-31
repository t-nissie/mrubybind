# This code is compiled by mrbc,
# and included into C code.

module MrubyBind
  def MrubyBind.define_function(binder, func_name, func_ptr)
    Kernel.send(:define_method, func_name) do |*args|
      MrubyBind::call_cfunc(binder, func_ptr, *args)
    end
  end

  def MrubyBind.bind_class(binder, class_name, new_func_ptr)
    Kernel.const_get(class_name).class_eval do
      define_method(:initialize) do |*args|
        MrubyBind::call_ctorfunc(binder, self, new_func_ptr, *args)
      end
    end
  end

  def MrubyBind.bind_class_method(binder, class_name, method_name, method_ptr)
    Kernel.const_get(class_name).class_eval do
      define_method(method_name) do |*args|
        MrubyBind::call_cmethod(binder, self, method_ptr, *args)
      end
    end
  end
end
