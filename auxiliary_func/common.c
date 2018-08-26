/*************************************************************************
	> File Name: common.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年06月10日 星期日 15时42分58秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"

#ifndef DEBUG 
#define DBG(fmt, args...) printf(fmt, ##args)
#else 
#define DBG(fmt, args...)
#endif
#define PI_COUNT 10005

char master_logdir[100] = "/var/log/pihealthd.log";
char client_logdir[100] = "~/log/pihealthd.log";

int socket_create(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in sock_addr = {0};
    if (socket_fd < 0) {
        printf("socket_create error");
        perror("socket_create");
        return -1;
    }
    
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if (bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        perror("bind");
        return -1;
    }

    if (listen(socket_fd, 10) < 0) {
        printf("listen error");
        perror("listen");
        return -1;
    }
    return socket_fd;
}

int socket_connect(int port, char *host) {
    int socket_fd;
    struct sockaddr_in dest_addr = {0};
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd < 0) {
        perror("socket_create");
        return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    
    if (connect(socket_fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("connect");
        return -1;
    }
    return socket_fd;
}

int socket_c(int server_listen) {
    int socketfd;
    char buffer[MAX_SIZE] = {0};
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    if ((socketfd = accept(server_listen, (struct sockaddr*)& client_addr, &len)) > 0) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(struct sockaddr_in);
        bzero(&peer, sizeof(struct sockaddr_in));
        getpeername(socketfd, (struct sockaddr *)&peer, &peer_len);
        char buffer_peer[64] = {'\0'};
        inet_ntop(AF_INET, (void*)&peer.sin_addr, buffer_peer, 63);
    }
    return socketfd;
}

char **get_ip(int *n) {
    char **ip = (char **)calloc(sizeof(char *), 10005);
    for (int i = 0; i < 10005; i++) {
        ip[i] = (char *)calloc(sizeof(char), 30);
    }
    FILE *fin = fopen("./script/IP", "r");
    int i = 0;
    if (fin == NULL) {perror("fopen"); return 0;}
    while (fscanf(fin, "%[^\n]s", ip[i]) != EOF) {
        fgetc(fin);
        i++;
    }
    *n = i;
    return ip;
}

void get_time(FILE *fin) {
    char weak[7][30] = {
        {"星期日"},
        {"星期一"},
        {"星期二"},
        {"星期三"},
        {"星期四"},
        {"星期五"},
        {"星期六"},
    };
    struct tm t;
    time_t now;
    time(&now);
    localtime_r(&now, &t);
    fprintf(fin, "%d年%02d月%02d日--%s--%02d:%02d:%02d\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, weak[t.tm_wday], t.tm_hour, t.tm_min, t.tm_sec);
}
