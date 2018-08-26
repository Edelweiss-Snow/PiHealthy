/*************************************************************************
	> File Name: client_script.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月26日 星期日 10时20分36秒
 ************************************************************************/

#include "./common.c"

#define Mem "./log/MemLog"
#define Proc "./log/ProcLog"
#define System "./log/systemLog"
#define User "./log/UserLog"
#define Disk "./log/DiskLog"
#define Cpu "./log/CpuLog"

char mem_info[10000] = {0};
char disk_info[10000] = {0};
char cpu_info[10000] = {0};
char user_info[10000] = {0};
char system_info[10000] = {0};
char proc_info[10000] = {0};

void script(int num) {
    switch(num) {
        case 1: {
            FILE *fp = popen("./script/MemLog.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(mem_info, buffer);
            }
            sleep(5);
            pclose(fp);
            break;
        }
        case 2: {
            FILE *fp = popen("./script/CpuLog.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(cpu_info, buffer);
            }
            sleep(5);
            pclose(fp);
            break;
        }
        case 3: {
            FILE *fp = popen("./script/DIskLog.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(disk_info, buffer);
            }
            sleep(60);
            pclose(fp);
            break;
        }
        case 4: {
            FILE *fp = popen("./script/System.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(mem_info, buffer);
            }
            sleep(60);
            pclose(fp);
            break;
        }
        case 5: {
            FILE *fp = popen("./script/UserLog.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(mem_info, buffer);
            }
            sleep(60);
            pclose(fp);
            break;
        }
        case 6: {
            FILE *fp = popen("./script/Process.sh &", "r");
            char buffer[MAX_SIZE] = {0};
            while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                strcat(mem_info, buffer);
            }
            sleep(30);
            pclose(fp);
            break;
        }
    }
    return ;
}

void system_call() {
    int x = 0;
    int pid = fork();
    for (int i = 1; i <= 6; i++) {
        if (pid != 0) {
            x = i;
            pid = fork();
        }
    }
    script(x);
    return;
}

void save_file() {
    FILE *fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", mem_info);
    fclose(fp);
    fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", cpu_info);
    fclose(fp);
    fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", disk_info);
    fclose(fp);
    fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", system_info);
    fclose(fp);
    fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", user_info);
    fclose(fp);
    fp = fopen(Mem, "a+");
    fprintf(fp, "%s\n", proc_info);
    fclose(fp);
}
