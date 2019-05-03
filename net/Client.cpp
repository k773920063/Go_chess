#include <WINSOCK2.H>  
#include <STDIO.H>  
#include<windows.h>
  
#pragma  comment(lib,"ws2_32.lib")  

int Talk(char* sendData,char recData[])
{
	WORD sockVersion = MAKEWORD(2,2);  
    WSADATA data;   
    if(WSAStartup(sockVersion, &data) != 0)  
    {  
        return 0;  
    }  
  
    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(sclient == INVALID_SOCKET)  
    {  
        printf("invalid socket !");  
        return 0;  
    }  
  
    sockaddr_in serAddr;  
    serAddr.sin_family = AF_INET;  
    serAddr.sin_port = htons(8888);  
    serAddr.sin_addr.S_un.S_addr = inet_addr("10.21.151.28");
	 
	   
    if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)  
    {  
        printf("connect error !\n");  
        closesocket(sclient);  
        return 0;  
    }  
    //char * sendData = "你好，TCP服务端，我是客户端!\n";
	//scanf("%s",sendData);  
    send(sclient, sendData, strlen(sendData), 0);  
  
    //char recData[255];  
    int ret = recv(sclient, recData, 255, 0);  
    if(ret > 0)  
    {  
        recData[ret] = 0x00;  
        printf("%s\n",recData);  
    }  
    
    closesocket(sclient);  
    WSACleanup();  
    return 0;  
}
  
  
int main(int argc, char* argv[])  
{  
    char sendData[100]={'\0'};
    while(true)
    {
	scanf("%s",sendData);
    Talk(sendData);
    for(int i=0;i<100;i++)
    {
    	sendData[i]='\0';
	}
	}
}  
