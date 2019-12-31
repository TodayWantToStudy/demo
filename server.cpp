#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>

const int SERVER_PORT = 8890;
int main(int argc, char** argv){
	int linstenfd;
	struct sockaddr_in server_address;
2
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(SERVER_PORT);

	linstenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(linstenfd >= 0);
	int ret = bind(linstenfd, (struct sockaddr*)&server_address, sizeof(server_address));
	assert(ret != -1);
	ret = linstenfd(linstenfd, 5);
	assert(ret != -1);

	int connfd;
	pid_t childpid;
	while(true){
		struct sockaddr_in client_address;
		socklen_t client_addrlength = sizeof(client_address);
		connfd = accept(linstenfd, (struct sockaddr*)&client_address, &client_addrlength);
		if(connfd < 0){
			printf("accept error\n");
			exit(1);
		}

		childpid = fork();
		if(fork < 0){
			printf("fork error\n");
			exit(2);
		}
		else if(childpid == 0){
			close(linstenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void str_echo(int connfd){
	char buf[1024];
	int len = read(connfd, buf, 1024);
	if(len < 0){
		printf("read error\n");
	}
	else if(len == 0){
		printf("read nothing\n");
	}
	else if(len > 0){
		printf("read:\n%s\n", buf);
		int len = write(connfd, buf, len);
		if(len < 0){
			printf("write error\n");
		}
		else if(len == 0){
			printf("write nothing\n");
		}
		else if(len > 0){
			printf("write succussful\n");
		}
	}
}