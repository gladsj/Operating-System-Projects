// Client side implementation of UDP client-server model 

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
int main(int argc, char**argv)
{
  char*server_fifo_name="./serverfifo";
   mkfifo(server_fifo_name, 0666); 
  char fifo_name[100]={'\0'};
  sprintf(fifo_name, "./Client%dfifo", atoi(argv[1]));
  mkfifo(fifo_name, 0666); 
	char buffer[MAXLINE]; 

	char info[200]={'\0'};
  sprintf(info,"%d,%s",atoi(argv[1]),fifo_name);
  int fd1 = open(server_fifo_name,O_WRONLY);
  char message[100]={'\0'};
  write(fd1, info, 100);

  int fd2 = open(fifo_name,O_RDONLY);
  char message1[100]={'\0'};
  read(fd2, message1, 100);

  write(1,message1, strlen(message1));

  while(1)
    {
      printf("Which system call do you want to send to the server?\n 1. READ\n 2. WRITE\n 3. OPEN\n 4. QUIT\n");

      int option=0;
      printf("Enter your option: ");
      scanf("%d", &option);

      if(option==4)
      {
        write(fd1, "QUIT", 4);
        break;
        
      }

      int no_of_parameters=0;

       printf("How many parameters do you want to send with the request?: ");

      scanf("%d", &no_of_parameters);

      char**parameters=(char**)malloc(sizeof(char*)*no_of_parameters);

      for(int a=0; a<no_of_parameters; a++)
        {
          parameters[a] = (char*)malloc(sizeof(char)*100);
        }

      for(int a=0; a<no_of_parameters; a++)
        {
          printf("Enter parameter %d: ", a+1);
          scanf("%s",parameters[a]);
        }

      char commands[10000]={'\0'};

      sprintf(commands, "%d,%d", option, no_of_parameters);

      for(int a=0;a<no_of_parameters;a++)
        {
          
          strcat(commands,",");
          strcat(commands,parameters[a]);
        }

        char acknowledgement[10000]={'\0'};
        write(fd1, commands, strlen(commands));
        read(fd2, acknowledgement, 10000);

        write(1, acknowledgement, strlen(acknowledgement));

    }
  
	// int n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	// buffer[n] = '\0'; 
	// write(1,buffer,strlen(buffer)); 
	// int port = ntohs(servaddr.sin_port);
	// printf("\nwith Port  %d\n",port);
	return 0; 
} 

