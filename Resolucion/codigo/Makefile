.PHONY : all clean new

CFLAGS+= -Wall -O2 -std=c++11 -g
SRCS= $(wildcard *.cpp)
BIN= main	 


all: main 

$(BIN): $(SRCS)
	g++ $(CFLAGS) -o ../bin/$(BIN) $(SRCS)

clean:
	rm -f ../bin/$(BIN) *.o

new: clean all
