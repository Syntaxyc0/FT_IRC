#include "Client.hpp"
#include "Replies.hpp"
#include "Commands.hpp"

// /USER <username> 0 * <realname>

bool	check_auth(Client *client)
{
	if (client->get_registered() != 3)
		return (0);
	return (1);
}

void	user(Client *client, std::vector<std::string> args)
{
	if (args.size() < 5)
	{
		client->send_reply(ERR_NEEDMOREPARAMS(client->get_hostname(), "USER"));
		return ;
	} 
	if (check_auth(client))
	{
		client->send_reply(ERR_ALREADYREGISTERED(client->get_nickname()));
		return ;
	}
	client->set_username(args[1]);
	client->set_realname(args[4]);

	if (client->get_registered() == 2)
	{
		client->set_register(3);
		client->send_reply(RPL_WELCOME(client->get_nickname(), client->get_username(), client->get_hostname()));
	}
	else
		client->set_register(0);
}
