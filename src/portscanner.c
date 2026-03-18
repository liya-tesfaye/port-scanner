#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

void port_scanner(char* ipaddress, char* low, char* high)
{
        int start = atoi(low);
        int end = atoi(high);

        struct sockaddr_in sockadd;

        for(int i = start; i < end + 1; i++)
        {
                sockadd.sin_family = AF_INET;
                sockadd.sin_port = htons(i);
                sockadd.sin_addr.s_addr = inet_addr(ipaddress);

                int sock = socket(AF_INET, SOCK_STREAM, 0);
		fcntl(sock, F_SETFL, O_NONBLOCK);

		fd_set myset;
		FD_ZERO(&myset);
		FD_SET(sock, &myset);

                int result = connect(sock, (struct sockaddr*)&sockadd, sizeof(sockadd));

		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		int s = select(sock + 1, NULL, &myset, NULL, &timeout);
		int err = -1;
		socklen_t len = sizeof(err);

		if(s == 0)
		{
			printf("Port %d Filtered\n", i);
			close(sock);
			continue;
		}
		else if(s == 1)
			getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);

		if(err == 0)
                	printf("Port %d: open\n", i);
		else
			printf("Port %d: closed\n", i);

                close(sock);
        }
}

int main(int argc, char* argv[])
{
        if(argc < 4)
        {
                printf("Enter IP address, Port number start and end");
                return 1;
        }

        char ipadd[16], portstart[6], portend[6];

        strcpy(ipadd, argv[1]);
        strcpy(portstart, argv[2]);
        strcpy(portend, argv[3]);

        port_scanner(ipadd, portstart, portend);

        return 0;
}
