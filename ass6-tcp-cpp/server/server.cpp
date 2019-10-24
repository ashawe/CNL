#include<iostream>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<string>
#include<fstream>
#include <arpa/inet.h>
#include<sys/socket.h>

#define PORT 6511
#define MAXLINES 1024
using namespace std;
int main()
{

    int sockfd,connfd;
    sockaddr_in server,client;
    char buffer[MAXLINES];
    char fileBuffer[MAXLINES];

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    

    bind(sockfd,(const sockaddr*) &server,sizeof(server));

    listen(sockfd,5);
    socklen_t len;
    connfd = accept(sockfd, (sockaddr *)&client, &len);

     if (connfd < 0) 
     {
         cout << "failse";
     }
     else
     {
         cout << "success";
     }

    int n = read(connfd,buffer,sizeof(buffer));
    buffer[n] = '\0';
    cout << "Client said: " << buffer << endl;

    ifstream ifs(buffer,ios::in|ios::ate);
    int size = ifs.tellg();
    ifs.seekg(ios::beg);
    ifs.read(fileBuffer,size);
    send(connfd,fileBuffer,size,0);

    return 0;
}