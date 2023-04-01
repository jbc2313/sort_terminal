#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

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

void print_userchoice_center(WINDOW *win, int user_choice, int height, int width) {
    mvwprintw(win, height/2, (width - 15)/2, "The user chose %d", user_choice); 
    wrefresh(win);
}

char *algo_choices[] = {
    "bubble",
    "merge",
    "selection",
    "insertion",
    "quick",
    "QUIT",
};
int num_algo_choices = sizeof(algo_choices) / sizeof(algo_choices[0]);

void display_bubble() {
  WINDOW *bubble_win = create_window(100, 100, 0, 0) ;
  //print_center(bubble_win, "Lets bubble sort", 5, 1);
}

void algo_selection_menu(int height, int width, int *algo_user_choice , int selection_size, char **choices) {
    WINDOW *algo_menu;
    algo_menu = create_window(selection_size+10, 50, height-10, width-20);
    int user_selection, i;
    int highlight = 1;
    int exit = 0;
    char teststring[] = "Print this out!";
    keypad(algo_menu, TRUE);
    for(i = 0; i < selection_size; i++) {
        mvwprintw(algo_menu, i+1, 2, "%s", choices[i]); 
    }
    //mvwprintw(algo_menu, 1, 1, "%s", "PRINT"); //this is the proper way to print inside a window 1,1 is the line/col respectively
    //wprintw(algo_menu, "PRINT THIS"); // this just prints at 0,1 of window
    wrefresh(algo_menu);
    // now need to deal with menu selection with a loop
    
    mvwprintw(algo_menu, highlight, 1, ">");
    while((user_selection=wgetch(algo_menu)) != 'q') {
        mvwprintw(algo_menu, highlight, 1, " ");
        mvwprintw(algo_menu, 12, 1, "                               ");
        switch (user_selection) {
            case KEY_UP:
                highlight--;
                if(highlight==0) {
                    highlight = 1;
                }
                mvwprintw(algo_menu, 12, 1, "highlight = %d", highlight);
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight > selection_size) {
                    highlight = 6;
                }
                mvwprintw(algo_menu, 12, 1, "highlight = %d", highlight);
                break;
            case 10: //This is the ENTER key
                if(highlight == 6) {
                    // this is the exit path
                    //user_selection = 'q';
                    //mvwprintw(algo_menu, 12, 2, "Press 'q' to exit.");
                    *algo_user_choice = -1;
                    exit = 1;
                } else {
                    // go into the selected item
                    //mvwprintw(algo_menu, 12, 2, "You selected %s", choices[highlight-1]);
                    //assign the algo user selection int to the index number of the algo they want
                    if (highlight == 1) {
                        *algo_user_choice = 0;
                    }
                    if (highlight == 2) {
                        *algo_user_choice = 1;
                    }
                    if (highlight == 3) {
                        *algo_user_choice = 2;
                    } 
                    if (highlight == 4) {
                        *algo_user_choice = 3;
                    }
                    if (highlight == 5) {
                        *algo_user_choice = 4;
                    }

                
                    exit = 2;
                    wrefresh(algo_menu);
                    break;
                };

                
        }
        mvwprintw(algo_menu, highlight, 1, ">");
        wrefresh(algo_menu);
        if(exit == 1) {
            //user chose quit
            break;
        }
        if(exit == 2) {
            //user chose an algo
            break;
        }
    }
    delwin(algo_menu);
};

void screen() {
    WINDOW *term_window;
    int start_x, start_y, width, height, row, col, m_width, m_height;
    int ch;
    int algo_user_choice;
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
                algo_selection_menu(m_height, m_width, &algo_user_choice, num_algo_choices, algo_choices);
                delwin(term_window);
                term_window = create_window(row, col, start_y, start_x);
                if (algo_user_choice == -1) {
                    //assert(strcmp(algo_user_choice,"quit") == 0); 
                    print_center(term_window, "you quit the menu", row, col);
                    wrefresh(term_window);
                } else {
                    // need to print the user selected algo
                    // this will print the user selected algo to double check
                    print_userchoice_center(term_window, algo_user_choice, row, col); 
                    wrefresh(term_window);
                }
                break;
        }
    };
    endwin();
};





