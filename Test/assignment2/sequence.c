#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    
    int row=0;
    char store[100][256]; 
    while(fgets(store[row], sizeof(store[row]),stdin) != NULL){
        int column = 0;
        while (store[row][column] != '\n'){
            column++;
        }
        store[row][column] = 0;
        row++;

    }

    int the_fock;
    for(int i=0;i<row;i++){

        // printf("%s\n",store[i]);

        the_fock=fork();

        if(the_fock < 0 ){
            // printf("you got the focking error");

        }else if (the_fock == 0 ){
            
            int count=0;
            char *ptr = strtok(store[i]," ");
            char *focking_command[100];

            while(ptr != NULL){
                focking_command[count]=ptr;
                // printf("%s ",focking_command[count]);
                count++;
                ptr = strtok(NULL," ");

                
            }

            //printf("%c\n", focking_command[0][0]);
            
            // printf("%s *",focking_command[1]);
            
            
            
            // char focking_command[count];
            // for(int split_num=0;split_num<count;split_num++){
            //     focking_command[split_num]=ptr[split_num];
            // }
            focking_command[count]=NULL;



            // printf("%s  \n",focking_command[0]);
            execvp(focking_command[0],focking_command);
            // char* fock2[2] = {"ls", NULL};
            // execvp(fock2[0], fock2);
        }else {
            //the focking parent only know wait;
            // printf("mother");
            wait(NULL);}
        


    }




}