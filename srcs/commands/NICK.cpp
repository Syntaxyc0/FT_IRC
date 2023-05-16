// 		/NICK <nickname>
#include "Commands.hpp"

Client	*Server::find_user_by_nickname(std::string nickname)
{
	for (std::map<int, Client*>::iterator it=_clientList.begin(); it != _clientList.end();it++)
	{
		if (nickname == it->second->get_nickname())
			return (it->second);
	}
	return (NULL);
}

void	Server::nick(Client *client, std::vector<std::string> args)
{
	if (args.size() == 1)
	{
		client->send_reply(ERR_NONICKNAMEGIVEN(client->get_hostname()));
		return ;
	}
	if (find_user_by_nickname(args[1]))
	{
		client->send_reply(ERR_NICKNAMEINUSE(client->get_hostname(), args[1]));
		return ;
	}
	client->set_nickname(args[1]);
	if (client->get_registered() == 2)
	{
		client->set_register(3);
		client->send_reply(RPL_WELCOME(client->get_nickname(), client->get_username(), client->get_hostname()));
		client->send_reply("auth ok !");
	}
	else
		client->set_register(1);
}
// erreurs possibles

// ERR_NONICKNAMEGIVEN (431) 
//   "<client> :No nickname given"

// ERR_ERRONEUSNICKNAME (432) 
//   "<client> <nick> :Erroneus nickname"

// ERR_NICKNAMEINUSE (433) 
//   "<client> <nick> :Nickname is already in use"

// ERR_NICKCOLLISION (436) 
//   "<client> <nick> :Nickname collision KILL from <user>@<host>"



	