#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("[ERROR] fork:");
        exit(0);
    }
    else if (pid == 0)
    {
        printf("Child A process running... < %d>\n", getpid()); // stdout 行缓存
        sleep(2);
        exit(88);
    }
    else if (pid > 0)
    {
        int status = 0;
        // pid_t rcpid = wait(&status); //会阻塞父进程  status 子进程推出变量值指针
        // pid_t rcpid = waitpid(-1,&status,0);  // -1任一子进程,默认第三个参数是0，和wait用法一样

        int rcpid = 0;
        while( (rcpid = (waitpid(-1, &status, WNOHANG)))==0)
        {

        }

        printf("rcpid = %d,exit code = %d\n", rcpid, WEXITSTATUS(status));
    }
    return 0;
}