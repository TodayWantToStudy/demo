#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>
void str_client(FILE*, int);
size_t writen(int, const char*, size_t);

const int MAXLINE = 1024;
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
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(SETVER_PORT);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	assert(ret >= 0);

	str_client(stdin, sockfd);
	return 0;
}


void err_sys(const char*);
void Writen(int, const char*, size_t);
size_t writen(int, const char*, size_t);


size_t my_read(int, char*);
size_t readline(int, char*, size_t);

void str_client(FILE* fp, int sockfd){
	size_t rc;
	char sendline[MAXLINE], recvline[MAXLINE];
	while(fgets(sendline, MAXLINE, fp) != NULL){
		Writen(sockfd,sendline, strlen(sendline));
		if(readline(sockfd, recvline, MAXLINE) < 0){
			printf("readline error");
			printf("errno %d", errno);
			exit(1);
		}
		fputs(recvline, stdout);
	}
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

static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];
size_t my_read(int fd, char* ptr){
	if(read_cnt <= 0){
	again:
		if( (read_cnt = read(fd, read_buf, MAXLINE)) < 0 ){
			if(errno == EINTR)
				goto again;
			return -1;
		}
		else if( read_cnt == 0 ){
			return 0;
		}
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}
size_t readline(int fd, char* vptr, size_t maxlen){
	size_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for(int n=1; n<maxlen; n++){
		if( (rc = my_read(fd, &c)) == 1 ){
			*ptr++ = c;
			if(c == '\n')
				break;
		}
		else if(rc == 0){
			*ptr = 0;
			return n-1;
		}
		else{
			return -1;
		}
	}

	*ptr = 0;
	return n;
}
