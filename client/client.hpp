#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "socket-linux.hpp"

/**
 * Test client
  */
class Client
{
private:
	/**
	 * Socket of the client
	 */
	ISocket* socketClient;

public:
	/**
	 * Constructor
	 */
	Client();

	/**
	 * Connects the client to the given server
	 * @param ip IP address of the server
	 * @param port Port of the server
	 */
	void connect(const std::string& ip, const int& port);
};

#endif