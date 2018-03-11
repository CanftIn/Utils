INCLUDE = -I ../../include

SRCFLAGS = set_test.c\
         ../../source/set.c\
		 ../../source/list.c

OBJFLAGS = set_test.o\
         ../../source/set.o\
		 ../../source/list.o

EXE = set_test.exe

CC = gcc

$(EXE): $(OBJFLAGS)
	$(CC) -o $@ $(OBJFLAGS)

.c.o:
	$(CC) -o $@ -c $(INCLUDE) $<

clean:
	-rm $(OBJFLAGS)
	-rm $(EXE)