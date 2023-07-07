#include "client.h"

int main(int argc, char** argv) 
{
    Client c;
    // argv[1] = "127.0.0.1", argv[2] = "9111";
    

    c.Start(argv[1], argv[2]);

    while(1)
    {
        c.Writen();
        if(c.Readn() == 0)
            break;
        printf("来自服务器消息: %s\n", c.GetBuf());
    }
}
