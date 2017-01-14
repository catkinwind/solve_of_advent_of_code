OBJ1 = 'd5_1.o'
OBJ2 = 'd5_2.o'
CFLAGS = '-g'

all		: d51 d52

d51   : d5_1.o
	gcc -o d51 d5_1.o -lcrypto

d52		: d5_2.o
	gcc -o d52 d5_2.o -lcrypto

d5_1.o :

d5_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d51 d52
