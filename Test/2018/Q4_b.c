#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 100
#define COPYMODE 0644
main(int argC, char* argv[])
{
    int srcFd;
    int dstFd;
    int charCnt;
    char buf[BUFFERSIZE];
    /* Check args */
    if( argC!=3 ){
        fprintf( stderr, "usage: %s source destination\n", argv[0]);
        exit(1);
    }
    /* Open the files */
    srcFd= open(argv[1],O_RDONLY);
    if( srcFd==-1 ){
        fprintf(stderr,"Cannot open %s \n", argv[1]);
    }
    dstFd= creat(argv[2],COPYMODE);
    if( dstFd==-1 ){
        fprintf( stderr,"Cannot create %s \n", argv[2]);
    }
/* put your code to copy from srcFd to dstFd here */

    FILE *src_file;
    FILE *dst_file;
    src_file = fdopen(srcFd, "r");
    dst_file = fdopen(dstFd, "w");

    fread(buf, BUFFERSIZE, 1, src_file);

    printf("%s", buf);

    fwrite(buf, strlen(buf) + 1, 1, dst_file);


    fclose(src_file);
    fclose(dst_file);


/* code to close files would go here. */

}