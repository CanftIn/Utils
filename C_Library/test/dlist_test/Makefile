INCLUDE = -I ../../include

SRCFLAGS = dlist_test.c\
         ../../source/dlist.c

OBJFLAGS = dlist_test.o\
         ../../source/dlist.o

EXE = dlist_test.exe

CC = gcc

$(EXE): $(OBJFLAGS)
	$(CC) -o $@ $(OBJFLAGS)

.c.o:
	$(CC) -o $@ -c $(INCLUDE) $<

clean:
	-rm $(OBJFLAGS)
	-rm $(EXE)