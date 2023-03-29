program: main.c
	clang -g -lncurses main.c -o show

.PHONY: clean

clean: 
	rm show
