#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<sys/wait.h>

const short MYPORT = 4396;
const int BACKLOG = 10;


int main(void)
{
    int sockfd,acpfd;
    sockaddr_in my_addr;
    sockaddr_in ot_addr;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("error\n");
        return 0;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero),sizeof(my_addr.sin_zero));
    if(bind(sockfd,(sockaddr*)&my_addr,sizeof(sockaddr)) == -1)
    {
        printf("error\n");
        return 0;
    }
    listen(sockfd,BACKLOG);
    socklen_t sin_size = sizeof(sockaddr_in);
    while(1)
    {
        if((acpfd = accept(sockfd,(sockaddr*)&ot_addr,&sin_size)) == -1)
        {
            printf("error\n");
            return 0;
        }
        pid_t pid = fork();
        if(pid == 0)
        {
            char a[100];
            memset(a,0,sizeof(a));
            while(1)
            {
                //int len = recv(acpfd,a,5,0);
                int len = recv(acpfd,a,5,MSG_WAITALL);
                if(len <= 0)
                    break;
                printf("%d %s\n",len,a);
                memset(a,0,sizeof(a));
            }
            printf("finish\n");
            close(acpfd);
            exit(0);
        }
    }

    wait(NULL);
    close(sockfd);
    close(acpfd);




    return 0;
}

