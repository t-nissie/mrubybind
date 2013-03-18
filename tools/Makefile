
all: ../mrubybind.dat

clean:
	echo ''

../mrubybind.dat:	binder.rb
	${MRUBY}/bin/mrbc -Bbinder binder.rb
	mv binder.c ../mrubybind.dat

#
