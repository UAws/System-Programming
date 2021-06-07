// Author : Akide Liu 
// Date : 28/5/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdlib.h>

int main(int argc, char **argv){
    int **array = (int**)malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; ++i) {
        array[i] = (int *) malloc(sizeof(int) * 10);
    }

    for (int i = 0; i < 10; ++i) {
        free(array[i]);
    }
    free(array);
}