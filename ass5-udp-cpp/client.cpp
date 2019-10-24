#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string>

#define PORT 7512
#define MAXLINES 1024

using namespace std;

int main()
{
    int sockfd;
    string fileName;
    char buffer[MAXLINES];
    struct sockaddr_in server;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    memset(&server,0,sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    cout << "Enter file name" << endl;
    cin >> fileName;

    cout << fileName.c_str() << endl;
    sendto(sockfd, (const char *)fileName.c_str(), fileName.length(),0,(const struct sockaddr *)&server, sizeof(server));
    cout << "Sent filename to server" << endl;

    cout << "Waiting for response" << endl;
    socklen_t len;
    int n = recvfrom(sockfd,(char *)buffer,sizeof(buffer),0,(struct sockaddr *)&server,&len);
    buffer[n] = '\0';
    cout << "Response recieved: " << buffer << endl;
    
    ofstream ofs;
    cout << "Creating file" << endl;
    ofs.open(fileName,ios::out);
    cout << "Writing to file" << endl;
    ofs.write(buffer,n);
    cout << "Closing file" << endl;
    ofs.close();
    cout << "Closing socket"<<endl;
    close(sockfd);
    return 0;
}