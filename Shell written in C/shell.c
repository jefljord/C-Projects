#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define bSize 1000

void driveLoop();
char *userInput(void);
void removeExit(char *original, char *subString); // removes string with substring "exit"
void batchMode(char *c);

int main(int argc, char **argv){

  if (argc == 1)
    driveLoop(); // calls the loop function that accepts input and executes commands.

  else if (argc == 2)
    batchMode(&argv[1][0]);
		    
  
  return 0;

}

void driveLoop(void){
  char *comTokens[100];
  char *tempTokens;
  char *command;
  char *cd;
  char *cdDir;
  char* cdTemp;
  char cdBuf[bSize];
    
  for (;;){

    printf("> ");
    command = userInput(); // reads input

    if (!*command) // allows for empty string error
      break;

    char *exitPtr = strstr(command, "quit"); // returns a value to a pointer if substring is found
    removeExit(command, "quit"); 
    puts(command); // updates the array after the function filter
    
    int i = 0;
    tempTokens = strtok(command, " \t\n"); // tokens are how the computer recognizes shell commands

    while (tempTokens && i < 99){ // geeksforgeeks.com
      comTokens[i++] = tempTokens;
      tempTokens = strtok(NULL, "\t\n");
    }

    if (strcmp(comTokens[0], "quit") == 0) // exit if input is "exit" only
      exit(0); 


    if(strcmp(comTokens[0], "cd") == 0){ // built in change directory command
      cd = getcwd(cdBuf, sizeof(cdBuf));
      cdDir = strcat(cd, "/");
      cdTemp = strcat(cdDir, comTokens[1]); // cplusplus.com reference
      chdir(cdTemp);
      continue;
    }
    
    comTokens[i] = NULL;

    pid_t cFork = fork(); // creates duplicate child process of parent

    if (cFork == (pid_t) - 1){ // error check
      perror("fork");
    }

    else if (cFork == 0) { // error codes found on cplusplus.com
      execvp(comTokens[0], comTokens);
      perror("exec");      
    }
    
    else { // children are returned. parent executes
      int status;
      waitpid(cFork, &status, 0);
      if (exitPtr != NULL){ // if substring exit was found, exit the program
	exit(0);
      }
    }

  }
  
}

char *userInput(void){  // referenced Linux man page - getline(3) (linux.die.net)
  char *input = NULL;
  size_t size = 0;
  getline(&input, &size, stdin); // updates the size as it goes along
  return input;
}

void removeExit(char *original, char *subString){ // removes exit from string
  char *ex;
  int len = strlen(subString); 
  while ((ex = strstr(original, subString))){ // Referenced from a Stack Overflow page.
    *ex = '\0';
    strcat(original, ex+len);
  }
}

void batchMode(char *c){

  char *tok[100];
    
  FILE *fp = fopen(c, "r");

  char buffer[bSize];

  while(fgets(buffer, sizeof(buffer), fp)){
    
     int i = 0;

     char *toks = strtok(buffer, "\t\n");

     while (toks && i < 99){
       tok[i] = malloc (strlen (toks) + 1);
       strcpy(tok[i++], toks);
       toks = strtok(NULL, " \t\n");
     }

     tok[i] = NULL;
     pid_t bFork = fork();

     if (bFork == (pid_t) - 1)
       perror("fork");

     else if (bFork == 0){
       execvp(tok[0], tok);
       perror("exec");
     }

     else {
       int status;
       waitpid(bFork, &status, 0);
     }
    
  }
  
}

