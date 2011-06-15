# Automated Makefile

CC = g++

CFLAGS = -Wall -O2
LDFLAGS += -lglut -lGLU


COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard /Src/*.cpp))
 


all: samil



samil: $(OBJFILES)

	$(CC) -o saiml $(OBJFILES) $(LDFLAGS)



%.o: %.cpp

	$(COMPILE) -o $@ $<

