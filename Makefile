.PHONY:	all clean test

all:
	make -C codegen

clean:
	make -C test clean

clean-all:	clean
	make -C codegen clean

test:	all
	make -C test test

#
