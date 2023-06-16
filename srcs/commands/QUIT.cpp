#include "Commands.hpp"

void	Quit(Client *client, std::vector<std::string> args, Server &serv)
{
	(void)	serv;
	(void)	args;
	client->set_register(DISCONNECTED);
}