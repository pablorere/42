#include "webserv.hpp"

int main(int ac, char **av)
{
	try
	{
		Service webserv(ac, av);
		// webserv.printServersInfo();
		webserv.setup();
		webserv.launch();
	}
	catch(const std::exception &e)
	{
		std::cerr << RED << "Error:\t" << e.what() << RESET << std::endl;
		return (EXIT_FAILURE);
	}
}