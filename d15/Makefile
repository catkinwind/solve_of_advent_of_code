OBJ1 = 'd15_1.o'
OBJ2 = 'd15_2.o'
CFLAGS = '-g'

all		: d151 d152

d151   : d15_1.o
	gcc -o d151 d15_1.o

d152		: d15_2.o
	gcc -o d152 d15_2.o 

d15_1.o :

d15_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d151 d152
