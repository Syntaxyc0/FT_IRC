// ERR_NEEDMOREPARAMS (461)
// ERR_CHANNELISFULL (471) MODE limit_user
// ERR_INVITEONLYCHAN (473) MODE invite only
// ERR_BADCHANNELKEY (475) MODE password
// ERR_NOSUCHCHANNEL (403) ??
// ERR_TOOMANYCHANNELS (405) ??
// ERR_BANNEDFROMCHAN (474) ??
// ERR_BADCHANMASK (476) ??
// RPL_TOPIC (332) ?? 
// RPL_TOPICWHOTIME (333) ?? 
// RPL_NAMREPLY (353) ??
// RPL_ENDOFNAMES (366) ??

#include "Commands.hpp"

void	join_command( Client *client, std::vector<std::string> received, Server &server )
{

	if ( join_error( client, received, server ) )
		return ;

	if ( !server.find_channel( received[1] ) )
	{
		Channel ret(received[1], client->get_nickname(), server);
		server.add_Channels( ret );
	}
	else
		server.find_channel( received[1] )->add_client( client->get_nickname() );

	Channel *current = server.find_channel( received[1] );

	client->set_add_channel(current);
	current->send_everyone_else( ":" + client->get_fullname() + " JOIN " + received[1], client->get_nickname());
	if (server.find_channel( received[1] )->get_topic() != "")
		client->send_message( ":localhost 332 "+ client->get_nickname() + " " + received[1] + " " + server.find_channel( received[1] )->get_topic() );
	client->send_message( ":localhost 353 "+ client->get_nickname() + " = " + received[1] + " :" + channel_list_user( received, server ) );
}

bool	join_error( Client *client, std::vector<std::string> received, Server &server )
{
	Channel *current = server.find_channel( received[1] );

	if (received.size() < 2)
		return ( client->send_reply( ERR_NEEDMOREPARAMS( client->get_nickname(), "JOIN" ) ), true );

	else if ( current && current->get_user_limit() == 1 && (int)current->get_channelClients().size() >=  current->get_user_limit_nb() )
		return ( client->send_reply( ERR_CHANNELISFULL( client->get_nickname(), current->get_name() ) ), true );

	else if ( current && current->get_channel_key() && received.size() < 3)
		return ( client->send_reply( ERR_BADCHANNELKEY( client->get_nickname(), current->get_name() ) ), true );

	else if ( current && current->get_channel_key() && received[2] != current->get_password() )
		return ( client->send_reply( ERR_BADCHANNELKEY( client->get_nickname(), current->get_name() ) ), true );

	else if ( current && current->get_invite_only() )
		return ( client->send_reply( ERR_INVITEONLYCHAN( client->get_nickname(), current->get_name() ) ), true );
	
	return (0);
}

std::string	channel_list_user( std::vector<std::string> received, Server &server )
{
	std::string message;
	Channel *current = server.find_channel( received[1] );

	for ( int i = 0; i < (int)current->get_channelClients().size(); i++ )
	{
		if (current->is_operator(current->get_channelClients().at(i)))
			message += '@';
		message += current->get_channelClients().at(i) + " ";
	}
	return ( message );
}