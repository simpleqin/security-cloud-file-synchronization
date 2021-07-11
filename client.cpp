#include<cstdio>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

const short DETPORT = 4396;


int main(int argc, char *argv[])
{
    int sockfd;
    sockaddr_in det_addr;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("error");
        return 0;
    }
    
    det_addr.sin_family = AF_INET;
    det_addr.sin_port = htons(DETPORT);
    det_addr.sin_addr.s_addr = INADDR_ANY;
    //det_addr.sin_addr.s_addr = inet_addr("192.168.1.105");
    bzero(&(det_addr.sin_zero),sizeof(det_addr.sin_zero));
    if(connect(sockfd,(sockaddr*)&det_addr,sizeof(sockaddr)) == -1)
    {
        printf("connect error\n");
        return 0;
    }
    while(1)
    {
        char a[100];
        scanf("%s",a);
        //send(sockfd,argv[1],sizeof(argv[1]),0);
        send(sockfd,a,strlen(a),0);
        if(a[0] == '6')
            break;
    }
    close(sockfd);
    printf("end\n");




    return 0;
}
