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

	int sockfd, ret;//creation du socket
	 struct sockaddr_in serverAddr;//serveur reçoit sur cette adresse 

	int newSocket;//acceptation du connection
	struct sockaddr_in newAddr;//le serveur envoie au client sur cette adresse

	socklen_t addr_size;
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in binding.\n");
		exit(1);
	}
	printf("Bind to port %d\n", 8080);

	if(listen(sockfd, 10) == 0){
		printf("Listening....\n");
	}else{
		printf("Error in binding.\n");
	}

       while(1){
	// processus parent en attente d'accepter une nouvelle connexion 
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
// le processus enfant est créé pour servir chaque nouveau client
		if((childpid = fork()) == 0){//duplique toutes les données du père au fils créé
			close(sockfd);//Le fils ferme la socket d'écoute

			
int arrsize, i;
recv(newSocket, &arrsize, sizeof(int), 0);
printf("Received array size from client is: %d\n", arrsize);
int arr[arrsize];
recv(newSocket,arr, sizeof(arr), 0);
int sum=0;
for(i=0; i<arrsize; i++)
{
sum=sum+arr[i];
}
send(newSocket,&sum,sizeof(int),0);
printf("sum of array is %d sent to client\n", sum);
		
		
			
		}

	}
	

	close(newSocket);//Le père ferme la socket de service qui vient d'être créée

	return 0;
}