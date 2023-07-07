#ifndef CLIENT_H_
#define CLIENT_H_

#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUF_SIZE = 1024;


void PrintInfo(const std::string& message, int opt = 1);

void error(const std::string& message);

class Client {
private:
    int m_Sock;
    char m_Buf[BUF_SIZE];

    int m_Strlen;
    int Option;

    struct sockaddr_in m_Serv_addr;

public:
    Client();
    ~Client();

    bool Start(const char* IP, const char*);

    void Init_Addr(const char* IP, const char* port);  // 地址初始化

    void Writen();

    int Readn();

    int ChecktoClose(const char* buf); // 检查输入，是否半关闭

    bool ReuseAddr(bool opt = false);  // 地址复用

    char* GetBuf();
};
#endif