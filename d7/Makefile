OBJ1 = 'd7_1.o'
OBJ2 = 'd7_2.o'
CFLAGS = '-g'

all		: d71 d72

d71   : d7_1.o
	gcc -o d71 d7_1.o

d72		: d7_2.o
	gcc -o d72 d7_2.o

d7_1.o :

d7_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d71 d72
