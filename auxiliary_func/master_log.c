/*************************************************************************
	> File Name: master_log.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月26日 星期日 10时32分16秒
 ************************************************************************/

#include "./common.c"

int record_flag = 0;
char warn_logdir[100] = "/var/log/warning.log";

void master_log(char *ip) {
    FILE *fin = fopen(master_logdir, "a+");
    //flock(fileno(fin), LOCK_EX);
    get_time(fin);
    switch(record_flag) {
        case -1: {
            fprintf(fin, "connect refused! IP:%s\n", ip);
            break;
        }
        case -2: {
            fprintf(fin, "file connect refused! IP:%s\n", ip);
            break;
        }
        case 100: {
            fprintf(fin, "recv Cpu.log fail! IP:%s\n", ip);
            break;
        }
        case 101: {
            fprintf(fin, "recv Mem.log fail! IP:%s\n", ip);
            break;
        }
        case 102: {
            fprintf(fin, "recv Disk.log fail! IP:%s\n", ip);
            break;
        }
        case 103: {
            fprintf(fin, "recv Sys.log fail! IP:%s\n", ip);
            break;
        }
        case 104: {
            fprintf(fin, "recv Users.log fail! IP:%s\n", ip);
            break;
        }
        case 105: {
            fprintf(fin, "recv Proc.log fail! IP:%s\n", ip);
            break;
        }
        case 1: {
            fprintf(fin, "recv success! IP:%s\n", ip);
            break;
        }
        case 0: {
            fprintf(fin, "not found IP!\n");
            break;
        }
    } 
    fclose(fin);
    
    return ;
}

void recv_warn_file(char *buffer_peer, int socketfd) {
    FILE *fp = fopen(warn_logdir, "a+");
    //flock(fileno(fp), LOCK_EX);
    get_time(fp);
    char buffer[MAX_SIZE] = {0};
    printf("------%s------\n", buffer_peer);
    while (recv(socketfd, buffer, MAX_SIZE, 0) > 0) {
        printf("%s", buffer);
        fwrite(buffer, sizeof(char), strlen(buffer), fp);
        memset(buffer, 0, MAX_SIZE);
    }
    //flock(fileno(fp), LOCK_UN);
    fclose(fp); 
    close(socketfd);
    return ;
}
