.PHONY : all clean new

CFLAGS+= -Wall -Og -std=c++11 -g
SRCS= $(wildcard *.cpp)
BIN= ej1	 


all: ej1

$(BIN): $(SRCS)
	g++ $(CFLAGS) -o ../../bin/$(BIN) $(SRCS)

clean:
	rm -f ../../bin/$(BIN) *.o

new: clean all
