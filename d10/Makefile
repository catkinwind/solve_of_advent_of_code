OBJ1 = 'd10_1.o'
OBJ2 = 'd10_2.o'
CFLAGS = '-g3'

all		: d101 d102

d101   : d10_1.o
	gcc -o d101 d10_1.o

d102		: d10_2.o
	gcc -o d102 d10_2.o

d10_1.o :

d10_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d101 d102
