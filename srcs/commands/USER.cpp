#include "Client.hpp"
#include "Replies.hpp"

// /USER <username> 0 * <realname>

void	user(Client *client, std::vector<std::string> args)
{
	if (args.size() < 4)
	{
		std::cerr<<ERR_NEEDMOREPARAMS(client->get_hostname(), "USER");
		return ;
	} 
	if (client->get_registered())
	{
		std::cerr<<ERR_ALREADYREGISTERED(client->get_hostname());
		return ;
	}
	client->set_username(args[0]);
	client->set_realname(args[3]);
	//verifier si l'enregistrement est complet
	//il faut avoir utilise PASS, NICK et USER pour pouvoir etre connecte et passer _is_registered a 1 
}