#include <ncurses.h>
#include <string.h>

/* Bubble Sort */
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// n is the size of the array
void bub(int *pntr, int n) {
    int i, z;
    for (i = 0; i < n - 1; i++) {
        for (z = 0; z < n - i - 1; z++) {
            if (pntr[z] > pntr[z + 1]) {
               swap(&pntr[z], &pntr[z + 1]); 
            };
        };
    };
}

void view_bubble(WINDOW *win){
    int i, x, z;
    int bub_array[] = { 12, 8, 9, 11, 6, 23, 15, 2, 7, 21};
    int bub_array_size = sizeof(bub_array) / sizeof(bub_array[0]);
    char visual[10][25] = {"x","x","x","x","x","x","x","x","x","x"};
    //make visual match bub_array with x's 
    for(z = 0; z < bub_array_size; z++){ 
        for(x = bub_array[z] - 1; x > 0; x--){
            strcat(visual[z], "x");
        }
    }
    for(i = 0; i < bub_array_size; i++) {
        mvwprintw(win, i+1, 1, "%s", visual[i]);
    }
    //wrefresh(win);
}

/* Merge Sort */ 
