//****************************************************//
//                   Commande MODE                    //
//****************************************************//

#include "Commands.hpp"

int	mode_parser(Client *client, std::vector<std::string> received, Server &server)
{
	if (received.size() < 2)
		client->send_message( ERR_NEEDMOREPARAMS( client->get_nickname(), "MODE" ) );
	for (int i = 1; i < (int)received.size(); i++)
	{
		if (received[i][1] == 'i')
			mode_invite_only( server.find_channel( received[1] ), client, received[i][0]);

	}
}

void	mode_manager(Client *client, std::vector<std::string> received, Server &server)
{
	if ( received[2] == "-i")
		mode_invite_only( server.find_channel( received[1] ), client );
	else if ( received[2] == "-k" )
		mode_channel_key( server.find_channel( received[1] ), client, received );
	else if ( received[2] == "-t" )
		mode_restricion_topic_cmd( server.find_channel( received[1] ), client );
	else if ( !strncmp("-l", received[2].c_str(), 2) )
		mode_limit_user( server.find_channel( received[1] ), client, received );
	else if ( received[2] == "-o" )
		mode_operator_privilege(server.find_channel( received[1] ), client, received[2]);
}

// -i set/remove invite-only channel :
//  "/MODE -i" active le invite only, s'il est désactivé et inversement. 
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

int	mode_invite_only(Channel *current, Client *user, char sign)
{
	std::string message = "PRIVMSG ";
	message += current->get_name() + " :";

	if (sign == '+')
	{
		current->set_invite_only(1);
		user->send_message( message += "Invite-only mode is ON" );
	}
	else
	{
		current->set_invite_only(0);
		user->send_message( message += "Invite-only mode is OFF" );
	}
}

// -k set/remove channel key (pw)
// "/MODE -k (password)" active l'utilisation d'un mot de passe pour JOIN le channel s'il est précisé. Si il n'est pas précisé, il désactive la demande de mot de passe.
// Si un mot de passe est précisé alors qu'il y en avait déja un, il est alors modifié par le nouveau.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_channel_key( Channel *current, Client *user, std::vector<std::string> received )
{
	std::string message = "PRIVMSG ";
	message += current->get_name() + " :";

	if ( received.size() == 3 )
		user->send_message( message += "Channel key is OFF" );
	else if ( current->get_channel_key() && received.size() == 4 )
		user->send_message( message += "Channel key has been changed" );
	else
	{
		current->set_channel_key(received[3]);
		user->send_message( message += "Channel key is ON" );
	}
}


// -t set/remove restriction of the topic command to channel operator
// "/MODE -t" active la restriction à tous les clients du Channel de changer le TOPIC. S'il était activé, le désactive.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_restricion_topic_cmd(Channel *current, Client *user)
{
	std::string message = "PRIVMSG ";
	message += current->get_name() + " :";

	current->set_restriction_TOPIC_cmd();
	if (current->get_restriction_TOPIC_cmd())
		user->send_message( message += "Restriction to TOPIC command is ON" );
	else
		user->send_message( message += "Restriction to TOPIC command is OFF" );
}

// -l set/remove the user limit to Channel:
// "/MODE -l (nb)" active le nombre de Client admis dans le Channel si (nb) est précisé. Sinon, désactive la limite.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_limit_user(Channel *current, Client *user, std::vector<std::string> received)
{
	std::string message = "PRIVMSG ";
	message += current->get_name() + " :";

	if ( user_limit_int_number( received[2] ) )
	{
		int limit_nb = atoi( received[2].c_str() );
		if ( limit_nb < (int)current->get_channelClients().size() )
			user->send_message( message += "Error : the limit cannot be less than the current number of users in that channel");
		else
		{
			current->set_user_limit( limit_nb, user , current->get_name());
			user->send_message( message += "User limit is " + received[2].erase( 0, 2 ) );
		}
	}
	else 
	{
		current->set_user_limit( -1, user, current->get_name());
		user->send_message( message += "User limit is OFF" );
	}
}

int	user_limit_int_number(std::string l)
{
	int i;

	if ( l.size() == 2 )
		return (0);
	else
	{
		l.erase( 0, 2 );
		i = atoi( l.c_str() );
	}
	return ( i );
}

// -o give/take channel operator privilege
// "MODE -o [target]" Si le client est au moins operator, il peut donner les pivilèges à n'importe qui.
// Seul le primordial peut retirer les privilèges. Envoie un message annonçant le nouvel operator, ou le client aayant été retrogradé.

void	mode_operator_privilege(Channel *current, Client *user, std::string target)
{
	current->operator_privilege(user, target);
} 