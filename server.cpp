#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>
void str_server(int);

const int MAXLINE = 1024;
const int SERVER_PORT = 8890;
int main(int argc, char** argv){
	int listenfd;
	struct sockaddr_in server_address;

	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(SERVER_PORT);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);
	int ret = bind(listenfd, (struct sockaddr*)&server_address, sizeof(server_address));
	assert(ret != -1);
	ret = listen(listenfd, 5);
	assert(ret != -1);

	int connfd;
	pid_t childpid;
	while(true){
		struct sockaddr_in client_address;
		socklen_t client_addrlength = sizeof(client_address);
		connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
		if(connfd < 0){
			printf("accept error\n");
			return 1;
		}

		childpid = fork();
		if(fork < 0){
			printf("fork error\n");
			return 2;
		}
		else if(childpid == 0){
			close(listenfd);
			str_server(connfd);
			return 0;
		}
		close(connfd);
	}
}

void err_sys(const char*);
void Writen(int, const char*, size_t);
size_t writen(int, const char*, size_t);

void str_server(int connfd){
	size_t n;
	char buf[MAXLINE];
again:
	while( (n = read(connfd, buf, MAXLINE)) > 0 ){
		Writen(connfd, buf, n);
	}

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

void Writen(int fd, const char* ptr, size_t nbytes){
	if(writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}

size_t writen(int fd, const char* vptr, size_t n){
	size_t nleft;
	size_t nwritten;
	const char* ptr;

	ptr = vptr;
	nleft = n;
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

void err_sys(const char* fmt){
	printf("%s\n", fmt);
	printf("errno:%d\n", errno);
	exit(1);
}
