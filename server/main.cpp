#include "server.hpp"
#include <cstdlib>

int main()
{
	Server server(5000);
	server.start();

	return EXIT_SUCCESS;
}