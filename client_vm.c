/*
vm_client.c : test program for forked vm block


*/
#include "csapp.h"

static unsigned int port = 0;
static unsigned int block_id= 0;
static char host[] = "localhost";
static char block_header[] = "block_id";


int main (int argc , char *argv[])
{
	int clientfd;
	rio_t rio;
	char buf[MAXLINE];
	int nobytes;
	
	if(argc != 2){
		printf("error in format : %s <port> <block_id>\n",argv[0]);
		exit(0);
	}

	// get server port and id
	port = atoi(argv[0]);
	block_id = atoi(argv[1]);
	printf("port=%d\nid=%d\n",port,block_id);
	// communicate with server
	clientfd = Open_clientfd(host,port);
	printf("Clientfd=%d for id:%d\n",clientfd,block_id);
	Rio_readinitb(&rio,clientfd);

	printf("Connection Established : block_id : %d\n",block_id);
	
	//send hello
	sprintf(buf,"%s : %d says hello\n",block_header,block_id);
	Rio_writen(clientfd,buf,strlen(buf) + 1);
	
	// receive reply
	nobytes = Rio_readlineb(&rio,buf,MAXLINE);		
	printf("Received from server :%s\n",buf); 
	Close(clientfd);
	exit(0);

}
