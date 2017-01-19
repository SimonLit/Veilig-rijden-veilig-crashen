#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "response.h"
#include "../datastruct/datastruct.h"

extern bool driving;

int respond(DATAPACKET* dp)
{
	printf("Send responds to socket %d\n",dp->sockFd );
	if(dp->action == DRIVING)
	{
		if(driving == true)
		{
			send(dp->sockFd, "#DRIVE@\n", 8,0);
		}
		else if(driving == true)
		{
			send(dp->sockFd, "#STOP@\n", 7,0);
		}
		else
		{
			send(dp->sockFd, "#DRIVE@\n", 8,0);
		}
	}
	return 0;
}
