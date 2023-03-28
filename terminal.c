#include <ncurses.h>
#include <string.h>
#include <unistd.h>

WINDOW *create_window(int height, int width, int start_y, int start_x);
void kill_window(WINDOW *window);

WINDOW *create_window(int height, int width, int start_y, int start_x) {
    WINDOW *local_window;
    local_window = newwin(height, width, start_y, start_x);
    box(local_window, 0, 0);

    wrefresh(local_window); // show the new box
    return local_window;

};

void print_center(WINDOW *win, char *string, int height, int width) {
    mvwprintw(win, height/2, (width-strlen(string))/2, "%s", string);
    wrefresh(win);
};

char *algo_choices[] = {
    "bubble",
    "merge",
    "selection",
    "insertion",
    "quick",
    "QUIT",
};
int num_algo_choices = sizeof(algo_choices) / sizeof(algo_choices[0]);

void algo_selection_menu(int width, int height, int selection_size, char **choices) {
    WINDOW *algo_menu = newwin(selection_size+2, 30, width, height);
    int i;
    for(i = 0; i < selection_size; i++) {
        mvprintw(i+1, 2, choices[i]);
    }
};

void screen() {
    WINDOW *term_window;
    int start_x, start_y, width, height, row, col, m_width, m_height;
    int ch;
    initscr(); // start ncurses
    getmaxyx(stdscr, row, col); 
    raw(); // line buffering disabled

    noecho(); // dont print every key user presses
    keypad(stdscr, TRUE);
    start_y = (LINES - row) / 2;
    start_x = (COLS - col) / 2; 
    //printw("Press F2 to exit");
    refresh();
    term_window = create_window(row, col, start_y, start_x);
    m_width = row / 2; //These are the dimensions of the algo menu
    m_height = col / 2;

    while((ch = getch()) != KEY_F(2)) {
        switch(ch) {
            case 'q':
                term_window = create_window(row, col, start_y, start_x);
                print_center(term_window, "You entered 'q', please enter 'F2' to quit", row, col);
                break;
            case 'c':
                delwin(term_window);
                term_window = create_window(row, col, start_y, start_x);
                print_center(term_window, "You entered 'c', please enter 'F2' to quit", row, col);
                break;
            case 's':
                delwin(term_window);
                term_window = create_window(row, col, start_y, start_x);
                //print_center(term_window, "Please select the algorithm you want to use.", row, col);
                algo_selection_menu(m_width, m_height, num_algo_choices, algo_choices);
                break;
        }
    };
    endwin();
};
