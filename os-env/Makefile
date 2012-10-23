AS      =as
LD      =ld
CC      =g++
AR      =ar



CCFLAGS =  -std=c++0x -g -Os
CCFLAGS += -I./ 
LDFLAGS = -lpthread
SRCS = 
OBJS := $(SRCS:.cc=.o)

tests = testTime.cc testCompile.cc
testOBJs := $(tests:.cc=.o)
testExe := $(testOBJs:.o=.exe)

all:$(testOBJs) $(OBJS) $(testExe)

$(testExe):%.exe:%.o
	$(CC) -o $@ $< $(OBJS)  $(LDFLAGS) 

$(OBJS):%.o:%.cc
	$(CC) -c $(CCFLAGS) -o $@ $<
$(testOBJs):%.o:./test/%.cc
	$(CC) -c $(CCFLAGS) -o $@ $<

.SUFFIXES:
.SUFFIXES: .c .o

.PHONY:clean
clean: 
	$(RM) *.o 
	$(RM) *.exe
