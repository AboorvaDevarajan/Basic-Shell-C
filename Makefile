CC=gcc
FLAGS=-O0 -ggdb3 -Wall -Werror

all:
	$(CC) $(FLAGS) unixShell.c -o us

clean:
	rm -rf us
