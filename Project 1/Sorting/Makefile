CC=g++
CFLAGS=-Wl,--stack-size=0x20000000
#try CFLAGS=-Wl,--stack-size=0x20000000
#?
INC=
LIB=

all:  sorting

sorting:  Driver.o Helper.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^ 

Driver.cpp:  Sorting.hpp Helper.cpp

Helper.cpp:  Helper.hpp

clean:
	rm -f *.o sorting
