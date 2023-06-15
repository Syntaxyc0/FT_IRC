#include "Commands.hpp"

void	Quit(Client *client, std::vector<std::string> args)
{
	(void)	args;
	client->set_register(DISCONNECTED);
}