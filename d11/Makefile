OBJ1 = 'd11_1.o'
OBJ2 = 'd11_2.o'
CFLAGS = '-g'

all		: d111 d112

d111   : d11_1.o
	gcc -o d111 d11_1.o

d112		: d11_2.o
	gcc -o d112 d11_2.o

d11_1.o :

d11_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d111 d112
