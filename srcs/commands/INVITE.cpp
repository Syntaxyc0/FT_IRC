//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	invite_command( Client *client, std::vector<std::string> received, Server &server );
{
	if ( invite_error( client ) )
		return;

	// add client to channel's list
	current.add_client( received[1] );

	client->send_message( "PRIVMSG " + server.find_channel( received[2] ) + " :" + server.find_client( received[1] ).get_nickname() + " has joined channel" );
}

bool	invite_error( Client *client, std::vector<std::string> received, Server &server )
{
	if ( received.size() != 3 )
		return ( client->send_reply( ERR_NEEDMOREPARAMS( client->get_nickname(), "INVITE" ) ), true );

	else if ( !server.find_channel( received[2] ) )
		return ( client->send_reply( ERR_NOSUCHCHANNEL( client->get_nickname(), server.find_channel( received[2] )->get_name() ) ), true );

	else if ( !server.find_channel( received[2] )->is_channelClient( client->get_nickname() ) )
		return ( client->send_reply( ERR_NOTONCHANNEL( client->get_nickname(), server.find_channel( received[2] )->get_name() ) ), true );

	else if ( !server.find_channel( received[2] )->is_operator( client->get_nickname() ) )
		return ( client->send_reply( ERR_CHANOPRIVSNEEDED( client->get_nickname(), server.find_channel( received[2] )->get_name() ) ), true );

	else if ( server.find_channel( received[2] )->is_channelClient( server.find_client(  ) ) )
		return ( client->send_reply( ERR_USERONCHANNEL( client->get_nickname(), target,  server.find_channel( received[2] )->get_name() ) ), true );

	else if ( (int)current.get_channelClients().size() >= current.get_user_limit_nb() )
		return ( client->send_reply( ERR_LIMITREACHED( server.find_channel( received[2] )->get_name() ) ), true );

	return ( false )
}
