// Author : Akide Liu 
// Date : 21/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    if (argc != 2) {
        printf("error");
    }

    size_t length = strlen(argv[1]);

    char *new_string = (char *) malloc(sizeof(char) * (length * 2 + 1));

    size_t index = 0;
    for (int i = 0; i < length * 2; ++i) {
        new_string[i] = argv[1][index];
        index++;

        if (index == length) {
            index = 0;
        }

    }

    printf("%s", new_string);

    free(new_string);



}