
TARGET= ../mrubybind.dat ../mrubybind.inc

all: $(TARGET)

clean:
	rm -rf $(TARGET)

../mrubybind.dat:	binder.rb
	${MRUBY}/bin/mrbc -Bbinder binder.rb
	mv binder.c ../mrubybind.dat

../mrubybind.inc:	gen_template.rb
	ruby gen_template.rb > ../mrubybind.inc

#
