program: main.c
	gcc -g -lncurses main.c -o show

.PHONY: clean

clean: 
	rm show
