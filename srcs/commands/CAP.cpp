#include "Commands.hpp"

void	Cap(Client *client, std::vector<std::string> args, Server &serv)
{
	(void)args;
	(void)serv;
	if (client->get_registered() == NOT_REGISTERED)
		client->set_register(AWAITING_AUTH);
	return ;
}