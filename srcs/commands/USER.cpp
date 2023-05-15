#include "Client.hpp"
#include "Replies.hpp"
#include "Commands.hpp"

// /USER <username> 0 * <realname>

void	user(Client *client, std::vector<std::string> args)
{
	if (args.size() < 5)
	{
		client->send_reply(ERR_NEEDMOREPARAMS(client->get_hostname(), "USER"));
		return ;
	} 
	if (client->get_registered())
	{
		client->send_reply(ERR_ALREADYREGISTERED(client->get_hostname()));
		return ;
	}
	std::string	username(args[1]);
	std::string	realname(args[4]);
	client->set_username(username);
	client->set_realname(realname);
	client->send_reply("welcome");
	//verifier si l'enregistrement est complet
	//il faut avoir utilise PASS, NICK et USER pour pouvoir etre connecte et passer _is_registered a 1 
}