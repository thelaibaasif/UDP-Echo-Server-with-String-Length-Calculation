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
struct sockaddr_in servaddr, cliaddr;
//creating
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}

memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);

if (bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}

int len, n;
len = sizeof(cliaddr); //len is value/resuslt

n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
buffer[n] = '\0';

printf("Client : %s\n", buffer);
printf("Length of string: %zu\n", strlen(buffer));

//send
sendto(sockfd, (const char *)buffer, strlen(buffer),
MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
return 0;
}
