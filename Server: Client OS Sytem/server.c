// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
//#include <sys/socket.h> 
//#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <netinet/in.h> 

#define PORT	 8084
#define MAXLINE 1024 

// Driver code 
int main() { 
  
	 char*server_fifo_name="./serverfifo";
   mkfifo(server_fifo_name, 0666); 
   char buffer[MAXLINE]; 
	
   while(1)
   {

  int fd1 = open(server_fifo_name,O_RDONLY);
  char message[100]={'\0'};
  read(fd1, message, 100);
  
  char * client_id = strtok(message, ",");

  char*fifo_name = strtok(NULL,",");

  int fd2 = open(fifo_name,O_WRONLY);
  write(fd2, "received", 8);

   char commands[10000]={'\0'};
  
   read(fd1,commands,10000);

   if(strcmp(commands,"QUIT")==0)
   {
     close(fd2);
   }

   char copy[10000]={'\0'};
   strcpy(copy,commands);

  char * system_call = strtok(commands, ",");
  char*no_of_parameters = strtok(NULL,",");
  
  write(1,"Client ID: ",11);
  write(1,client_id,strlen(client_id));
  write(1, "\nSystem call requested: ", 24);
  write(1,system_call, strlen(system_call));
  write(1, " with ", 6);
  write(1,no_of_parameters, strlen(no_of_parameters));
  write(1," parameters which are: \n", 24);

  int i=0;
  while(1)
  {
    no_of_parameters = strtok(NULL,",");

    if(no_of_parameters==NULL)
    {
      break;
    }

    char indexes[100]={'\0'};
    write(1,"param ",6);
    sprintf(indexes,"%d",i+1);
    write(1,indexes,strlen(indexes));
    write(1,":",1);
    write(1,no_of_parameters,strlen(no_of_parameters));
    write(1,"\n",1);
    i++;
  }

  write(fd2,copy, strlen(copy));
  
 	
  }

 
	return 0; 
} 
