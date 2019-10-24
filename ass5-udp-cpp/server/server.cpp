#include<iostream>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<fstream>
#include<string>

#define PORT 7512
#define MAXLINES 1024

using namespace std;

int main()
{
    int sockfd;
    char* fileName = new char[1];
    char buffer[MAXLINES];
    struct sockaddr_in server,client;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd,(const struct sockaddr*) &server,sizeof(server));


    socklen_t len;
    int n = recvfrom(sockfd,fileName,MAXLINES,0,( struct sockaddr *)&client,&len);
    fileName[n]='\0';
    cout << "Client wants file: " << fileName << endl;
    
    cout << "Opening file" << endl;
    std::ifstream ifs(fileName,ios::ate);
    if(!ifs)
    {
        cout << "file not present";
    }
    else
    {
        int size = ifs.tellg();
        ifs.seekg(ios::beg);
        
        cout << "Reading file. size:"<<size << endl;
        ifs.read(buffer,size);

        cout << "Sending file" << endl;    

        sendto(sockfd,(const char *)buffer,size,0,(const struct sockaddr *) &client,sizeof(client));
        cout << "file sent " << endl;
        cout << "Closing file" << endl;
        ifs.close();
        cout << "Closing socket" << endl;
        close(sockfd);
    }
    
    return 0;
}