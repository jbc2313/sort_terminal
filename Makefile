program: main.c
	gcc -g -lncurses -lmenu main.c -o show

.PHONY: clean

clean: 
	rm show
