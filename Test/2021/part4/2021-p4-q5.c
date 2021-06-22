// Author : Akide Liu 
// Date : 22/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdlib.h>
#include <stdio.h>

void confuse(int * a, int * b)
{
    int * c = b;
    *a = *b + *c;
    a = c;
    *a = *b + *c;
}

int main()
{
    char a[4] = "cat\0";
    char b[4] = "bar\0";
    char * c;
    c = b;
    c[0] = 'p';
    c = b + 1;
    int * x;
    int * y;
    int * z;

    printf("%s%s\n", a, b);
    printf("%s%s\n", c, a);

    int i = 5;
    int j = 1;

    x = &i;
    y = &j;

    printf("%d, %d\n", *x, *y);
    confuse(x, y);
    printf("%d, %d\n", *x, *y);
}