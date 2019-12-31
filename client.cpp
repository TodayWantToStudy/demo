#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<assert.h>

const int SETVER_PORT = 8890;
int main(int argc, char** argv){
	int sockfd;
	struct sockaddr_in server_addr;
	if(argc != 2){
		printf("usage: <exename> <IPaddress>\n");
		return 1;		
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[2]);
	server_addr.sin_port = htons(SETVER_PORT);

	int ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	assert(ret >= 0);

	str_client(stdin, sockfd);
	return 0;
}
void str_client(FILE* fp, int sockfd){
	char sendline[1024], recvline[1024];
	while(fgets(sendline, 1024, fp) != NULL){
		write(sockfd, sendline, strlen(sendline));
		read(sockfd, recvline, 1024);
		fputs(recvline, stdout);
	}
}

size_t writen(int fd, const char* vptr, size_t n){
	size_t nleft = n;
	const char* ptr = vptr;

	size_t nwritten;
	while(nleft > 0){
		if( (nwritten = write(fd, ptr, nleft)) <= 0 ){
			if(nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}