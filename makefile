CXX=g++
RM = rm -f
CPPFLAGS=-I ./src/include

HEADERS=$(shell ls src/include/)
SRCS=$(shell ls src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: main clean

main: 		$(OBJS)
		$(CXX) $(CPPFLAGS) -o main $(OBJS)

main.o: 	$(SRCS) $(HEADERS)

clean:
		$(RM) $(OBJS)

distclean: 	clean
		$(RM) main
