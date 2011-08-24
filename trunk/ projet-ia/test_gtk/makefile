CC     = gcc
CFLAGS = `pkg-config --cflags gtk+-2.0 gmodule-2.0` 
LIBS   = `pkg-config --libs   gtk+-2.0 gmodule-2.0` 
DEBUG  = -Wall -g
 
OBJECTS = dialog1.o
 
.PHONY: clean
 
all: dialog1
 
dialog1: $(OBJECTS)
	$(CC) $(DEBUG) $(LIBS) $(OBJECTS) -o $@
 
dialog1.o: dialog1.c 
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@
 

 
clean:
	rm -f *.o dialog1