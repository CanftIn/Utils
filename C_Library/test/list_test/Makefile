INCLUDE = -I ../../include

SRCFLAGS = list_test.c\
         ../../source/list.c

OBJFLAGS = list_test.o\
         ../../source/list.o

EXE = list_test.exe

CC = gcc

$(EXE): $(OBJFLAGS)
	$(CC) -o $@ $(OBJFLAGS)

.c.o:
	$(CC) -o $@ -c $(INCLUDE) $<

clean:
	-rm $(OBJFLAGS)
	-rm $(EXE)