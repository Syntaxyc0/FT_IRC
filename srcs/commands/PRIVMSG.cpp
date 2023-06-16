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

void	Privmsg(Client *client, std::vector<std::string> args, Server &serv)
{
	if (args.size() <= 2)
	{
		client->send_reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PRIVMSG"));
		return ;
	}
	else if (!args[1].compare(0 , 1, "#")) //msg a un channel
	{
		if (!serv.find_channel(args[1].erase(0, 0)))
		{
			// client->send_reply(ERR_NOSUCHNICK(client->get_nickname(), args[1].erase(0, 0)));
			client->send_message(args[1].erase(0, 0) + " :No such Channel");
			return ;
		}
		std::string message("");
		for (unsigned int i = 2; i < args.size();i++)
		{
			message += args[i];
			message += " ";
		}
		serv.find_channel(args[1].erase(0, 0))->send_all_clients_from(client->get_nickname(), message);
		// client->send_all_clients_from(args[1], message);
		return ;
	}
	else //msg a un user
	{
		if (!serv.find_client(args[1]))
		{
			client->send_message(args[1] + " :No such nick");
			return ;
		}
		std::string message(args[2]);
		for (unsigned int i = 3; i < args.size();i++)
		{
			message += " ";
			message += args[i];
		}
		serv.find_client(args[1])->send_privmessage_from(client->get_nickname(), message);
	}
}