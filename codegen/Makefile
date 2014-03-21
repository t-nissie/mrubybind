
TARGET= ../mrubybind.cc ../mrubybind.h

all: $(TARGET)

clean:
	rm -rf $(TARGET)

../mrubybind.cc:	mrubybind.1.cc mrubybind.3.cc binder.rb
	${MRUBY}/bin/mrbc -Bbinder binder.rb
	(echo "// Do not modify this file directly, this is generated" && \
	 cat mrubybind.1.cc binder.c mrubybind.3.cc) > $@
	rm binder.c

../mrubybind.h:	mrubybind.1.h mrubybind.3.h mrubybind_types.1.h mrubybind_types.3.h gen_template.rb
	(echo "// Do not modify this file directly, this is generated" && \
	 cat mrubybind.1.h mrubybind_types.1.h && \
	 ruby gen_template.rb && \
	 cat mrubybind_types.3.h mrubybind.3.h) > $@

#
