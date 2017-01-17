#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "response.h"
#include "../datastruct/datastruct.h"

int respond(DATAPACKET* dp)
{
	printf("Send responds to socket %d\n",dp->sockFd );
	if(dp->action == DRIVING)
	{
		send(dp->sockFd, "#Je moeder is een hoer@", 23, 0);
	}


	return 0;
}
