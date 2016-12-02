/*
 * Serversocket.c
 * Simon Lit
 * Project groep 1/A
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "serverSocket.h"

#define BACKLOG 10 //How many pending connections queue will hold

int sockfd, new_fd;
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr;
socklen_t sin_size;
struct sigaction sa;
int yes = 1;
char s[INET6_ADDRSTRLEN];
int returnValue;
char buffer[256];
int n = 0;

static void sigchld_handler(int s)
{
	int saved_errno = errno;
	while(waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
static void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int setupCommunicationServer(const char* node, const char* service, int* socketnumber)
{
    sockfd = 0;
    new_fd = 0;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    returnValue = getaddrinfo(node, service, &hints, &servinfo);//makes struct from given settings
    if(returnValue != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(returnValue));
        return 1;
    }

    //Loop through all the results and bind to the first we can find
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
        {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if( p == NULL)
    {
        fprintf(stderr, "Server failed to bind\n");
        exit(1);
    }
    else
    {
        *socketnumber = sockfd;//Save socket int so it can be used to accept connections
    }
    if(listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }
    sa.sa_handler = sigchld_handler; //Reap all dead zombies
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    printf("Server : waiting for connections ....\n");
    return(0);
}

int acceptinConnectionsOnServer(int sockfd)
{
    printf("Starting listen on socket %d\n", sockfd);
    while(1)
    {
    sin_size = sizeof(their_addr);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if(new_fd == -1)
    {
        perror("accept");
    }
    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
    printf("Server : Got connection from %s\n", s);
    if(!fork())
    {
        close(sockfd);
        if(send(new_fd, "Connected to sever : make request", 35, 0) == -1)
            perror("send");
        memset(buffer, 0, 1);
        n = read(new_fd, buffer, 255);
        if(n < 0)
            perror("read");
        printf("The message is: %s\n", buffer);
        send(new_fd, "Twerk", 5, 0);
        close(new_fd);
        printf("Closing connection.\n");
        exit(0);
    }
    close(new_fd);  
    }
    return 0;
 }

