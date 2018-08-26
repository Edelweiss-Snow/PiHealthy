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
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/MemLog.sh 50", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(mem_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(Mem, "a+");
                    //printf("%s\n", mem_info);
                    fprintf(fin, "%s\n", mem_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(5);
            }
            break;
            exit(0);
        }
        case 2: {
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/CpuLog.sh", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(cpu_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(Cpu, "a+");
                    fprintf(fin, "%s\n", cpu_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(5);
            }
            break;
            exit(0);
        }
        case 3: {
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/DiskLog.sh", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(disk_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(Disk, "a+");
                    fprintf(fin, "%s\n", disk_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(60);
            }
            break;
            exit(0);
        }
        case 4: {
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/System.sh", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(system_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(System, "a+");
                    fprintf(fin, "%s\n", system_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(60);
            }
            break;
            exit(0);
        }
        case 5: {
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/UserLog.sh", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(user_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(User, "a+");
                    fprintf(fin, "%s\n", user_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(60);
            }
            break;
            exit(0);
        }
        case 6: {
            int count = 0;
            while (1) {
                FILE *fp = popen("./script/Process.sh 50", "r");
                char buffer[MAX_SIZE] = {0};
                while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                    strcat(proc_info, buffer);
                }
                pclose(fp);
                count++;
                if (count >= 10) {
                    FILE *fin = fopen(Proc, "a+");
                    fprintf(fin, "%s\n", proc_info);
                    fclose(fin);
                    count = 0;
                }
                sleep(30);
            }
            break;
            exit(0);
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
