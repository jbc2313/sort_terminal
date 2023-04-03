#include <ncurses.h>
#include <string.h>
#include <unistd.h>

/* Bubble Sort */

//original bubble sort algo
/*
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
*/

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
//end of original bubble sort code
*/

/*
// my attempt at figuring out bubble sort with arrays of strings
// could not get it to work due to pointers etc etc
void bub(char *pntr, int array_size, int bub_iterator, WINDOW *win) {
    int z;
    for (z=0; z < array_size - bub_iterator - 1; z++) {
       if(strlen(&pntr[z]) > strlen(&pntr[z+1])) {
            //strswap(pntr[z], pntr[z+1], pntr);
            char tmp[29];
            strcpy(tmp, &pntr[z]);
            //strcpy(&pntr[z], &pntr[z+1]);
            //strcpy(&pntr[z+1], tmp);
            mvwprintw(win, 18, 1, "__tmp of swap: %d %s", strlen(tmp), tmp); 
            mvwprintw(win, 19, 1, "Lhand of swap: %d %s", strlen(&pntr[z]), &pntr[z]);
            mvwprintw(win, 20, 1, "Rhand of swap: %d %s", strlen(&pntr[z+1]), &pntr[z+1]);
            mvwprintw(win, 21+bub_iterator, 1, "num of iteration: %d", bub_iterator);
       }
    }
}
*/

void view_bubble(WINDOW *win){
    int b, c, d, i, j, x, z;
    int bub_array[] = { 12, 8, 9, 11, 6, 23, 15, 2, 7, 21};
    int bub_array_size = sizeof(bub_array) / sizeof(bub_array[0]);
    int bub_iterator = 0;
    // have to figure this out
    char visual[10][30] = {"x","x","x","x","x","x","x","x","x","x"};
    //char *visual[30] = {"x","x","x","x","x","x","x","x","x","x"};
    
    //make visual match bub_array with x's 
     for(z = 0; z < bub_array_size; z++){  
         for(x = bub_array[z] - 1; x > 0; x--){ 
             strcat(visual[z], "x");
         } 
     } 
    /*  
    //print visual array on screen 
    for(i = 0; i < bub_array_size; i++) {
        mvwprintw(win, i+1, 1, "%s", visual[i]);
    }
    //print strlen of visual array just below visual array
    for(j = 0; j < bub_array_size; j++) {
        mvwprintw(win, j+15, 1, "%d", strlen(visual[j]));
    }
    */     

    // bubble sort the array of strings in this function because of scope and pointers
    for (b = 0; b < bub_array_size - 1; b++) { 
        for (c = 0; c < bub_array_size - b - 1; c++) {
            if (strlen(visual[c]) > strlen(visual[c + 1])) {
                //swap the two
                char tmp[29];
                strcpy(tmp, visual[c]);
                strcpy(visual[c], visual[c+1]);
                strcpy(visual[c+1], tmp);
            };
        };
        for(d = 0; d < bub_array_size; d++) {
            mvwprintw(win, d+1, 1, "                                      ");
        }
        for(i = 0; i < bub_array_size; i++) {
            mvwprintw(win, i+1, 1, "%s", visual[i]);
        }   
        
        //print out main forloop iteration index
        mvwprintw(win, 20, 1, "Index of B: %d", b);

        wrefresh(win);
        sleep(1);
    }
}

/* Merge Sort */ 
