CC = g++
INCDIR += ./include/
LIBDIR += ./lib/
# CFLAGS = 
LFLAGS = -lmingw32 -lSDL2main -lSDL2
all:
	$(CC) main.cpp -o line -I$(INCDIR) -L$(LIBDIR) $(LFLAGS)
clean:
	rm line
run:
	./line
