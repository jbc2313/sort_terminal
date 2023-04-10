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
    int b, c, d, i, j, k, l, m, x, z;
    int bub_array[] = { 12, 8, 9, 11, 6, 23, 15, 2, 7, 21};
    int bub_array_size = sizeof(bub_array) / sizeof(bub_array[0]);
    int bub_iterator = 0;
    // have to figure this out
    char visual[10][30] = {"x","x","x","x","x","x","x","x","x","x"};
    //char *visual[30] = {"x","x","x","x","x","x","x","x","x","x"};
    
    // two dimensional array used to highlight lines moving
    int original_lookup[10][2];
    int lookup[10][2] = { 
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
        0,0,
    };
    
    //make visual match bub_array with x's 
    for(z = 0; z < bub_array_size; z++){  
         for(x = bub_array[z] - 1; x > 0; x--){ 
             strcat(visual[z], "x");
         } 
     };
    // copy visual index size to lookup index lhand 
    // j < 10 because array is 10. j <= 10 is actually 11 
    for(j = 0; j < 10; j++) {
       lookup[j][0] = (int)strlen(visual[j]); 
       original_lookup[j][0] = (int)strlen(visual[j]);
       lookup[j][1] = j;
       original_lookup[j][1] = j;
    };



    // print inital lookup table on right of screen
    for(j = 0; j < 10; j++) {
        int tmp = lookup[j][0];
        int tmp2 = lookup[j][1];
        mvwprintw(win, j+1, 30, "lookup 0: %d", tmp);
        mvwprintw(win, j+1, 45, "%d", tmp2);
    }

    // print visual array before sort starts
    for(i = 0; i < bub_array_size; i++) {
        mvwprintw(win, i+1, 1, "%d: %s", strlen(visual[i]), visual[i]);
    };
    wrefresh(win);
    sleep(1);
    /*
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
        // copy visual to lookup;
                    
        for(l = 0; l < 10; l++) {
           lookup[l][0] = (int)strlen(visual[l]); 
           lookup[l][1] = l;
        };


        // find the index of the visual array that has moved
        int moved_value;
        int to_index;
        int from_index;
        for(k = 0; k < 10; k++) {
            if (original_lookup[k][0] !=  lookup[k][0]){ 
                // check the previous index to see if it changed. if it didnt then the current index is was the number moved 
                if(original_lookup[k-1][0] == lookup[k+1][0]) {
                    from_index = k;
                    // assign moved value here
                    moved_value = original_lookup[k][0];
                }
                // check to see if index is zero
                if (k == 0) {
                    from_index = k;
                    // assign moved value here 
                    moved_value = original_lookup[k][0];
                }
                //check the next index to see if it changed, if it didnt then the index before is where the number moved to. 
                if(original_lookup[k+1][0] == lookup[k+1][0]) {
                     to_index = k;      
                } else if (k == 9) {
                    to_index = k;
                }
            }
            int tmp_print1 = lookup[k][0];
            int tmp_print2 = lookup[k][1];
            mvwprintw(win, k+1, 50, "updated lookup: %d ", tmp_print1); 
            mvwprintw(win, k+1, 70, "%d", tmp_print2); 
        }

        // copy lookup to original lookup
        for(m = 0; m < 10; m++) {
           original_lookup[m][0] = lookup[m][0];
           original_lookup[m][1] = m;
        };

        // remove previous visual array and print visual array to screen
        for(d = 0; d < bub_array_size; d++) {
            mvwprintw(win, d+1, 1, "                                      ");
        }
        // print visual array to screen 
        init_pair(1, COLOR_RED, COLOR_BLACK);
        for(i = 0; i < bub_array_size; i++) {    
            // add color to the index that was moved last.
            wattroff(win,COLOR_PAIR(1));
            if(i == to_index) {
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win, i+1, 1, "%2d: %s  ", strlen(visual[i]), visual[i]);
                //wattroff(win,COLOR_PAIR(1));
                //mvwchgat(win, i+1, 1, 60, A_UNDERLINE, 1, NULL);
            }
            mvwprintw(win, i+1, 1, "%2d: %s", strlen(visual[i]), visual[i]);
            

            /*
             NOT SURE WHY THIS WONT WORK?? TYPE WRONG MAYBE??
            if(strlen(visual[i]) > 9) {
                mvwprintw(win, i+1, 1, "%d: poop %s", strlen(visual[i]), visual[i]);
            }
                mvwprintw(win, i+1, 1, "%d:  %s", strlen(visual[i]), visual[i]);
            */

        }   
        
        //print out main forloop iteration index
        mvwprintw(win, 20, 1, "Index of B: %d", b);

        wrefresh(win);
        //usleep(99999);
        sleep(1);
    }
}

/* Merge Sort */ 
