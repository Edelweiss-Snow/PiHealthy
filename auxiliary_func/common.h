/*************************************************************************
	> File Name: common.h
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年06月10日 星期日 15时13分33秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <sys/stat.h>

#define MAX_SIZE 1024

int socket_create(int port);
int socket_connect(int port, char *host);

#endif
