#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256
int main()
{
struct sockaddr_in sin; // Server address structure
char buf[MAX_LINE]; // Buffer for storing incoming messages
int len; // Length of received message
int s, new_s; // Socket descriptors
// Initialize server address structure
memset((char *)&sin, 0, sizeof(sin));
sin.sin_family = AF_INET;
sin.sin_addr.s_addr = INADDR_ANY;
sin.sin_port = htons(SERVER_PORT);
// Create a new socket
if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
perror("simplex-talk: socket");
exit(1);
}
// Bind the socket to the server address and port
if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
perror("simplex-talk: bind");
exit(1);
}
// Listen for incoming connections
listen(s, MAX_PENDING);
printf("Server started. Listening for connections...\n");
// Main server loop
while(1) {
// Accept a new connection
if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
perror("simplex-talk: accept");
exit(1);
}
printf("Connection accepted from client.\n");
// Receive messages from the client
while (len = recv(new_s, buf, sizeof(buf), 0)) {
buf[len] = '\0';
printf("Received message from client: %s\n", buf);
// Echo the received message back to the client
send(new_s, buf, len, 0);
printf("Sent message to client: %s\n", buf);
}
// Close the connection
printf("Connection with client closed.\n");
close(new_s);
}
}