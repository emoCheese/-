#include "client.h"

Client::Client() {}

Client::~Client()
{
    close(m_Sock);
}

bool Client::Start(const char *IP, const char *port)
{
    m_Sock = socket(PF_INET, SOCK_STREAM, 0);
    if (m_Sock == -1)
        error("socket error!");

    Client::ReuseAddr(true);

    memset(&m_Serv_addr, 0, sizeof(m_Serv_addr));
    m_Serv_addr.sin_port = htons(atoi(port));
    m_Serv_addr.sin_family = AF_INET;
    m_Serv_addr.sin_addr.s_addr = inet_addr(IP);
    
    if (connect(m_Sock, (sockaddr *)&m_Serv_addr, sizeof(m_Serv_addr)) == -1)
        error("connect error!");
    else
        std::cout << "正在连接...." << std::endl;

    return true;
}

void Client::Init_Addr(const char *IP, const char *port)
{
    memset(&m_Serv_addr, 0, sizeof(m_Serv_addr));
    m_Serv_addr.sin_port = htons(atoi(port));
    m_Serv_addr.sin_family = AF_INET;
    m_Serv_addr.sin_addr.s_addr = inet_addr(IP);
}

int Client::ChecktoClose(const char *buf)
{
    if (!strcmp(buf, "q") || !strcmp(buf, "Q"))
    {
        shutdown(m_Sock, SHUT_WR);
        return 0;
    }
    return 1;
}

void Client::Writen()
{
    PrintInfo("请输入消息(输入Q或q退出): ", 0);
    std::cin >> m_Buf;
    if (ChecktoClose(m_Buf))
        write(m_Sock, m_Buf, sizeof(m_Buf));
}

int Client::Readn()
{
    m_Strlen = read(m_Sock, m_Buf, sizeof(m_Buf));
    if (m_Strlen == 0)
        return 0;
    return 1;
}

bool Client::ReuseAddr(bool opt)
{
    Option = opt;
    int Optlen = sizeof(Option);
    if ((setsockopt(m_Sock, SOL_SOCKET, SO_REUSEADDR, (void *)&Option, Optlen)) == 0)
        return true;
    else
        return false;
}

char *Client::GetBuf()
{
    return m_Buf;
}

void error(const std::string &message)
{
    std::cout << message << std::endl;
    exit(1);
}

void PrintInfo(const std::string &message, int opt)
{
    if (opt == 1)
        std::cout << message << std::endl;
    else if (opt == 0)
        std::cout << message;
}