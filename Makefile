.PHONY:	all clean test

all:
	make -C codegen

clean:
	make -C codegen clean
	make -C test clean

test:	all
	make -C test test

#
