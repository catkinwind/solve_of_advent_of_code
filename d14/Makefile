OBJ1 = 'd14_1.o'
OBJ2 = 'd14_2.o'
CFLAGS = '-g'

all		: d141 d142

d141   : d14_1.o
	gcc -o d141 d14_1.o -lcrypto

d142		: d14_2.o
	gcc -o d142 d14_2.o -lcrypto

d14_1.o :

d14_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d141 d142
