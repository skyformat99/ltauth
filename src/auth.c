/*
 ============================================================================
 Name        : auth.c
 Author      : changdi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define DEST_PORT 808
#define DEST_IP_ADDR "114.247.41.52"
int get_local_ip(char *ifname, char *ip);
void process_info(int fd, char *basip, char *lpsUserName, char *lpsPwd,
		char *ifname) {
	int send_num;
	char wlanip[16];
	//char send_buf [200] = "basip=61.148.2.119&lpsUserName=21102374&lpsPwd=951210&wlanuserip=";
	char send_buf[200];
	char recv_buf[5000];
	char str1[4096];
	char content_len[50];
	int i;
	get_local_ip(ifname, wlanip);
	for (i = 0; i < strlen(wlanip); i++) {
		if (wlanip[i] > 57 || wlanip[i] < 46) {
			wlanip[i] = '\0';
		}
	}
	printf("%s\n", wlanip);
	sprintf(send_buf, "basip=%s&lpsUserName=%s&lpsPwd=%s&wlanuserip=%s", basip,
			lpsUserName, lpsPwd, wlanip);
	while (1)
    {
	printf("begin send\n");
	memset(str1, 0, 4096);
	strcat(str1, "POST /services/portal/portalAuth HTTP/1.1\r\n");
	strcat(str1, "Host: 114.247.41.52:808\r\n");
	sprintf(content_len, "Content-Length: %d\r\n", strlen(send_buf));
	strcat(str1, content_len);
	strcat(str1, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(str1, "\r\n");
	strcat(str1, send_buf);
	printf("str1 = %s\n", str1);
	send_num = send(fd, str1, strlen(str1), 0);
	if (send_num < 0) {
		perror("send error");
		exit(1);
	} else {
		printf("send successful\n");
		printf("begin recv:\n");
		int recv_num = recv(fd, recv_buf, sizeof(recv_buf), 0);
		if (recv_num < 0) {
			perror("recv");
			exit(1);
		} else {
			printf("recv sucess:%s\n", recv_buf);
		}
	}
	break;
	sleep(5);
}
}

void auth(char *basip, char *lpsUserName, char *lpsPwd, char *ifname) {
	int sock_fd;
	struct sockaddr_in addr_serv;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		perror("sock error");
		exit(1);
	} else {
		printf("sock successful");
	}
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(DEST_PORT);
	addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDR);

	if (connect(sock_fd, (struct sockaddr*) (&addr_serv), sizeof(addr_serv))
			< 0) {
		perror("connect error\n");
		exit(1);
	} else {
		printf("connect successful\n");
	}
	process_info(sock_fd, basip, lpsUserName, lpsPwd, ifname);
}

