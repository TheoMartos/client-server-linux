#include "socket-linux.hpp"
#include <sstream>

//Set the default value of the static attribut initialized
int SocketLinux::instances = 0;

/**
 * Constructor
 */
SocketLinux::SocketLinux()
{
	_socket = 0;
	SocketLinux::instances++;
}

/**
 * Constructor with always opened socket
 */
SocketLinux::SocketLinux(const SOCKET& sock)
{
	SocketLinux();

	_socket = sock;
}

/**
 * Destructor
  */
SocketLinux::~SocketLinux()
{
	SocketLinux::instances--;
}

/**
 * Starts listening on given port
 */
void SocketLinux::listenOn(const int& port)
{
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(this->_socket, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketLinux::listenOn - An error occured when trying to bind socket";
		throw new std::runtime_error(error.str().c_str());
	}

	if (listen(this->_socket, 5) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketLinux::listenOn - An error occured when trying to listen on port " << port;
		throw new std::runtime_error(error.str().c_str());
	}
}

/**
 * Accepts new client connection
 */
ISocket* SocketLinux::acceptConnection()
{
	SOCKADDR_IN clientsin;
	socklen_t clientsinSize = sizeof(clientsin);
	SOCKET clientSocket = accept(this->_socket, (SOCKADDR*)&clientsin, &clientsinSize);

	if (clientSocket == INVALID_SOCKET)
	{
		std::stringstream error;
		error << "SocketLinux::accept - Invalid client socket";
		throw new std::runtime_error(error.str().c_str());
	}

	return new SocketLinux(clientSocket);
}

/**
 * Connects to the server with given address and port
 */
void SocketLinux::connectTo(const std::string& address, const int& port)
{
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	inet_pton(AF_INET, address.c_str(), &sin.sin_addr.s_addr);

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(this->_socket, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketLinux::connectTo - Unable to connect to server " << address << ":" << port;
		throw new std::runtime_error(error.str().c_str());
	}
}

/**
 * Sends data
 * @param to Pointer to the socket to use to send data
 * @buffer Bytes array containing data to send
 * @bufferLength size of the data to send
 */
void SocketLinux::sendData(ISocket* to, const char* buffer, const int& bufferLength)
{
	SocketLinux* temp = dynamic_cast<SocketLinux*>(to);

	if (send(temp->_socket, buffer, bufferLength, 0) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketLinux::sendData - An error occured when trying to send data";
		throw new std::runtime_error(error.str().c_str());
	}
}

/**
 * Receives data
 * @param from Pointer to the socket to use to get data
 */
int SocketLinux::receiveData(ISocket* from, char* buffer, const int& bufferLength)
{
	SocketLinux* temp = dynamic_cast<SocketLinux*>(from);

	int res = recv(temp->_socket, buffer, bufferLength, 0);

	if (res == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketLinux::receiveData - An error occured when trying to receive data";
		throw new std::runtime_error(error.str().c_str());
	}

	return res;
}

/**
 * Closes the socket
 */
void SocketLinux::close()
{
	shutdown(_socket, SHUT_RDWR);
}