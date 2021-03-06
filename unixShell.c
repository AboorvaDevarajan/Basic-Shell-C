#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

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

/*
* variables for storing the command history
*/

typedef struct History{
    char *command;
    struct History *next;
}History;

typedef struct List{
    unsigned int count;
    History *top;
}List;
/*
*    History functions
*/

int isHistoryEmpty(List *list){
    if (list->count == 0){
        return 1;
    }
    return 0;
}


void  addHistory(List *list, char *cmd){
    History *h = (History*) malloc(sizeof(History));
    h->command = (char*) malloc(sizeof(char) * (strlen(cmd) + 1));
    strcpy(h->command, cmd);

    if (isHistoryEmpty(list)){
        h->next = NULL;
        list->top = h;
    }
    else{
        h->next = list->top;
        list->top =  h;
    }
    list->count++;
}

void clearHistory(List *list){
    while (!isHistoryEmpty(list)){
        History *temp = list->top;
        list->count--;
        list->top = list->top->next;
        free(temp);
    }
    free(list);
}

void printHistory(List *list){
    int i = 1;
    List * tempLst;
    tempLst = list;
    printf("Command History\n"); 
    while (!tempLst->top == NULL){ //this line causes a warning on compilation (comparison between pointer and integer)
        History *temp = tempLst->top;
        printf("[%d] %s \n", i, temp->command);
        tempLst->top = tempLst->top->next;
        i++;
    }
}  


int main(int argc, char **argv) {
     
     List *historyList = malloc (sizeof(List));
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

          strtok(shell, "\n");
          parameter = strtok(shell, " ");
          while (parameter != NULL) {
               params[i] = parameter;
               i++;
               parameter = strtok(NULL, " ");
          }
          
          fprintf(stdout,"parameter %s\n\n",params[0]);
          
          // 1.     New Line ; do nothing
          if (strcmp(params[0], "\n") == 0)
          {
               
          }
          
          // 2. exit the prompt
          else if (strcmp(params[0], "exit") == 0){
               quit = 1;
               addHistory(historyList, shell);
          }
          
          // 3. pid of the shell
          else if (strcmp(params[0], "pid") == 0){
               fprintf(stdout,"current process id (pid): %d\n", (int)getpid());
               addHistory(historyList, shell);
          }
         
          // 4. ppid of the shell
          else if (strcmp(params[0], "ppid") == 0){
               fprintf(stdout,"current parent process id (ppid): %d\n", (int)getppid());
               addHistory(historyList, shell);
          }
          
          // 5. print the current working directory (pwd)
          else if (strcmp(params[0], "pwd") == 0){
               char pwd[1024];
               if (getcwd(pwd, sizeof(pwd)) != NULL)
                    fprintf(stdout, "Current working directory: %s\n", pwd);
               else
                    perror("getcwd() error\n");
               addHistory(historyList, shell);
          }
                        
          // 6. changing the current directory (cd)
          else if (strcmp(params[0], "cd") == 0){
               if (params[2] != NULL)
                    printf("Invalid number of arguments\n");
               else if (params[1] == NULL)
                    chdir(getenv("HOME"));
               else {
                    if (chdir(params[1]) != 0) {
                         printf("Couldn't change directory\n");
                    }
               }
               addHistory(historyList, shell);
          }
          
          // 5. history
          else if (strcmp(params[0], "history") == 0){
               addHistory(historyList, shell);
               printHistory(historyList);
          }
          
    
     }     
     
     return 0;
}
