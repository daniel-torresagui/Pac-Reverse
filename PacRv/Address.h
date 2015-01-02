#pragma once
/******************************************************************************************************************
**************                                   Platform detection                                 ***************
******************************************************************************************************************/

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif

/******************************************************************************************************************
**************                           Addign the necessary libreries                             ***************
******************************************************************************************************************/

#if PLATFORM == PLATFORM_WINDOWS

	#include <winsock2.h>
    #pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == PLATFORM_MAC

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#elif PLATFORM == PLATFORM_UNIX

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>

#endif

class Address
{
	sockaddr_in ip;
public:
	Address(void);
	Address(unsigned short port, bool myself = 0);
	Address(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short port);
	Address(char* direccion,unsigned short puerto);
	sockaddr_in getIp(void) {return ip;}
	inline unsigned int getAddress(void) {return ntohl( ip.sin_addr.s_addr );}
	inline unsigned int getPort(void) {return ntohs( ip.sin_port );}
	~Address(void);

	Address& operator=(Address& new_ip);

};
