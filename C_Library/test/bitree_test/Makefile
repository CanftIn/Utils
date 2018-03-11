INCLUDE = -I ../../include

SRCFLAGS = bitree_test.c\
         ../../source/bitree.c\
		 ../../source/list.c

OBJFLAGS = bitree_test.o\
         ../../source/bitree.o\
		 ../../source/list.o

EXE = bitree_test.exe

CC = gcc

$(EXE): $(OBJFLAGS)
	$(CC) -o $@ $(OBJFLAGS)

.c.o:
	$(CC) -o $@ -c $(INCLUDE) $<

clean:
	-rm $(OBJFLAGS)
	-rm $(EXE)