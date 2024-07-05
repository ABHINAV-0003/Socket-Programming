#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SERVER_PORT 5432
#define MAX_LINE 256
int main(int argc, char * argv[])
{
FILE *fp;
struct hostent *hp; // Server info
struct sockaddr_in sin; // Server address
char *host; // Host name
char buf[MAX_LINE]; // Buffer for messages
int s; // Socket descriptor
int len; // Message length
// Check command line arguments
if (argc==2) {
host = argv[1];
}
else {
fprintf(stderr, "usage: simplex-talk host\n");
exit(1);
}
// Get server info
hp = gethostbyname(host);
if (!hp) {
fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
exit(1);
}
// Set up server address
memset((char *)&sin, 0, sizeof(sin));
sin.sin_family = AF_INET;
memcpy((char *)&sin.sin_addr, hp->h_addr, hp->h_length);
sin.sin_port = htons(SERVER_PORT);
// Create socket
if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
perror("simplex-talk: socket");
exit(1);
}
// Connect to server
if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
perror("simplex-talk: connect");
close(s);
exit(1);
}
printf("Connected to server.\n");
// Main client loop
while (fgets(buf, sizeof(buf), stdin)) {
buf[MAX_LINE-1] = '\0';
len = strlen(buf) + 1;
// Send message to server
send(s, buf, len, 0);
printf("Sent to server: %s\n", buf);
// Receive response from server
char response[MAX_LINE];
int response_len = recv(s, response, sizeof(response) - 1, 0);
if (response_len >= 0) {
response[response_len] = '\0'; // Null-terminate the response
printf("Received from server: %s\n", response);
}
}
close(s); // Close the connection
printf("Disconnected from server.\n");
}