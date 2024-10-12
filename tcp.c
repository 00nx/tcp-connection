#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

	int server_fd, new_socket;
	struct sockaddr_in address; // for storing socket address information
	int opt = 1; // for socket options
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

	// creating a socket file descriptor /  a socket identifier 

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
	perror("socket creation error :  ");
        exit(EXIT_FAILURE);
	}
	 
	// setting socket options 
	
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
	
		perror("setsockopt error : ");
	        exit(EXIT_FAILURE);
	}


	// setting address family 

	address.sin_family = AF_INET; // setting the family address to INET ( IPv4 ) 


	address.sin_addr.s_addr = INADDR_ANY; // accepting connection on any available interface  
	
	address.sin_port = htons(PORT); // setting the port number in network byte
	
	if( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
	perror("binding error : ");
        exit(EXIT_FAILURE);
	}

	// LISTENING TO THE SERVER 
	
	if(listen(server_fd, 3) < 0) {
	perror("Listening failed :  ");
        exit(EXIT_FAILURE);
	
	} else {
	
	printf("server listening on port %d\n", PORT );
	}
	
	// accepting incoming connections 
	
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
	
	perror("failed to accept connection :  ");
        exit(EXIT_FAILURE);
	} else {
	
	printf("Connection accepted\n");
	}

	// fetch clients data and output it 
	
	// declare a signed size type for the number of bytes to read
	
	ssize_t valread;

	while((valread = read(new_socket, buffer,  BUFFER_SIZE )) > 0 ) { 

		printf( "Client %s", buffer );
		memset(buffer, 0, sizeof(buffer));
	}

	// close the socket

        close(new_socket);
	
	close(server_fd);
	return 0;
       

}
