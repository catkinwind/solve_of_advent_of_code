OBJ1 = 'd9_1.o'
OBJ2 = 'd9_2.o'
CFLAGS = '-g3'

all		: d91 d92

d91   : d9_1.o
	gcc -o d91 d9_1.o

d92		: d9_2.o
	gcc -o d92 d9_2.o

d9_1.o :

d9_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d91 d92
