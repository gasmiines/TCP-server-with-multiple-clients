#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");

	while(1){
		int arr[100],i,arrsize;
      printf("Enter the array size: ");
      scanf("%d",&arrsize);
      send(clientSocket,&arrsize,sizeof(int),0);
      printf("Enter %d elements to array\n",arrsize);
      for(i=0;i<arrsize; i++)
       {
            scanf("%d",&arr[i]);
           }
    send(clientSocket, arr,sizeof(arr), 0);
    printf("Array sent to server\n");
    int sum;
    recv(clientSocket, &sum, sizeof(int), 0);
     printf("The sum of array element is: %d\n", sum);

	}

	return 0;
}