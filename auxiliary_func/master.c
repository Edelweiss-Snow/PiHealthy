/*************************************************************************
	> File Name: client.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年06月10日 星期日 17时26分19秒
 ************************************************************************/
 
#include "./script/master_log.c"

int send_signal(int socketfd, int data_socket, int num) {
    char c[20] = {0};
    sprintf(c, "%d\n", num);
    if (send(socketfd, c, strlen(c), 0) < 0) {close(socketfd); close(data_socket); return num;} 
    return 1;
}

int generate_name(int code, char *logname) {
    switch (code) {
        case 100:
            strcat(logname, "/Mem.log");
            break;
        case 101:
            strcat(logname, "/Disk.log");
            break;
        case 102:
            strcat(logname, "/Cpu.log");
            break;
        case 103:
            strcat(logname, "/Users.log");
            break;
        case 104:
            strcat(logname, "/Sys.log");
            break;
        case 105:
            strcat(logname, "/Proc.log");
            break;
    }
    return 0;
}

void recv_file(char *ip, int num, int data_socket, char *client, int socketfd) {
    char logdir[100] = "/tmp";
    char arg[MAX_SIZE] = {0};
    strcat(logdir, "/");
    strcat(logdir, client);
    mkdir(logdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    generate_name(num, logdir);
    FILE *fp = fopen(logdir, "a+");
    int a;
    char buffer[MAX_SIZE] = {0};
    printf("------%s------%s\n", ip, logdir);
    while ((a = recv(data_socket, buffer, 1000, 0)) > 0) {
        printf("%s", buffer);
        fwrite(buffer, 1, a, fp);
        memset(buffer, 0, MAX_SIZE);
    }
    fclose(fp);
    close(data_socket);
}

int slave(int ip_count, int port, char **ip, int n) {
    if (ip_count > n) return 0;
    int socketfd = socket_connect(port, ip[ip_count]);
    if (socketfd < 0) {
        //perror("socketfd");
        close(socketfd);
        return -1;
    } 
    if (socketfd > 0) {
        int data_port = atoi("4869");
        char temp[100] = "client_";
        strcat(temp, ip[ip_count]);
        for (int i = 100; i <= 105; i++) {
            int data_socket = socket_connect(data_port, ip[ip_count]);
            if (data_socket < 0) {
                //printf("1\n");
                //perror("data_socket_connect");
                close(socketfd);
                close(data_socket);
                return -2;
            }
            int flag = send_signal(socketfd, data_socket, i);
            if (flag == 1) {
                recv_file(ip[ip_count], i, data_socket, temp, socketfd);
            } else {
                close(socketfd);
                close(data_socket);
                return flag;
            }
        }
    }
    close(socketfd);
    return 1;
}

int main(int argc, char **argv) {
    FILE *fin = fopen(master_logdir, "a+");
    if (fin == NULL) {perror("fopen"); return 0;}
    get_time(fin);
    fprintf(fin, "运行启动\n");
    fclose(fin);
    char **ip = NULL;
    int n = 0, x = 0, ip_count = 0;
    ip = get_ip(&n);
    int port = atoi("6868");
    int fid = fork();
    if (fid) {
        for (int i = 0; i < 10; i += 10) {
            if (fid != 0) {
                x = i;
                fid = fork();
            }
        }
        if (fid) {
            int wpid, status;
            while ((wpid = wait(&status)) > 0);
        }
        while (fid == 0) {
            int j = 0;
            while (j < 10) {
                ip_count = x + j;
                record_flag = slave(ip_count, port, ip, n);
                master_log(ip[ip_count]);
                j++;
                sleep(3);
            }
        }
    }
    if (fid == 0) {
        int server_listen, port, count = 1;
        port = atoi("9694");
        if ((server_listen = socket_create(port)) < 0) {
            perror("server_listen");
        } 
        int socketfd;
        char *buffer_peer = (char *)calloc(sizeof(char), 64);
        while ((socketfd = socket_c(buffer_peer, server_listen)) > 0) {
            recv_warn_file(buffer_peer, socketfd);
        }
    }
    return 0;
}
