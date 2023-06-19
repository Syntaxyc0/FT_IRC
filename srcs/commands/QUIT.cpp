#include "Commands.hpp"

void	Quit(Client *client, std::vector<std::string> args, Server &serv)
{
	(void)	serv;
	(void)	args;
	std::string reason = "";
	if (args.size() != 1)
	{
		for (unsigned int i = 1; i < args.size() ; i++)
		{
			reason += args[i];
			if (i != args.size() - 1)
				reason += " ";
		}
	}
	serv.broadcast_server(":" + client->get_fullname() + " QUIT :" + reason);
	client->set_register(DISCONNECTED);
}