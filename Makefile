# Set you prefererred CFLAGS/compiler compiler here.
# Our github runner provides gcc-10 by default.
CC ?= cc
CFLAGS ?= -g -Wall -O2
CXX ?= c++
CXXFLAGS ?= -g -Wall -O2
CARGO ?= cargo
RUSTFLAGS ?= -g

.PHONY: clean

# this target should build all executables for all tests
#all:
#	@echo "Please set a concrete build command here"
#	false

# C example:
#all: librw_1.so librw_2.so
#librw_1.so: task-1_1.c
#	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<
#
#librw_2.so: task-1_2.c
#	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

# Rust example:
#all:
#	$(CARGO) build --release

all: librw_1.so librw_2.so tracer test_librw_1 test_librw_2
	true

tracer: tracer.c
	gcc -o tracer tracer.c
	cp -f tracer tests/tracer

test_librw_1: test_librw.c librw_1.so
	gcc -o test_librw_1 test_librw.c librw_1.so

test_librw_2: test_librw.c librw_2.so
	gcc -o test_librw_2 test_librw.c librw_2.so

librw_1.so : task-1_1.c
	gcc -fPIC -c task-1_1.c -o librw_1.o
	gcc -shared librw_1.o -o librw_1.so
	cp -f librw_1.so tests/librw_1.so

librw_2.so : task-1_2.c
	gcc -fPIC -c task-1_2.c -o librw_2.o
	gcc -shared librw_2.o -o librw_2.so
	cp -f librw_2.so tests/librw_2.so

clean:
	rm *.out *.o *.so

# Usually there is no need to modify this
check: all
	$(MAKE) -C tests check
