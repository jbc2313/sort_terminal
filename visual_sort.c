#include <ncurses.h>
#include <string.h>
#include <unistd.h>

/* Bubble Sort */



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
            //wattroff(win,COLOR_PAIR(1));
            if(i == to_index) {
                //wattron(win, COLOR_PAIR(1));
                mvwprintw(win, i+1, 1, "%2d: %s  ", strlen(visual[i]), visual[i]);
                //mvwchgat(win, i+1, 1, 60, A_UNDERLINE, 1, NULL);
                //Everything randomly turns red bug... ??
                // This is happening because everything printed after wattron is printed red. DUH
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
/* Original merge and sort code */

void sort(int *pntr, int low, int mid, int high) {
    int x, y, z;
    int nLow = mid - low + 1;
    int nHigh = high - mid;
    int lowArr[nLow], highArr[nHigh];

    // copy to both temp arrays
    for (x = 0; x < nLow; x++) {
        lowArr[x] = pntr[low + x];
    };
    for (y = 0; y < nHigh; y++) {
        highArr[y] = pntr[mid + 1 + y];
    };
    
    // merge temp arrays back together pntr[low...high]
    
    // index of lowArr
    x = 0;
    // index of highArr
    y = 0;
    // index of merged arrays
    z = low;

    while (x < nLow && y < nHigh) {
        if (lowArr[x] <= highArr[y]) {
            pntr[z] = lowArr[x];
            x++;
        } else {
            pntr[z] = highArr[y];
            y++;
        };
        z++;
    };

    while (x < nLow) {
        pntr[z] = lowArr[x];
        x++;
        z++;
    };

    while (y < nHigh) {
        pntr[z] = highArr[y];
        y++;
        z++;
    };

};


void merge (int *pntr, int low, int high) {
    if ( low < high ) {
        // (low + high)/2 will work too, below prevents overflow 
        int mid = low + (high - low) / 2;
        merge(pntr, low, mid);
        merge(pntr, mid + 1, high);
        sort(pntr, low, mid, high);

    }
};

void view_merge(WINDOW *win){
    int merge_array[] = {8, 15, 3, 7, 2, 17, 12, 10, 5, 1}; 
    int merge_array_size = sizeof(merge_array) / sizeof(merge_array[0]);
    char visual[10][30] = {"x","x","x","x","x","x","x","x","x","x"};

    
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
    
    int i, x;
    for(i = 0; i < merge_array_size; i++){  
         for(x = merge_array[i] - 1; x > 0; x--){ 
             strcat(visual[i], "x");
         } 
     };
     

    // copy visual index size to lookup index lhand 
    // j < 10 because array is 10. j <= 10 is actually 11 
    
    int j;
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
        mvwprintw(win, j+1, 30, "lookup init: %d", tmp);
        mvwprintw(win, j+1, 47, "%d", tmp2);
    }
    

    // print visual array before sort starts
    
    for(i = 0; i < merge_array_size; i++) {
        mvwprintw(win, i+1, 1, "%d: %s", strlen(visual[i]), visual[i]);
    };
    wrefresh(win);
    sleep(1);
    
    
    // start merge loop
    for(i = 0; i < 10; i++) {
        mvwprintw(win, i+1, 55, "%d is the loop index", i);
        wrefresh(win);
        sleep(1);
    }


   // mvwprintw(win, 1, 1, "Merge Sort Visualized");
   // mvwprintw(win, 2, 1, "THE POWER OF NCURSES");

}


/* END OF MERGE */

