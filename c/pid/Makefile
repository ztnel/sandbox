CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address

all: main

main: main.c pid.c
	$(CC) $(CFLAGS) main.c pid.c -o pid

clean:
	rm -f main