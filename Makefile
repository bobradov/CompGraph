#
# Netlist Makefile
#

include Makefile.include

CFLAGS = -g -std=c++14

INCLUDE = -I$(ROOT)

LDFLAGS  = -stdlib=libc++
LINKLIBS = -lstdc++

#----- Compilation Rules

.cpp.o:
	$(CC) -c $(CFLAGS) -I$(ROOT) $(INCLUDE) $<

all: test1

OBJS = FunctionGraph.o

test1: test1.o $(OBJS)
	$(CC) $(BIND_AT_LOAD) -o test1 test1.o \
	$(OBJS) \
	$(LDFLAGS) $(LINKLIBS)  

clean:
	rm -f test1
	rm -f *.o
	rm -f core.*
	rm -f core

depend:
	g++ -MM *.cpp > make.depend

include make.depend
