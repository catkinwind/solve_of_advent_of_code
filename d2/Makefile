OBJ1 = 'd2_1.o'
OBJ2 = 'd2_2.o'
CFLAGS = '-g'

all		: d21 d22

d21   : d2_1.o
	gcc -o d21 d2_1.o

d22		: d2_2.o
	gcc -o d22 d2_2.o

d2_1.o :

d2_2.o :

#d2_1.c
#	gcc -c d2_1.c -o d21.o

.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d21 d22
