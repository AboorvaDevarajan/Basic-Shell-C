#include<stdio.h>
#include<stdlib.h>
/*
*
*    Unix shell implementation using C.
*    It consitis of basic functionalities of unix prompt such as
*    
*    Execute commands like
*     1. ls
*     2. cd
*     3. pid (process id)
*     4. ppid (parent process id)
*     5. history  
*     6. pipe (|)
*     7. quit
*
*/


#include<string.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char **argv) {
     
     
     char shellStr[100],shell[100];
     char *parameter;
     char *params[100];
     if(argc == 1){
          strcpy(shellStr,"abu >>");
     }
     else {
          if (strcmp(argv[1], "-p") == 0)
               strcpy(shellStr, argv[2]);
          else
               strcpy(shellStr, "abu >> ");
     }
     
     int quit = 0;
     
     
     
     while( !quit ) {
          
          fprintf(stdout,"%s",shellStr);
          fgets(shell,1000,stdin);
          
          int i=0;

          parameter = strtok(shell, "\n");
          while (parameter != NULL) {
               params[i] = parameter;
               i++;
               parameter = strtok(NULL, " ");
          }
          
          // 1.     New Line ; do nothing
          
          if (strcmp(params[0], "\n") == 0)
          {
               
          }
          
          // 2. exit the prompt
          else if (strcmp(params[0], "exit") == 0){
               quit = 1;
          }
          
          // 3. pid of the shell
          else if (strcmp(params[0], "pid") == 0){
               fprintf(stdout,"current process id (pid): %d\n", (int)getpid());
          }
         
          // 4. ppid of the shell
          else if (strcmp(params[0], "ppid") == 0){
               fprintf(stdout,"current parent process id (ppid): %d\n", (int)getppid());
          }
          
          // 5. print the current working directory (pwd)
          else if (strcmp(params[0], "pwd") == 0){
               char pwd[1024];
               if (getcwd(pwd, sizeof(pwd)) != NULL)
                    fprintf(stdout, "Current working directory: %s\n", pwd);
               else
                    perror("getcwd() error\n");
          }
    
     }     
     
     return 0;
}
