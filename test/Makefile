
INC=-I $(MRUBY)/include -I ..
LIB=-L $(MRUBY)/build/host/lib -lmruby

MRUBYBIND_SRCDIR=..
MRUBYBIND_OBJ=mrubybind.o

SRCS=$(wildcard *.cc)
EXES=$(SRCS:%.cc=%)

CXXFLAGS=-Wall -Wextra -Werror

all:	$(EXES)

clean:
	rm -rf *.o $(EXES)

test:	$(EXES)
	./test.sh

%.o:	%.cc
	g++ -c -o $@ $(INC) $(CXXFLAGS) $<

mrubybind.o:	$(MRUBYBIND_SRCDIR)/mrubybind.cc
	g++ -c -o $@ $(INC) $(CXXFLAGS) $<

void:	void.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

int:	int.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

float:	float.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

string:	string.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

cptr:	cptr.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

class:	class.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

module:	module.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

wrong_type:	wrong_type.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

wrong_arg_num:	wrong_arg_num.o $(MRUBYBIND_OBJ)
	g++ -o $@ $^ $(LIB)

#
