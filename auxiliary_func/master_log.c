/*************************************************************************
	> File Name: master_log.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月26日 星期日 10时32分16秒
 ************************************************************************/

#include "./common.c"

int record_flag = 0;

void master_log(char *ip, FILE *fin) {
    get_time(fin);
    switch(record_flag) {
        case -1: {
            fprintf(fin, "获取对端连接建立失败，失败对端IP为%s\n", ip);
            break;
        }
        case -2: {
            fprintf(fin, "传输文件连接建立失败，失败对端IP为%s\n", ip);
            break;
        }
        case 100: {
            fprintf(fin, "接受文件失败，失败文件为Cpu.log，对端IP为%s\n", ip);
            break;
        }
        case 101: {
            fprintf(fin, "接受文件失败，失败文件为Mem.log，对端IP为%s\n", ip);
            break;
        }
        case 102: {
            fprintf(fin, "接受文件失败，失败文件为Disk.log，对端IP为%s\n", ip);
            break;
        }
        case 103: {
            fprintf(fin, "接受文件失败，失败文件为Sys.log，对端IP为%s\n", ip);
            break;
        }
        case 104: {
            fprintf(fin, "接受文件失败，失败文件为Users.log，对端IP为%s\n", ip);
            break;
        }
        case 105: {
            fprintf(fin, "接受文件失败，失败文件为Proc.log，对端IP为%s\n", ip);
            break;
        }
        default: {
            fprintf(fin, "接收文件success！，成功的对端IP为%s", ip);
            break;
        }
    }   
}
