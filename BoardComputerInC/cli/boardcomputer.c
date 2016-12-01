#include <stdio.h>
#include "serverSocket.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"

int main(int argc, char const *argv[])
{
    int temp = 0;
    setupCommunicationServer(NodeInternal, ServiceInternal, &temp);
    while(1)
    {
        acceptinConnectionsOnServer(temp);
    }
    return 0;
}