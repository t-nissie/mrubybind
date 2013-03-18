
INC=-I $(MRUBY)/include -I ..
LIB=-L $(MRUBY)/build/host/lib -lmruby

all: a.out

clean:
	rm -rf *.o a.out

a.out:	main.cc ../mrubybind.cc ../mrubybind.h ../mrubybind.inc ../mrubybind.dat
	g++ -o a.out main.cc ../mrubybind.cc $(INC) $(LIB)

#
