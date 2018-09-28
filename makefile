CXX = g++
RM = rm -rf
CFLAGS += -Wall
INC = -I ./src/include
CPPFLAGS = --std=c++11 -Wall $(INC)

HEADERS=$(shell ls src/include/)
SRCS=$(shell ls src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: prep bin clean


finite:		$(OBJS)
		$(CXX) $(CPPFLAGS) -o -Dfinite_queue main_finite_queue $(OBJS)

infinite:	$(OBJS)
		$(CXX) $(CPPFLAGS) -o -Dinfinite_queue main_infinite_queue $(OBJS)		

main.o: 	$(SRCS) $(HEADERS)

prep:
		if [[ ! -d "output" ]] ; then mkdir output; fi

bin:		infinite finite
		if [[ ! -d "bin" ]] ; then mkdir bin; fi;
		mv main* bin

clean:
		$(RM) $(OBJS)

distclean: 	clean
		$(RM) main
		$(RM) bin output
