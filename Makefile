program: main.c
	gcc -g -lncurses main.c -o sort_terminal

.PHONY: clean

clean: 
	rm sort_terminal
