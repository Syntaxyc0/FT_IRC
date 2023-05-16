#include "Replies.hpp"
#include "Server.hpp"

// 		/PASS <password>

// PASS ne requiert pas du client d'etre authentifie
// 

void    Server::Pass(Client *client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->send_reply(ERR_NEEDMOREPARAMS(client->get_hostname(), "PASS"));
        return ;
    }
    else if (check_auth(client))
    {
        client->send_reply(ERR_ALREADYREGISTERED(client->get_nickname()));
        return ;
    }
	client->set_register(client->get_registered() + 1);
    if (args[0].compare(_password) != 0)
    {
    	client->send_reply(ERR_PASSWDMISMATCH(client->get_hostname()));
        return ;
    }
    if (check_auth(client))
	{
		client->send_reply(RPL_WELCOME(client->get_nickname(), client->get_username(), client->get_hostname()));
		return ;
	}
}