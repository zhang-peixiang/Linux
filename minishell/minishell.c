#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


char g_command[1024];

// 获得输入的命令
int GetCommand()
{
    printf("[minishell@localhost minishell] ");
    fflush(stdout);
    memset(g_command,'\0',sizeof(g_command));
    if(fgets(g_command,sizeof(g_command)-1,stdin)==NULL)
    {
        perror("fgets error");
        return -1;
    }
    printf("%s\n",g_command);
    return 0;
}

int ExecCommand(char* argv[])
{
    //创建子进程
    //子进程程序替换
    if(argv[0]==NULL)
    {
        printf("ExecCommand failed\n");
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid == 0)
    {
        // child--> 进程程序替换
        execvp(argv[0],argv);
        
        exit(0);
    }
    else
    {
        // father
        waitpid(pid,NULL,0);
    }

    return 0;
}

int DealCommand(char* command)
{
    int argc=0;
    char* argv[1024]={0};
    int i=0;
    while(*command)
    {
        if(!isspace(*command)&& *command!='\0')
        {
            argv[argc]=command;
            argc++;

             while(!isspace(*command)&& *command!='\0')
             {
                command++;  
             }
            
             *command='\0';
         }
        command++;
    }
    argv[argc]=NULL;

    for(i=0;i<argc;i++)
    {
        printf("%d;%s\n",i,argv[i]);
    }

    
    ExecCommand(argv);
    return 0;
}



int main()
{
    while(1)
    {
        if((GetCommand())== -1)
        {
            continue;
        }


        DealCommand(g_command);
    }
     return 0;
}
