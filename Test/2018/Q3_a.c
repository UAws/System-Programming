// Author : Akide Liu 
// Date : 21/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdlib.h>


int main(int argc, char **argv){
    int *x;
    int y=4;
    x = (int*) malloc(sizeof(int));
/* ... some code using x here ...*/
    x=&y;
}
