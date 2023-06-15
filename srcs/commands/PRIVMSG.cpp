#include "Server.hpp"

//EN TRAVAUX

// 	/PRIVMSG <target> {,<target>} <text to be sent>
// target peut etre le nom d'un user ou d'un channel

// replies possibles
// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402) ??
// ERR_CANNOTSENDTOCHAN (404)
// ERR_TOOMANYTARGETS (407)
// ERR_NORECIPIENT (411)
// ERR_NOTEXTTOSEND (412)
// ERR_NOTOPLEVEL (413)?
// ERR_WILDTOPLEVEL (414)?
// RPL_AWAY (301)?

void	Server::Privmsg(Client *client, std::vector<std::string> args)
{
	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end(); it++)
	{
		std::cout<<*it<<std::endl;
	}
	if (args.size() == 2)
	{
		client->send_reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PRIVMSG"));
		return ;
	}
	else if (!args[1].compare(0 , 1, "#")) //msg a un channel
	{
		if (!find_channel(args[1].erase(0, 0)))
		{
			client->send_reply(ERR_NOSUCHNICK(client->get_nickname(), args[1].erase(0, 0)));
			return ;
		}
		std::string message("");
		for (unsigned int i = 2; i < args.size();i++)
		{
			message += args[i];
			message += " ";
		}
			find_channel(args[1].erase(0, 0))->send_all(message);
			return ;
	}
	else //msg a un user
	{
		std::cout <<"client "<< args[1]<<std::endl;
		if (!find_client(args[1]))
		{
			client->send_reply(ERR_NOSUCHNICK(client->get_nickname(), args[1]));
			return ;
		}
		std::string message("");
		for (unsigned int i = 2; i < args.size();i++)
		{
			message += " ";
			message += args[i];
		}
		find_client(args[1])->send_reply(message);
	}
}