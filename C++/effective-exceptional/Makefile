AS      =as
LD      =ld
CC      =g++
AR      =ar

CFLAGS = -g -Wall -pedantic -Wall -std=c++0x
CFLAGS += 
LDFLAGS = -g -lpthread
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.exe)


all:$(OBJS)
	echo compile OBJ $(OBJS)
	echo $(CPP)

$(OBJS):%.exe:%.cpp
	$(CC) -g -o $@ $< $(CFLAGS) $(LDFLAGS)

.PHONY:clean
clean: 
	$(RM) ${OBJS}
