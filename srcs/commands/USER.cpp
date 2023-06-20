#include "Client.hpp"
#include "Replies.hpp"
#include "Commands.hpp"

// /USER <username> 0 * <realname>

bool	check_auth(Client *client)
{
	if (client->get_registered() != REGISTERED)
		return (0);
	return (1);
}

void	User(Client *client, std::vector<std::string> args, Server &serv)
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

	if (client->get_registered() == NICK_CHECKED)
	{
		client->set_register(REGISTERED);
		// client->send_reply(RPL_WELCOME(client->get_nickname(), client->get_username(), client->get_hostname()));
		client->send_message(":localhost 001 " + client->get_nickname() + " :Welcome to IRC " + client->get_nickname()+"!"+client->get_username()+"@localhost");
		std::cout<<MAGENTA<<client->get_nickname()<<" has registered"<<END<<std::endl;
	}
	else
	{
		client->set_register(NOT_REGISTERED);
		return ;
	}
	serv.broadcast_server(client->get_nickname() + " has joined the server");
}
