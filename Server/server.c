#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#define MAX_EVENTS 5
#define READ_SIZE 10

void dostuff(int sock)
{
        int i;
        char buffer[256];
        bzero(buffer, 256);
        i = read(sock, buffer, 255);
//	for(int i = 0; i < 5; i++){
//            for(int j = 0; j <= 6; j++)
//                i = write(sock,"_",1);
//            i = write(sock,"     ",5);
//        }
	if(buffer[0] != '\0')
        	printf("Here is a message: %s",buffer);
        if(i < 0)
                perror("ERROR writing to socket");
}

void setnonblocking(int sock){
        int non;
        non = fcntl(sock,F_GETFL);
        non = non | O_NONBLOCK;

        if(fcntl(sock,F_SETFL, non) < 0){
                perror("fctnl");
                exit(0);
        }
}

int main(int argc, char *argv[]){

	struct epoll_event ev, events[MAX_EVENTS];
	int listen_sock, conn_sock, nfds, epollfd;

	int portno, client, pid;
        struct sockaddr_in serv_addr, cli_addr;

        int running = 1, event_count, i, n;
        size_t bytes_read;
        char read_buffer[READ_SIZE + 1];

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(argv[1]);

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(portno);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(listen_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
                perror("ERROR on accept");

        listen(listen_sock, 5);

	epollfd = epoll_create1(0);
	if(epollfd == -1){
		perror("epoll_create1");
		exit(1);
	}
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;

	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1){
		perror("epol_ctl: listen_sock");
		exit(1);
	}

	while(1){
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if(nfds == -1){
			perror("epoll_wait");
			exit(1);
		}
		for( n = 0; n < nfds; n++){
			if(events[n].data.fd == listen_sock){
				conn_sock = accept(listen_sock, (struct sockaddr *) &cli_addr, &client);
				if(conn_sock == -1){
					perror("accept");
					exit(1);
				}
				setnonblocking(conn_sock);
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if(epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1){
					perror("epoll_ctl: conn_sock");
					exit(1);
				}
			}
			else {
				dostuff(events[n].data.fd);
			}
		}
	}
}
