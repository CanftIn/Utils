INCLUDE = -I ../../include

SRCFLAGS = list_case.c\
         ../../source/list.c

OBJFLAGS = list_case.o\
         ../../source/list.o

EXE = list_case.exe

CC = gcc

$(EXE): $(OBJFLAGS)
	$(CC) -o $@ $(OBJFLAGS)

.c.o:
	$(CC) -o $@ -c $(INCLUDE) $<

clean:
	-rm $(OBJFLAGS)
	-rm $(EXE)