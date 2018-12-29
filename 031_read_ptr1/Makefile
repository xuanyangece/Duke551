FLAGS=-std=gnu99 -Wall -Werror -pedantic
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc $(FLAGS) -c test.c
