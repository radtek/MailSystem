#ifndef _TCPCLIENT_SOCKET_H_
#define _TCPCLIENT_SOCKET_H_
#endif // !_TCPCLIENT_SOCKET_H_

#define DEFAULT_READ_TIMEOUT 10
#define DEFAULT_WRITE_TIMEOUT 10

#include <WinSock2.h>
#include <string>
#include <WS2tcpip.h>

typedef std::string rstring;


class TCPClientSocket
{
public:
	TCPClientSocket();
	TCPClientSocket(const char* addr, int port, int tmo);

	bool connect2ServerAddr(const char* addr, int port, int tmo);
	sockaddr getServerAddr();
	
	void closeSocket();
	int readLine(char* buf, int len, int tmo = DEFAULT_READ_TIMEOUT);
	int readBlock(char* buf, int len, int tmo = DEFAULT_READ_TIMEOUT);
	int write(char* buf, int len, int tmo = DEFAULT_WRITE_TIMEOUT);

protected:
	sockaddr mServerAddr;
	SOCKET mSocket;
	virtual void report(rstring info);

private:
	bool createNBSocketAndConnect(addrinfo* info, int tmo = DEFAULT_WRITE_TIMEOUT);
};

