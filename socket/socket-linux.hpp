#ifndef SOCKET_LINUX_HPP
#define SOCKET_LINUX_HPP

#include "isocket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1

/**
 * Linux Socket
 */
class SocketLinux: public ISocket
{
private:
	/**
	 * Opened Linux socket
	 */
	SOCKET _socket;

public:
	/**
	 * Constructor
	 */
	SocketLinux();

	/**
	 * Constructor with always opened socket 
	 */
	SocketLinux(const SOCKET& sock);

	/**
	 * Desctructor
	 */
	~SocketLinux();
		
	/**
	 * Starts listening on given port
	 */
	void listenOn(const int& port);

	/**
	 * Accepts new client connection
	 */
	ISocket* acceptConnection();

	/**
	 * Connects to the server with given address and port
	 */
	void connectTo(const std::string& address, const int& port);

	/**
	 * Sends data
	 * @param to Pointer to the socket to use to send data
	 * @buffer Bytes array containing data to send
	 * @bufferLength size of the data to send
	 */
	void sendData(ISocket* to, const char* buffer, const int& bufferLength);

	/**
	 * Receives data
	 * @param from Pointer to the socket to use to get data
	 */
	int receiveData(ISocket* from, char* buffer, const int& bufferLength);

	/**
	 * Closes the socket
	 */
	void close();
};

#endif