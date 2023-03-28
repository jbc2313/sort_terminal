#include <ncurses.h>
#include <string.h>
#include <unistd.h>

//WINDOW *create_window(int height, int width, int start_y, int start_x);
//void kill_window(WINDOW *window);

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

void algo_selection_menu(int height, int width, int selection_size, char **choices) {
    WINDOW *algo_menu = create_window(selection_size+10, 50, height-10, width-20);
    int i;
    char teststring[] = "Print this out!";
    for(i = 0; i < selection_size; i++) {
        mvwprintw(algo_menu, i+1, 1, "%s", choices[i]);
        
    }
    //mvwprintw(algo_menu, 1, 1, "%s", "PRINT"); //this is the proper way to print inside a window 1,1 is the line/col respectively
    //wprintw(algo_menu, "PRINT THIS"); // this just prints at 0,1 of window
    wrefresh(algo_menu);
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
    m_height = row / 2; //These are the dimensions of the algo menu
    m_width = col / 2;

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
                algo_selection_menu(m_height, m_width, num_algo_choices, algo_choices);
                break;
        }
    };
    endwin();
};
