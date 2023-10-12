all : s-talk

s-talk: 
	gcc -g -pthread -pedantic -Wall -Werror -o s-talk list.o blah2.o

list.o: list.c
	gcc -g -pedantic -Wall -Werror -c list.c

clean:

# -lpthread (maybe)
