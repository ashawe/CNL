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

    int sockfd;
    sockaddr_in server;
    char buffer[MAXLINES];
    string fileName;

    if( (sockfd = socket(AF_INET,SOCK_STREAM,0) ) < 0 )
    {
        cout << "err";
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd,(const sockaddr *) &server,sizeof(server)) < 0 )
        cout << "error";

    cout << "Enter fileName" << endl;
    cin >> fileName;
    send(sockfd,fileName.c_str(),fileName.length(),0);

    int n = read(sockfd,buffer,MAXLINES);

    ofstream ofs(fileName,ios::out);
    ofs.write(buffer,n);
    ofs.close();

    return 0;
}