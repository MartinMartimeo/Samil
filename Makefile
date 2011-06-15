# Automated Makefile

CC = g++

CFLAGS = -Wall -O2
LDFLAGS += -lglut -lGLU


COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard /Src/*.cpp))
 


all: samil



samil: $(OBJFILES)

	$(CC) -o samil $(OBJFILES) $(LDFLAGS)



%.o: %.cpp

	$(COMPILE) -o $@ $<

