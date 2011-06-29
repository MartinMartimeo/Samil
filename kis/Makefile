# Automated Makefile

CC = g++

CFLAGS = -Wall -pedantic -O2
LDFLAGS += 


COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
 


all: kis



kis: $(OBJFILES)

	$(CC) --shared -o $(OBJFILES).so $(OBJFILES) $(LDFLAGS) $(CFLAGS)



%.o: %.cpp

	$(COMPILE) -o $@ $<

clean:
	rm src/*.o

