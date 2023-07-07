#include "server.h"

int main(int argc, char** argv) {
    Server serv1;
    serv1.Start(argv[1]);
    
    for(int i = 0; i < 5; ++i)
    {
        serv1.Accept();
        while(serv1.Readen() != 0)
            serv1.Writen();
        serv1.Close();
    }
    return 0;
}