#include <stdio.h>  
#include <winsock2.h>  
  
#pragma comment(lib,"ws2_32.lib")  

void Codemaker(char recdata[],char senddata[])
{
	if(recdata[0]=='1')
	{
		senddata[0]='1';
		senddata[1]=recdata[1];
		senddata[2]=recdata[2];
		senddata[3]='0';
		senddata[4]='9';
		senddata[5]='9';
	}
	else if(recdata[0]=='2')
	{
		senddata[0]='0';
		senddata[1]='9';
		senddata[2]='9';
		senddata[3]='1';
		senddata[4]=recdata[1];
		senddata[5]=recdata[2];
	}
}

void SendComman(char recdata[],char senddata[],SOCKET sClient)
{
	char A[1];
	A[0]='A';
	
	Codemaker(recdata,senddata);
	if(recdata[0]=='0')
	{
		send(sClient, senddata, strlen(senddata), 0);
		if(recdata[1]=='0')
		senddata[3]='0';
		else if(recdata[1]=='1')
		senddata[0]='0';
	}
	else
	{
		send(sClient, A,strlen(A),0);
	}
}
  
int main(int argc, char* argv[])  
{  
    //��ʼ��WSA  
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
    char sendData[6]={'0'};
    //char recData[3]={'\0'};
    if(WSAStartup(sockVersion, &wsaData)!=0)  
    {  
        return 0;  
    }  
  
    //�����׽���  
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(slisten == INVALID_SOCKET)  
    {  
        printf("socket error !");  
        return 0;  
    }  
  
    //��IP�Ͷ˿�  
    sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(8888);  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)  
    {  
        printf("bind error !");  
    }  
  
    //��ʼ����  
    if(listen(slisten, 5) == SOCKET_ERROR)  
    {  
        printf("listen error !");  
        return 0;  
    }  
  
    //ѭ����������  
    SOCKET sClient;  
    sockaddr_in remoteAddr;  
    int nAddrlen = sizeof(remoteAddr);  
    char revData[255];   
    while (true)  
    {  
        printf("�ȴ�����...\n");  
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);  
        if(sClient == INVALID_SOCKET)  
        {  
            printf("accept error !");  
            continue;  
        }  
        printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));  
          
        //��������  
        int ret = recv(sClient, revData, 255, 0);         
        if(ret > 0)  
        {  
            revData[ret] = 0x00;  
            printf("%s\n",revData);  
        }  
  		
  		//Codemaker(revData,sendData);
        //��������  
        //char * sendData = "��ã�TCP�ͻ��ˣ�\n";  
        //send(sClient, sendData, strlen(sendData), 0);
		SendComman(revData,sendData,sClient);  
        closesocket(sClient);  
    }  
      
    closesocket(slisten);  
    WSACleanup();  
    return 0;  
} 
