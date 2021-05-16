// Author : Akide Liu 
// Date : 16/5/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <glob.h>
#include <stdio.h>

int foo(char const * epath, int eerrno) { return 0; }

int main()
{
    glob_t globbuf = {0};

    glob("*.c", GLOB_DOOFFS, foo, &globbuf);

    for (size_t i = 0; i != globbuf.gl_pathc; ++i)
    {
        printf("Found: %s\n", globbuf.gl_pathv[i]);
    }

    globfree(&globbuf);
}