OBJ1 = 'd4_1.o'
OBJ2 = 'd4_2.o'
CFLAGS = '-g'

all		: d41 d42

d41   : d4_1.o
	gcc -o d41 d4_1.o

d42		: d4_2.o
	gcc -o d42 d4_2.o

d4_1.o :

d4_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d41 d42
