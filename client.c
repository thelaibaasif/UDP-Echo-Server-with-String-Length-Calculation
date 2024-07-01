#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAXLINE 1052

int main() {
int sockfd;
char buffer[MAXLINE];
struct sockaddr_in servaddr;

//creating
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}

memset(&servaddr, 0, sizeof(servaddr));

servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr = INADDR_ANY;

int n, len;
printf("Enter a string: ");
fgets(buffer, MAXLINE, stdin);

sendto(sockfd, (const char *)buffer, strlen(buffer),
MSG_CONFIRM, (const struct sockaddr *) &servaddr,
sizeof(servaddr));

printf("String sent to server: %s\n", buffer);

n = recvfrom(sockfd, (char *)buffer, MAXLINE,
MSG_WAITALL, (struct sockaddr *) &servaddr,
&len);
buffer[n] = '\0';
printf("Server : %s\n", buffer);

close(sockfd);
return 0;
}
