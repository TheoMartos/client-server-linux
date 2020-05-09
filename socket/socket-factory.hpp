#ifndef SOCKET_FACTORY_HPP
#define SOCKET_FACTORY_HPP

#include "isocket.hpp"

/**
 * Socket Factory
 */
class SocketFactory
{
public:
	/**
	 * Returns a socket function of the OS
	 */
	static ISocket* createSocket();
};

#endif