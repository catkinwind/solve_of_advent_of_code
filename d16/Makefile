OBJ1 = 'd16_1.o'
OBJ2 = 'd16_2.o'
CFLAGS = '-g'

all		: d161 d162

d161   : d16_1.o
	gcc -o d161 d16_1.o

d162		: d16_2.o
	gcc -o d162 d16_2.o 

d16_1.o :

d16_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d161 d162
