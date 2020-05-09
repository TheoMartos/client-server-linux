#include "client.hpp"
#include "socket-factory.hpp"
#include <iostream>
#include <cstring>

/**
 * Constructor
 */
Client::Client()
{
	socketClient = NULL;
}

/**
 * Connects the client to the given server
 * @param ip IP address of the server
 * @param port Port of the server
 */
void Client::connect(const std::string& ip, const int& port)
{
	const unsigned short BUFFER_SIZE = 500;
	char* buffer = new char[BUFFER_SIZE];

	try
	{
		std::cout << "Connection to " << ip << ":" << port << "in progress..." << std::endl;

		socketClient = SocketFactory::createSocket();

		socketClient->connectTo(ip, port);

		std::cout << " Connected." << std::endl;

		std::cout << "Sending data...";

		socketClient->sendData(socketClient, "Hello !", 7);

		std::cout << " Sended." << std::endl;

		memset(buffer, 0, BUFFER_SIZE);

		std::cout << "Receive data from server...";
		socketClient->receiveData(socketClient, buffer, BUFFER_SIZE);
		
		std::cout << std::endl << buffer << std::endl;

		socketClient->close();

		std::cout << "End of the connection." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	delete[] buffer;
}