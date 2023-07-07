#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <array>
#include <string>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



const int BUF_SIZE = 1024;



void error(const char* message);

class Server {
private:
	const char* Port;	//端口
	int m_Serv_sock, m_Clnt_sock;          // 服务器，客户端sock
	char Buf[BUF_SIZE];
	int m_strLen;
	struct sockaddr_in m_Serv_addr, m_Clnt_addr;     // 服务器，客户端addr
	socklen_t m_clntAddr_size;

	int Option;


public:
	Server(){}
	~Server();

	bool Start(const char* port);

	void init_Addr(const char* Port );

	void Accept();   // accpet() 包装

	int Readen();

	void Writen();

	void Close();

	bool ReuseAddr(bool opt = false); // 地址复用
};

#endif