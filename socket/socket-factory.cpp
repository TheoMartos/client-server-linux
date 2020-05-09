#include "socket-factory.hpp"
#include "socket-linux.hpp"

/**
 * Returns a socket function of the OS
 */
ISocket* SocketFactory::createSocket()
{
#if defined (linux)
	return new SocketLinux();
#endif
}