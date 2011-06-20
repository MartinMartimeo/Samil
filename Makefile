# Automated Makefile

CC = g++

CFLAGS = -Wall -O2
LDFLAGS += -lglut -lGLU


COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp))
 


all: samil



samil: $(OBJFILES)

	$(CC) -o samil $(OBJFILES) $(LDFLAGS) $(CFLAGS)



%.o: %.cpp

	$(COMPILE) -o $@ $<

clean:
	rm src/*.o

