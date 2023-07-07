#include "server.h"

void error(const char *message)
{
    std::cout << &message << std::endl; //  打印错误信息
    exit(1);
}

Server::~Server()
{
    close(m_Serv_sock);
}

bool Server::Start(const char *port)
{
    Port = port;
    m_Serv_sock = socket(PF_INET, SOCK_STREAM, 0); // IPV4, TCP协议
    if (m_Serv_sock == -1)
        error("socket() error!");

    memset(&m_Serv_addr, 0, sizeof(m_Serv_addr));
    m_Serv_addr.sin_family = AF_INET;
    m_Serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_Serv_addr.sin_port = htons(atoi(Port));

    Server::ReuseAddr(true);

    if (bind(m_Serv_sock, (sockaddr *)&m_Serv_addr, sizeof(m_Serv_addr)) == -1)
        error("bind() error!");
    if (listen(m_Serv_sock, 5) != -1)
        std::cout << "正在监听 " << port << " 端口..." << std::endl;
    else
        error("listen() error!");
    return true;
}

// 地址初始化
void Server::init_Addr(const char *Port)
{
    memset(&m_Serv_addr, 0, sizeof(m_Serv_addr));
    m_Serv_addr.sin_family = AF_INET;
    m_Serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_Serv_addr.sin_port = htons(atoi(Port));
}

// 接受客户端连接
void Server::Accept()
{
    m_clntAddr_size = sizeof(m_Clnt_addr);
    m_Clnt_sock = accept(m_Serv_sock, (sockaddr *)&m_Clnt_addr, &m_clntAddr_size);
    if (m_Clnt_sock == -1)
        error("accpet() error!");
    else
        std::cout << "已连接" << std::endl;
}

// 读取客户端发送的数据
int Server::Readen()
{
    m_strLen = read(m_Clnt_sock, Buf, BUF_SIZE);
    Buf[m_strLen] = 0;
    if (m_strLen == 0)
        return 0;
    return 1;
}

void Server::Writen()
{
    write(m_Clnt_sock, Buf, m_strLen);
}

void Server::Close()
{
    close(m_Clnt_sock);
}

bool Server::ReuseAddr(bool opt)
{
    Option = opt;
    int Optlen = sizeof(Option);
    if ((setsockopt(m_Serv_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&Option, Optlen)) == 0)
        return true;
    else
        return false;
}