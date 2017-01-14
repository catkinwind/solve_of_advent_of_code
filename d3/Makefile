OBJ1 = 'd3_1.o'
OBJ2 = 'd3_2.o'
CFLAGS = '-g'

all		: d31 d32

d31   : d3_1.o
	gcc -o d31 d3_1.o

d32		: d3_2.o
	gcc -o d32 d3_2.o

d3_1.o :

d3_2.o :


.PHONY: clean all
clean :
	rm $(OBJ1) $(OBJ2) d31 d32
