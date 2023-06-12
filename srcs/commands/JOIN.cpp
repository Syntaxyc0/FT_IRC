// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_TOOMANYCHANNELS (405)
// ERR_BADCHANNELKEY (475)
// ERR_BANNEDFROMCHAN (474)
// ERR_CHANNELISFULL (471)
// ERR_INVITEONLYCHAN (473)
// ERR_BADCHANMASK (476)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
// RPL_NAMREPLY (353)
// RPL_ENDOFNAMES (366)

#include "Commands.hpp"

void	join( Client *client, std::vector<std::string> received, Server &server)
{
	if ( !server.find_channel( received[1] ) )
		create_channel(client, received[1], server);
	std::cout << server.find_channel( received[1] )->get_name() << std::endl;
}

void	create_channel(Client *client, std::string name, Server &server)
{
	Channel (name, client, server);
}