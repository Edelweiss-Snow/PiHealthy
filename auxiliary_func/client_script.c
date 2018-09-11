/*************************************************************************
	> File Name: client_script.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月26日 星期日 10时20分36秒
 ************************************************************************/

#include "./common.c"

char Mem[50] = "./log/MemLog";
char Proc[50] = "./log/ProcLog";
char System[50] = "./log/systemLog";
char User[50] = "./log/UserLog";
char Disk[50] = "./log/DiskLog";
char Cpu[50] = "./log/CpuLog";

char mem_fp[100] = "./script/MemLog.sh 50";
char disk_fp[100] = "./script/DiskLog.sh";
char cpu_fp[100] = "./script/CpuLog.sh";
char user_fp[100] = "./script/UserLog.sh";
char sys_fp[100] = "./script/System.sh";
char proc_fp[100] = "./script/Process.sh";

char mem_info[10000] = {0};
char disk_info[10000] = {0};
char cpu_info[10000] = {0};
char user_info[10000] = {0};
char sys_info[10000] = {0};
char proc_info[10000] = {0};

char warn[10000] = {0};
char mem_warn[100] = "Mem warning Mem used";
char disk_warn[100] = "Disk warning Disk used";
char cpu_warn[100] = "Cpu warning Cpu temperature";
char proc_warn[100] = "find bad course\n";
char sign[100] = "signal 3";
int len = 8;
int sleep_time[7] = {0, 5, 5, 60, 60, 60, 30};

void script(int num) {
    char *temp = NULL;
    char *info = NULL;
    char *log_dir = NULL;
    char *file_in = NULL;
    switch(num) {
        case 1: {log_dir = mem_fp; file_in = Mem; temp = mem_warn; info = mem_info; break;} 
        case 2: {log_dir = disk_fp; file_in = Disk; temp = disk_warn; info = disk_info; break;}
        case 3: {log_dir = cpu_fp; file_in = Cpu; temp = cpu_warn; info = cpu_info; break;}
        case 4: {log_dir = user_fp; file_in = User; info = user_info; break;}
        case 5: {log_dir = sys_fp; file_in = System; info = sys_info; break;}
        case 6: {log_dir = proc_fp; file_in = Proc; temp = proc_warn; info = proc_info; break;}
    }
    int count = 0;
    while (1) {
        char buffer[MAX_SIZE] = {0};
        FILE *fp = popen(log_dir, "r");
        while (fgets(buffer, MAX_SIZE, fp) != NULL) {
            strcat(info, buffer);
            if (!strncmp(sign, buffer, len)) {
                strcat(warn, temp);
                strcat(warn, buffer + len);
                int socketfd = socket_connect(9694, master);
                if (socketfd > 0) send(socketfd, warn, strlen(warn), 0);
                memset(warn, 0, 10000);
                close(socketfd);
            }
        }
        count++;
        pclose(fp);
        if (count >= 10) {
            FILE *fin = fopen(file_in, "a+");
            flock(fileno(fin), LOCK_EX);
            fprintf(fin, "%s\n", info);
            memset(info, 0, 10000);
            count = 0;
            fclose(fin);
        }
        sleep(sleep_time[num]);
    }
    return ;
}

void system_call() {
    int x = 0;
    int pid = 1;
    for (int i = 1; i <= 6; i++) {
        if (pid != 0) {
            x = i;
            pid = fork();
        }
    }
    if (x == 0) exit(0);
    script(x);
    return;
}
