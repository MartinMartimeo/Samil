# Automated Makefile

CC = g++

CFLAGS = -Wall -pedantic -O2
LDFLAGS += -lglut -lGLU


COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp))

KISOBJECTS := $(patsubst %.cpp,%.o,$(wildcard ./kis/*.cpp))
KISFILES := $(patsubst %.cpp,%.so,$(wildcard ./kis/*.cpp))	
	


all: samil kis


kis: $(KISOBJECTS)
	
	$(CC) --shared -o $(KISFILES) $(KISOBJECTS) $(LDFLAGS) $(CFLAGS)

samil: $(OBJFILES)

	$(CC) -o samil $(OBJFILES) $(LDFLAGS) $(CFLAGS)

%.o: %.cpp

	$(COMPILE) -o $@ $<

clean:
	rm src/*.o
	rm kis/*.o
	rm kis/*.so

