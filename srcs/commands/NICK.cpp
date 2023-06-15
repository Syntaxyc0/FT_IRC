// 		/NICK <nickname>
#include "Commands.hpp"


void	Server::Nick(Client *client, std::vector<std::string> args)
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
	if (client->get_registered() != 3 && client->get_registered() != 4)
	{	
		if (client->get_registered() == 1)
			client->set_register(2);
		else
			client->set_register(0);
	}
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



	