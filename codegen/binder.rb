# This code is compiled by mrbc,
# and included into C code.

module MrubyBind
  def MrubyBind.bind_static_method(mod, binder, class_name, method_name, method_ptr, nparam)
    mod.const_get(class_name).class_eval do
      self.class.instance_eval do
        define_method(method_name) do |*args|
          if args.size != nparam
            raise ArgumentError.new("'#{method_name}': wrong number of arguments (#{args.size} for #{nparam})")
          end
          MrubyBind::call_cfunc(binder, method_ptr, *args)
        end
      end
    end
  end
end
