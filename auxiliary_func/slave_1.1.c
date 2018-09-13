/*************************************************************************
	> File Name: slave.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年06月24日 星期日 14时24分28秒
 ************************************************************************/

#include "./script/client_script.c"

int send_file(int num, int data_send, int socketfd) {
    char *file_in = NULL;
    switch (num) {
        case 100: {
            file_in = Mem;
            break;
        }
        case 101: {
            file_in = Disk;
            break; 
        }
        case 102: {
            file_in = Cpu;
            break; 
        }
        case 103: {
            file_in = User;
            break; 
        }
        case 104: {
            file_in = System;
            break;  
        }
        case 105: {
            file_in = Proc;
            break;  
        }
        default : {
            break;
        }
    }
    FILE *fp = fopen(file_in, "r");
    if (fp == NULL) {perror("fopen"); return -1;}
    flock(fileno(fp), LOCK_EX);
    char buffer[MAX_SIZE * 2] = {0};
    while (fread(buffer, 1, 1000, fp)) {
        printf("buffer:%s", buffer);
        int  a = send(data_send, buffer, strlen(buffer), 0);
        if (a < 0) {
            perror("Error:");
        }
        memset(buffer, 0, sizeof(buffer));
    }
    fclose(fp);
    fp = fopen(file_in, "w");
    fclose(fp);
    return 1;
}

int file_back(int num) {
    char *file_in = NULL;
    switch (num) {
        case 100: {
            file_in = Mem;
            break;
        }
        case 101: {
            file_in = Disk;
            break; 
        }
        case 102: {
            file_in = Cpu;
            break; 
        }
        case 103: {
            file_in = User;
            break; 
        }
        case 104: {
            file_in = System;
            break;  
        }
        case 105: {
            file_in = Proc;
            break;  
        }
        default : {
            break;
        }
    }
    char buffer[50] = "du ";
    strncat(buffer, file_in, strlen(file_in));
    FILE *fp = popen(buffer, "r");
    char buf[20] = {0};
    fgets(buf, 20, fp);
    if (buf[0] - '0' == 0) {pclose(fp); return 1;}
    pclose(fp);
    return 0;
}


int main() {
    int server_listen, port, count = 1;
    port = atoi("6868");
    if ((server_listen = socket_create(port)) < 0) {
        perror("server_listen");
    }
    int data_listen, data_port;
    data_port = atoi("4869");
    if ((data_listen = socket_create(data_port)) < 0) {
        perror("data_listen");
    }
    int socketfd;
    int fid = fork();
    char *buffer_peer = (char *)calloc(sizeof(char), 64);
    while (fid != 0 && (socketfd = socket_c(buffer_peer, server_listen)) > 0) {
        for (int i = 0; i <= 5; i++) {
            char recv_buffer[MAX_SIZE] = {0};
            if (recv(socketfd, recv_buffer, MAX_SIZE, 0) < 0) {perror("recv"); close(socketfd);}
            //if (!file_back(atoi(recv_buffer))) {
                //printf("11111\n");
                if (send(socketfd, recv_buffer,strlen(recv_buffer), 0) < 0) {perror("send"); close(socketfd);}
            //} else {
                //printf("22222\n");
            //    send(socketfd, "-1", 2, 0);
            //    continue;
            //}
            char *data_peer = (char *)calloc(sizeof(char), 64);
            int data_socket = socket_c(data_peer, data_listen);
            int num = atoi(recv_buffer);
            send_file(num, data_socket, socketfd);
            free(data_peer);
            close(data_socket);
        }
        sleep(10);
        close(socketfd);
    }
    if (fid == 0) {
        system_call();
        exit(0);
    }
    return 0;
}
