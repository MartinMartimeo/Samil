# Automated Makefile

CC = g++

CFLAGS = -Wall -pedantic -O0 -fPIC
LDFLAGS += -lglut -lGLU


COMPILE = $(CC) $(CFLAGS) -c -g

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp))

KISOBJECTS := $(patsubst %.cpp,%.oo,$(wildcard ./kis/*.cpp))	
	


all: samil kis


kis: $(KISOBJECTS)
	
	

samil: $(OBJFILES)

	$(CC) -o samil $(OBJFILES) $(LDFLAGS) $(CFLAGS)

%.o: %.cpp

	$(COMPILE) -o $@ $<
	
%.oo: %.cpp	
	
	$(COMPILE) -o $@ $<
	$(CC) --shared -o $(patsubst %.oo,%.so,$@) $@ $(LDFLAGS) $(CFLAGS)

clean:
	rm src/*.o
	rm kis/*.oo
	rm kis/*.so

