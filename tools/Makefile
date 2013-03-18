
all: ../mrubybind.dat ../mrubybind.inc

clean:
	echo ''

../mrubybind.dat:	binder.rb
	${MRUBY}/bin/mrbc -Bbinder binder.rb
	mv binder.c ../mrubybind.dat

../mrubybind.inc:	gen_template.rb
	ruby gen_template.rb > ../mrubybind.inc

#
