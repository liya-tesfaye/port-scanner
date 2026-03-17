#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void port_scanner(char* ipaddress, char* low, char* high)
{
        int start = atoi(low);
        int end = atoi(high);

        struct sockaddr_in sockadd;

        for(int i = start; i < end; i++)
        {
                sockadd.sin_family = AF_INET;
                sockadd.sin_port = htons(i);
                sockadd.sin_addr.s_addr = inet_addr(ipaddress);

                int sock = socket(AF_INET, SOCK_STREAM, 0);
                int result = connect(sock, (struct sockaddr*)&sockadd, sizeof(sockadd));

                if(result == 0)
                        printf("Port %d: open\n", i);
//                if(result == -1)
//                        printf("Port %d: Closed\n", i);

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
