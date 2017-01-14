OBJ1 = 'd6_1.o'
OBJ2 = 'd6_2.o'
CFLAGS = '-g'

all		: d61 d62

d61   : d6_1.o
	gcc -o d61 d6_1.o

d62		: d6_2.o
	gcc -o d62 d6_2.o

d6_1.o :

d6_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d61 d62
