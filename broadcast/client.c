#include <stdio.h>          // for printf() and fprintf() 
#include <sys/socket.h>     // for socket(), bind(), and connect() 
#include <arpa/inet.h>      // for sockaddr_in and inet_ntoa() 
#include <stdlib.h>         // for atoi() and exit() 
#include <string.h>         // for memset() 
#include <unistd.h>         // for close() 
#include <fcntl.h>          // for fcntl() 
#include <errno.h>

#include <sys/epoll.h>

#define BUFSIZE 1024         // Size of receive buffer 

static int make_socket_non_blocking ( int sfd )
{
    int flags, s;
  
    flags = fcntl (sfd, F_GETFL, 0);
    
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }
                          
    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }
                                                    
    return 0;
}

int main( int argc, char *argv[] )
{
    int             sockfd;            // Socket descriptors for server
    int                broadcast = 1;    // Socket Option.
    struct sockaddr_in cliaddr;        // Broadcast Receiver Address
    struct sockaddr_in srvaddr;     // Broadcast Server Address
    int                   srvaddr_len = sizeof( srvaddr );
    
    char    buffer[BUFSIZE];        // Input and Receive buffer
    int     i;                      // For loop use
    int        running = 1;            // Main Loop
    int        rcvlen = 0;                // Receive Message Size
    
    int                     epfd;                   // EPOLL File Descriptor. 
    struct epoll_event      ev;                     // Used for EPOLL.
    struct epoll_event      events[5];                // Used for EPOLL.
    int                     noEvents;               // EPOLL event number.
    
    printf( "This process is a UDP broadcast echo client process!.\n" );
    
    // Test for correct number of arguments
    
    if ( argc < 2 )     
    {
        fprintf( stderr, "Usage:  %s <Local Port> ...\n", argv[0]);
        exit(1);
    }
    
    // Create Socket
    
    if( ( sockfd = socket( AF_INET, SOCK_DGRAM, 0 ) ) == -1 )
    {
        perror( "Create Sockfd Fail!!\n" );
        exit(1);
    }
    
    // Nonblocking
    
    make_socket_non_blocking( sockfd );
    
    // Reset the addresses
    
    memset( &cliaddr, 0, sizeof( cliaddr ) );
    
    // Setup the addresses
    
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons( atoi( argv[1] ) );
    cliaddr.sin_addr.s_addr = INADDR_ANY;
                    
    if( bind( sockfd, (struct sockaddr*) &cliaddr, sizeof( cliaddr ) ) == -1 )
    {
        perror("bind");
        exit(1);
    }
                                                    
    // Create epoll file descriptor.

    epfd = epoll_create( 5 );
    
    // Add socket into the EPOLL set.
    
    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl( epfd, EPOLL_CTL_ADD, sockfd, &ev );
        
    while ( running )
    {
        // Wait for events.
        // int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
        // Specifying a timeout of -1 makes epoll_wait() wait indefinitely.
        
        noEvents = epoll_wait( epfd, events, FD_SETSIZE , -1 );
        
        for( i = 0 ; i < noEvents; i++ )
        {
            if( events[i].events & EPOLLIN && sockfd == events[i].data.fd )
            {
                memset( buffer, 0, BUFSIZE );
                
                while( ( rcvlen = recvfrom( sockfd, buffer, BUFSIZE, 0,
                                             ( struct sockaddr * )&srvaddr, (socklen_t *)&srvaddr_len ) ) 
                        != -1 )
                {
                    printf( "Receive from %s_%d: %s", inet_ntoa( srvaddr.sin_addr ), ntohs( srvaddr.sin_port ), buffer );
                    
                    if( sendto( sockfd, buffer, rcvlen, 0,
                                ( struct sockaddr * )&srvaddr, sizeof( srvaddr ) ) == -1 )
                    {
                        printf( "Send Fail!\n" );
                        running = 0;
                        continue;
                    }
                }
                
                if( errno != EAGAIN )
                {
                    perror( "Receive the brocast message response FAIL!!\n" );
                    running = 0;
                }
            }
        }
    }

    // Close the socket 
    
    close( sockfd );
    close( epfd );

    return 0;
}
