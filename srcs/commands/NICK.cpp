// 		/NICK <nickname>
#include "Commands.hpp"


bool	check_nick(std::string nick)
{
	for (unsigned int i = 0; i < nick.size(); i++)
	{
		if (!isalnum(nick[i]) && nick[i] != '\\' && nick[i] != '|' && nick[i] != '{' && nick[i] != '}' && nick[i] != '[' && nick[i] != ']')
			return false;
	}
	return true;
}

void	Nick(Client *client, std::vector<std::string> args, Server &serv)
{
	std::string name = args[1];
	if (args.size() == 1)
	{
		client->send_reply(ERR_NONICKNAMEGIVEN(client->get_nickname()));
		return ;
	}
	if (!check_nick(args[1]))
	{
		client->send_reply(ERR_ERRONEUSNICKNAME(client->get_nickname(), args[1]));
		return ;
	}
	if (serv.find_client(args[1]))
	{
		client->send_reply(ERR_NICKNAMEINUSE(client->get_hostname(), args[1]));
		name += "_";
		while (serv.find_client(name))
			name += "_";
	}
	if (client->get_registered() != 3 && client->get_registered() != 4)
	{	
		if (client->get_registered() == PASS_CHECKED)
		{
			client->set_nickname(name);
			client->set_register(NICK_CHECKED);
		}
		else
			client->set_register(NOT_REGISTERED);
		return ;
	}
	serv.broadcast_server(":" + client->get_fullname() + " NICK " + name);
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



	