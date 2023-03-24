#include <ncurses.h>

WINDOW *create_window(int height, int width, int start_y, int start_x);
void kill_window(WINDOW *window);

void screen() {
   WINDOW *term_window;
   int start_x, start_y, width, height;
   int ch;
   initscr();
   raw();


};
