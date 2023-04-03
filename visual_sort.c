#include <ncurses.h>
#include <string.h>

/* Bubble Sort */

/*
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
*/

void strswap(char *x, char *y) {
    char tmp[30];
    strcpy(tmp, x);
    strcpy(x, y);
    strcpy(y, tmp);
}


// n is the size of the array
/*
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
*/

void bub(char **pntr, int array_size, int bub_iterator) {
    int z;
    for (z=0; z < array_size - bub_iterator - 1; z++) {
       if(strlen(pntr[z]) > strlen(pntr[z+1])) {
            strswap(pntr[z], pntr[z+1]);
       }
    }
}

void view_bubble(WINDOW *win){
    int i, x, z;
    int bub_array[] = { 12, 8, 9, 11, 6, 23, 15, 2, 7, 21};
    int bub_array_size = sizeof(bub_array) / sizeof(bub_array[0]);
    int bub_iterator = bub_array_size - 1;
    
    // have to figure this out
    char visual[10][30] = {"x","x","x","x","x","x","x","x","x","x"};
    //char *visual[30] = {"x","x","x","x","x","x","x","x","x","x"};
    
    //make visual match bub_array with x's 
    for(z = 0; z < bub_array_size; z++){ 
        for(x = bub_array[z] - 1; x > 0; x--){
            strcat(visual[z], "x");
        }
    }

    mvwprintw(win, i+1, 1, "%s", visual[i]);
    /* while(bub_iterator > 0){ */
    /*     for(i = 0; i < bub_array_size; i++) { */
    /*         mvwprintw(win, i+1, 1, "%s", visual[i]); */
    /*     } */
    /*     bub(visual, bub_array_size, bub_iterator); */
    /*     bub_iterator--; */
    /* } */
    //wrefresh(win);
}

/* Merge Sort */ 
