#include "Channel.hpp"
#include "Commands.hpp"
#include "Server.hpp"
// window close handling
void	Part(Client *client, std::vector<std::string> args, Server &serv)
{
	Channel *channel = 0;
	for (unsigned long i = 1; i < args.size(); i++)
	{
		if ( ( channel = serv.find_channel( args[i] ) ) ) 
			channel->kick_client(client->get_nickname());
	}
}