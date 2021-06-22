// Author : Akide Liu 
// Date : 22/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <string.h>
void mystery(int *a, int *b, int *c) {
    int *t = a;
    a = b;
    b = t;
    *c = *a - *b;
}
int main() {
    char foo[5] = "Hey";
    char bar[3] = "Yo";
    int u = strlen(foo);
    int x = 0;
    int *y = &x;
    int *z;
    int p = 12;
    strcpy(foo,bar);
    printf("%s %s\n", foo,bar);
    x = 1;
    z = &p;
    *y = *y + u;
    printf("XP: %d %d\n", x, p);
    printf("*: %d %d\n", *y, *z);
    mystery(z, y, &p);
    printf("XP: %d %d\n", x, p);
    printf("*: %d %d\n", *y, *z);
}