#include "server.hpp"
#include "socket-factory.hpp"
#include <iostream>
#include <exception>
#include <thread>

/**
 * Constructor
 * @param listeningPort Listening port of the server
 */
Server::Server(const int& listeningPort)
{
	port = listeningPort;
	socketServer = nullptr;
}

/**
 * Destructor
 */
Server::~Server()
{
	if (socketServer)
		delete socketServer;
}

/**
 * Starts listening on the given port
 */
void Server::start()
{
	try {
		socketServer = SocketFactory::createSocket();

		socketServer->listenOn(port);

		std::cout << "Server started. Waiting for connections..." << std::endl;

		std::thread connectionThread(&Server::waitForConnections, socketServer);
		connectionThread.join();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

/**
 * Thread Function - Waits for new connections to accept
 */
void Server::waitForConnections(ISocket* socketServer)
{
	while (true)
	{
		try
		{
			ISocket* socketClient = socketServer->acceptConnection();
			new std::thread(&Server::processConnection, socketServer, socketClient);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

/**
 * Thread function - Process a client request
 */
void Server::processConnection(ISocket* socketServer, ISocket* socketClient)
{
	const unsigned short BUFFER_SIZE = 4096;
	char* buffer = new char[BUFFER_SIZE];

	try {
		const std::string EOL = "\r\n";
		std::cout << "Incoming connection - Process request..." << std::endl;

		socketServer->receiveData(socketClient, buffer, BUFFER_SIZE);
		std::cout << buffer << std::endl;

		std::string response = "HTTP/1.0 200 OK" + EOL;
		response += "Content-Type: text/html" + EOL;
		response += "Content-Length: 48" + EOL;
		response += EOL;
		response += "<html><head></head><body>Page Web !</body></html>";

		socketServer->sendData(socketClient, response.c_str(), response.length());

	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	delete[] buffer;
	socketClient->close();
	std::cout << "Connection closed." << std::endl;
}