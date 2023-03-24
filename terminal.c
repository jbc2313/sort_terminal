#include <ncurses.h>

WINDOW *create_window(int height, int width, int start_y, int start_x);
void kill_window(WINDOW *window);

WINDOW *create_window(int height, int width, int start_y, int start_x) {
    WINDOW *local_window;
    local_window = newwin(height, width, start_y, start_x);
    box(local_window, 0, 0);

    wrefresh(local_window); // show the new box
    return local_window;

};

void screen() {
    WINDOW *term_window;
    int start_x, start_y, width, height, row, col;
    int ch;
    initscr(); // start ncurses
    getmaxyx(stdscr, row, col); 
    raw(); // line buffering disabled

    noecho(); // dont print every key user presses
    keypad(stdscr, TRUE);
    start_y = (LINES - row) / 2;
    start_x = (COLS - col) / 2; 
    printw("Press F2 to exit");
    refresh();
    term_window = create_window(row, col, start_y, start_x);
   

};
