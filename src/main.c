/*
 * main.c
 *
 *  Created on: 2017年10月11日
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
int NetIsOklt();
int NetIsOk();
void auth(char *basip, char *lpsUserName, char *lpsPwd, char *ifname);

int main(int argc, char *argv[]) {
	char *lpsUserName;
	char *lpsPwd;
	char *ifname;
	char *domain;
	/* 检查命令行参数格式 */
	if (argc<3 || argc>5) {
		fprintf(stderr, "命令行参数错误！\n");
		fprintf(stderr,	"正确的调用格式例子如下：\n");
		fprintf(stderr,	"    %s domain username password\n", argv[0]);
		fprintf(stderr,	"    %s domain username password eth0\n", argv[0]);
		fprintf(stderr,	"    %s domain username password eth1\n", argv[0]);
		fprintf(stderr, "(注：若不指明网卡，默认情况下将使用eth0.2)\n");
		exit(-1);
	} else if (argc == 5) {
		ifname = argv[4]; // 允许从命令行指定设备名
	} else {
		ifname = "eth0.2"; // 缺省情况下使用的设备
	}
	domain=argv[1];
	lpsUserName=argv[2];
	lpsPwd=argv[3];
	while(1){
		
		if(NetIsOk()){
			printf("网络已连接\n");
			
		}else if(NetIsOklt()==1&&NetIsOk()==0){//判断如果联通网络可以ping通并且外部网络不同，即可以进行认证
			auth(domain,lpsUserName,lpsPwd,ifname);
			sleep(20);
		}
		
	}
	
	return 1;
}
