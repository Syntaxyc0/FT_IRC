// 		/NICK <nickname>
#include "Commands.hpp"


void	Nick(Client *client, std::vector<std::string> args, Server &serv)
{
	if (args.size() == 1)
	{
		client->send_reply(ERR_NONICKNAMEGIVEN(client->get_hostname()));
		return ;
	}
	if (serv.find_user_by_nickname(args[1]))
	{
		// client->send_reply(ERR_NICKNAMEINUSE(client->get_hostname(), args[1]));
		client->send_message(args[1] + ": Nickname is already in use");
		return ;
	}
	if (client->get_registered() != 3 && client->get_registered() != 4)
	{	
		if (client->get_registered() == PASS_CHECKED)
		{
			client->set_nickname(args[1]);
			client->set_register(NICK_CHECKED);
		}
		else
			client->set_register(NOT_REGISTERED);
		return ;
	}
	serv.broadcast_server(client-> get_nickname() + " changed his nickname to " + args[1]);
	client->set_nickname(args[1]);
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



	