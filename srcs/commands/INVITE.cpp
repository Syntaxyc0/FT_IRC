//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	invite_command( Client *client, std::vector<std::string> received, Server &server )
{
	if ( invite_error( client, received, server) )
		return;

	Channel* channel = server.find_channel( received[2] );
	Client *target = server.find_client( received[1] );

	// add client to channel's list
	channel->send_all( ":" + client->get_fullname() + " JOIN " + received[1] );
	channel->add_client( received[1] );

	target->send_message( client->get_nickname() + " = " + received[1] + " :" + channel_list_user( received, server ) );
	target->send_message( client->get_nickname() + " = " + received[1] + " :End of NAMES list" );
}

bool	invite_error( Client *client, std::vector<std::string> received, Server &server )
{
	std::string nickname = client->get_nickname();
	Channel* channel = server.find_channel( received[2] );

	if ( received.size() != 3 )
		return ( client->send_reply( ERR_NEEDMOREPARAMS( nickname, "INVITE" ) ), true );

	else if ( !channel )
		return ( client->send_reply( ERR_NOSUCHCHANNEL( nickname, channel->get_name() ) ), true );

	else if ( !channel->is_channelClient( nickname ) )
		return ( client->send_reply( ERR_NOTONCHANNEL( nickname, channel->get_name() ) ), true );

	else if ( !channel->is_operator( nickname ) )
		return ( client->send_reply( ERR_CHANOPRIVSNEEDED( nickname, channel->get_name() ) ), true );

	else if ( channel->is_channelClient( server.find_client( received[1] )->get_nickname() ) )
		return ( client->send_reply( ERR_USERONCHANNEL( nickname, server.find_client( received[1] )->get_nickname(),  channel->get_name() ) ), true );

	else if ( (int)channel->get_channelClients().size() >= channel->get_user_limit_nb() )
		return ( client->send_reply( ERR_LIMITREACHED( channel->get_name() ) ), true );

	return ( false );
}
